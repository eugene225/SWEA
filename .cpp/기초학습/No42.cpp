#include <iostream>
using namespace std;

int N;
long M;
long* candy;

bool check(long bag, long m) {
	long cnt = 0;
	for (int i = 0; i < N; i++) {
		cnt += candy[i] / bag;
	}
	return cnt >= m;
}

long long binarySearch(long candy[], long m) {
	long min = 0;
	long max = 1000000000000000000L;
	long mid = 0;

	while (max != min) {
		mid = (max + min + 1) / 2;
		if (check(mid, m)) {
			min = mid;
		}
		else max = mid - 1;
	}
	return min;
}

int main()
{
	int T;
	cin >> T;


	for (int tc = 1; tc <= T; tc++) {
		cin >> N >> M;

		candy = new long[N];

		for (int i = 0; i < N; i++) {
			cin >> candy[i];
		}

		cout << "#" << tc << " " << binarySearch(candy, M) << endl;
		
	}
}