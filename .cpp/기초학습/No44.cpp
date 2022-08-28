#include <iostream>
#include <algorithm>

#define MAX_VALUE 1000001;
using namespace std;

int main()
{
	int T;
	cin >> T;

	int N, M;
	for (int tc = 1; tc <= T; tc++) {
		cin >> N >> M;

		int a, b;
		cin >> a >> b;
		int dx = abs(a - b);

		int* cows = new int[N];
		for (int i = 0; i < N; i++) {
			cin >> cows[i];
		}
		sort(cows, cows + N);

		int min = MAX_VALUE;
		int cnt = 0;

		for (int i = 0; i < M; i++) {
			int H_pos;
			cin >> pos;
			int cIdx = binarySearch(cows, pos);

			if (0 <= cIdx && cIdx < N) {
				int C_pos
			}
		}

	}
}