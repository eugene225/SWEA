#include<queue>
#include<vector>
#include<algorithm>

int g_timestamp;

struct post {
    int uID;
    int timestamp;
    int like;
    int pID;
    post(int uID, int timestamp, int pID) {
        this->uID = uID;
        this->timestamp = timestamp;
        this->pID = pID;
        this->like = 0;
    }
    post() = default;
    bool operator<(post another_post) {
        if (g_timestamp - this->timestamp <= 1000 && g_timestamp - another_post.timestamp > 1000) {
            return false;
        }
        else if (g_timestamp - this->timestamp > 1000 && g_timestamp - another_post.timestamp <= 1000) {
            return true;
        }
        else if (g_timestamp - this->timestamp > 1000 && g_timestamp - another_post.timestamp > 1000) {
            return this->timestamp < another_post.timestamp;
        }
        else {//g_timestamp-this->timestamp<=1000 && g_timestamp-another_post->timestamp<=1000
            if (this->like == another_post.like) {
                return this->timestamp < another_post.timestamp;
            }
            else {
                return this->like < another_post.like;
            }
        }

    }
};
int p_cnt = 1;
post postpool[100001];

post* getpost(int uID, int timestamp, int pID) {

    postpool[p_cnt] = post(uID, timestamp, pID);
    return &postpool[p_cnt++];
}

struct greater {//minheap
    bool operator()(post* post1, post* post2) {
        if (g_timestamp - post1->timestamp <= 1000 && g_timestamp - post2->timestamp > 1000) {
            return true;
        }
        else if (g_timestamp - post1->timestamp > 1000 && g_timestamp - post2->timestamp <= 1000) {
            return false;
        }
        else if (g_timestamp - post1->timestamp > 1000 && g_timestamp - post2->timestamp > 1000) {
            return post1->timestamp > post2->timestamp;
        }
        else {//g_timestamp-post1->timestamp<=1000 && g_timestamp-post2->timestamp<=1000
            if (post1->like == post2->like) {
                return post1->timestamp > post2->timestamp;
            }
            else {
                return post1->like > post2->like;
            }
        }
    }
};

std::vector<int> follow_list[1001];
std::vector<post* > userpost[1001];

void init(int N)
{
    p_cnt = 1;
    for (int i = 1; i < N + 1; i++) {
        userpost[i].clear();
        follow_list[i].clear();
    }
    //자기자신 팔로우
    for (int i = 1; i < N + 1; i++) {
        follow_list[i].push_back(i);
    }

}
void follow(int uID1, int uID2, int timestamp)
{
    g_timestamp = timestamp;
    follow_list[uID1].push_back(uID2);
}
void makePost(int uID, int pID, int timestamp)
{
    g_timestamp = timestamp;
    userpost[uID].push_back(getpost(uID, timestamp, pID));

}
void like(int pID, int timestamp)
{
    g_timestamp = timestamp;
    postpool[pID].like++;

}
void getFeed(int uID, int timestamp, int pIDList[])
{
    g_timestamp = timestamp;
    std::priority_queue<post*, std::vector<post* >, greater> pq_min;
    for (auto element : follow_list[uID]) {
        for (auto element2 : userpost[element]) {

            if (pq_min.size() < 10) {
                pq_min.push(element2);
            }
            else {
                if (timestamp - element2->timestamp > 1000) break;
                pq_min.pop();
                pq_min.push(element2);
            }
        }
    }
    int size = pq_min.size();
    for (int i = size - 1; i >= 0; i--) {
        pIDList[i] = pq_min.top()->pID;
        pq_min.pop();
    }
}
