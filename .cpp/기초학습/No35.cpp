#include <iostream>
#include <queue>
#pragma warning(disable:4996)

using namespace std;

int N, K, ans;
int num[11];

void input() {
	int i;
	scanf("%d", &N);

	for (i = 0; i < N; i++) {
		scanf("%d", &num[i]);
	}
	scanf("%d", &K);
}

void getans() {
	int i;
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	pq.push(make_pair(0, K));

	while (pq.top().second) {
		pair<int, int> cur = pq.top();
		pq.pop();
		pq.push(make_pair(cur.first + cur.second, 0));

		for (i = 0; i < N; i++) {
			pq.push(make_pair(cur.first + cur.second % num[i], cur.second / num[i]));
		}
	}
	ans = pq.top().first;
}

int main() {
	int T;
	scanf("%d", &T);

	for (int tc = 1; tc <= T; tc++) {
		input();
		getans();
		printf("#%d %d\n", tc, ans);
	}
	return 0;
}