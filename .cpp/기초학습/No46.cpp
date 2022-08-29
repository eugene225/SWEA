#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int T, K;

int main(void) {

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> T;

	string s;
	for (int tc = 1; tc <= T; tc++) {
		cin >> K >> s;

		vector<string> list;
		string tmp = "";
		for (int i = s.length() - 1; i >= 0; i--) {
			tmp = s[i] + tmp;
			list.push_back(tmp);
		}

		sort(list.begin(), list.end());

		cout << "#" << tc << " " << list[K - 1] << "\n";
	}


	return 0;
}