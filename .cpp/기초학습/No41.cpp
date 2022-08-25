#include <iostream>
#include <cstring>
#include <cmath>

#define endl "\n"
using namespace std;

long long N, answer;

void Solution() {
	long long num = sqrt(N * 2);
	if (num * (num + 1) == N * 2) answer = num;
	else answer = -1;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int T;
	cin >> T;

	for (int tc = 1; tc <= T; tc++) {
		cin >> N;

		Solution();

		cout << "#" << tc << " " << answer << endl;
	}

	return 0;
}