#include<iostream>
using namespace std;

int main() {
	int T;
	int X, Y, L;

	cin >> T;
	int* res = new int[T+1];

	for (int tc = 1; tc <= T; tc++) {
		cin >> X >> Y >> L;

		for (int i = 0; i < L; i++) {

			if (X > Y) {
				int tmp = Y;
				Y = X;
				X = tmp;
			}

			Y = Y - X;
			X = 2 * X;

		}
		res[tc] = min(X, Y);
	}

	for (int tc = 1; tc <= T; tc++)
	{
		cout << "#" << tc << " " << res[tc] << endl;

	}
}