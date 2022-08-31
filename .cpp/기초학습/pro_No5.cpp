#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define CMD_INIT 1
#define CMD_NUMBER_OF_CANDIDATE 2
#define CMD_MAX_AREA 3

extern void init(int N, int mMap[20][20]);
extern int numberOfCandidate(int M, int mStructure[5]);
extern int maxArea(int M, int mStructure[5], int mSeaLevel);

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

static int mMap[20][20];
static int mStructure[5];

static bool run()
{
    int numQuery;
    int N, M, mSeaLevel;
    int userAns, ans;

    bool isCorrect = false;

    scanf("%d", &numQuery);

    for (int i = 0; i < numQuery; ++i)
    {
        int cmd;
        scanf("%d", &cmd);

        switch (cmd)
        {
        case CMD_INIT:
            scanf("%d", &N);
            for (int j = 0; j < N; j++)
                for (int k = 0; k < N; k++)
                    scanf("%d", &mMap[j][k]);
            init(N, mMap);
            isCorrect = true;
            break;
        case CMD_NUMBER_OF_CANDIDATE:
            scanf("%d", &M);
            for (int j = 0; j < M; j++)
                scanf("%d", &mStructure[j]);
            userAns = numberOfCandidate(M, mStructure);
            scanf("%d", &ans);
            if (userAns != ans)
            {
                isCorrect = false;
            }
            break;
        case CMD_MAX_AREA:
            scanf("%d", &M);
            for (int j = 0; j < M; j++)
                scanf("%d", &mStructure[j]);
            scanf("%d", &mSeaLevel);
            userAns = maxArea(M, mStructure, mSeaLevel);
            scanf("%d", &ans);
            if (userAns != ans)
            {
                isCorrect = false;
            }
            break;
        default:
            isCorrect = false;
            break;
        }
    }
    return isCorrect;
}

int main()
{
    setbuf(stdout, NULL);
    // freopen("sample_input.txt", "r", stdin);

    int T, MARK;
    scanf("%d %d", &T, &MARK);

    for (int tc = 1; tc <= T; tc++)
    {
        int score = run() ? MARK : 0;
        printf("#%d %d\n", tc, score);
    }

    return 0;
}

//#include <bits/stdc++.h>
#include <vector>
using namespace std;

#define endl '\n' 
#define fi first
#define se second

// erase
#define CMD_INIT 1
#define CMD_NUMBER_OF_CANDIDATE 2
#define CMD_MAX_AREA 3

typedef pair<int, int> pi;


int N, A[22][22], B[22][22];
int TABLE[50005];

int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { 1, -1, 0, 0 };


bool safe(int x, int y) {
    return (x > 0 && y > 0 && x <= N && y <= N);
}

bool safe_new(int x, int y) {
    return (x >= 0 && y >= 0 && x <= N + 1 && y <= N + 1);
}

bool palindrome(int x) {
    int a = x, b = 0;
    while (x) {
        b = b * 10 + x % 10;
        x /= 10;
    }
    return a == b;
}


struct Queue {
    pi data[505];
    int l, r;

    void init() {
        l = r = 0;
    }

    void push(int x, int y) {
        data[r++] = pi(x, y);
    }

    pi pop() {
        return data[l++];
    }

    bool empty() {
        return l == r;
    }
};

bool visit[22][22];
Queue q;

int cal(int lev) {
    q.init();
    memset(visit, 0, sizeof(visit));

    q.push(0, 0);
    visit[0][0] = 1;

    int ret = (N + 2) * (N + 2);

    while (!q.empty()) {
        pi cur = q.pop();
        ret--;

        for (int i = 0; i < 4; i++) {
            int nx = cur.first + dx[i];
            int ny = cur.second + dy[i];
            if (safe_new(nx, ny) && !visit[nx][ny] && B[nx][ny] < lev) {
                visit[nx][ny] = 1;
                q.push(nx, ny);
            }
        }
    }

    return ret;
}

int ls[8005], idx = 0;
void init(int n, int _A[20][20]) {
    memset(B, 0, sizeof(B));

    for (int i = 0; i < idx; i++) TABLE[ls[i]] = 0;
    idx = 0;

    N = n;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) A[i][j] = B[i][j] = _A[i - 1][j - 1];
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            int base = A[i][j];

            for (int k = 0; k < 4; k++) {
                int nx = i + dx[k];
                int ny = j + dy[k];

                int num = 4;

                for (int m = 1; m < 5; m++) {
                    if (!safe(nx, ny)) break;

                    num = num * 10 + (A[nx][ny] - base + 4);
                    TABLE[num]++;
                    ls[idx++] = num;

                    nx += dx[k];
                    ny += dy[k];
                }
            }
        }
    }
}

int numberOfCandidate(int M, int block[5]) {
    if (M == 1) return N * N;

    int num = 4;
    for (int i = 1; i < M; i++) num = num * 10 + (block[0] - block[i] + 4);

    int ret = TABLE[num];

    if (palindrome(num)) ret /= 2;

    return ret;
}

int maxArea(int M, int block[5], int lev) {
    int ans = -1;

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            int base = A[i][j];
            int t = base + block[0];

            for (int k = 0; k < 4; k++) {
                int nx = i + dx[k];
                int ny = j + dy[k];

                bool flag = true;

                for (int m = 1; m < M; m++) {
                    if (!safe(nx, ny)) {
                        flag = false;
                        break;
                    }
                    if (A[nx][ny] + block[m] != t) {
                        flag = false;
                        break;
                    }

                    nx += dx[k];
                    ny += dy[k];
                }

                if (flag) {
                    nx = i;
                    ny = j;

                    for (int m = 0; m < M; m++) {
                        B[nx][ny] = t;
                        nx += dx[k];
                        ny += dy[k];
                    }

                    ans = max(ans, cal(lev));

                    nx = i;
                    ny = j;
                    for (int m = 0; m < M; m++) {
                        B[nx][ny] = A[nx][ny];
                        nx += dx[k];
                        ny += dy[k];
                    }
                }

            }
        }
    }

    return ans;
}