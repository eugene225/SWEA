#include <iostream>
using namespace std;

constexpr size_t MAX_N = 100001;

int arr[MAX_N];
int tmp[MAX_N];
long long answer = 0;

void merge(int l, int m, int r) {
	int x = l; int y = m + 1; int k = l;

	while (x <= m || y <= r) {
		if (y > r || x <= m && arr[x] < arr[y]) {
			tmp[k] = arr[x++];
		}
		else {
			answer += (long long)(m - x + 1);
			tmp[k] = arr[y++];
		}
		k++;
	}

	for (int i = l; i <= r; i++) {
		arr[i] = tmp[i];
	}
}

void mergeSort(int l, int r) {
	if (l >= r) return;
	int mid = (l + r) / 2;
	mergeSort(l, mid);
	mergeSort(mid + 1, r);
	merge(l, mid, r);
}

int main()
{
	int T;
	cin >> T;

	for (int tc = 1; tc <= T; tc++) {
		int N;
		cin >> N;

		answer = 0;
		for (int i = 1; i <= N; i++) {
			cin >> arr[i];
		}
		
		mergeSort(1, N);
		cout << "#" << tc << " " << answer << endl;
	}
}