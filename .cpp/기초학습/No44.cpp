#include <iostream>
#include <algorithm>
#define MAX_VALUE 1000001;

using namespace std;

int N, M;
int cows[1000001];

int binarySearch(int arr[], int value) {
	int left = 0;
	int right = N - 1;
	int mid = (left + right) / 2;

	if (value < arr[left])
		return 0;
	if (arr[right] < value)
		return N - 1;

	while (left <= right) {
		mid = (left + right) / 2;

		if (arr[mid] == value) {
			return mid;
		}
		else if (arr[mid] < value) {
			left = mid + 1;
		}
		else {
			right = mid - 1;
		}
	}

	if (arr[mid] < value)
		mid++;

	return mid;
}

int main()
{
	int T;
	cin >> T;

	for (int tc = 1; tc <= T; tc++) {
		cin >> N >> M;

		int a, b;
		cin >> a >> b;
		int dx = abs(a - b);

		for (int i = 0; i < N; i++) {
			cin >> cows[i];
		}
		sort(cows, cows + N);

		int min = MAX_VALUE;
		int cnt = 0;

		for (int i = 0; i < M; i++) {
			int H_pos;
			cin >> H_pos;
			int cIdx = binarySearch(cows, H_pos);

			if (0 <= cIdx && cIdx < N) {
				int C_pos = cows[cIdx];
				int dz = abs(C_pos - H_pos);

				if (min > dz) {
					min = dz;
					cnt = 1;
				}
				else if (min == dz) {
					cnt++;
				}
			}

			if (0 <= cIdx && cIdx < N && cows[cIdx] != H_pos) {
				int C_pos = cows[cIdx-1];
				int dz = abs(C_pos - H_pos);
				if (min > dz) {
					min = dz;
					cnt = 1;
				}
				else if (min == dz) {
					cnt++;
				}
			}
		}
		cout << "#" << tc << " " << (dx + min) << " " << cnt << endl;
	}
}