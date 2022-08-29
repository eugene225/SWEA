#include <iostream>
#include <string>
#include <set>
using namespace std;

int T, K;
string str;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		set<string> sets;

		cin >> K >> str;
		for (int i = 0; i < str.size(); i++)
		{
			string tmp = { str[i] };
			sets.insert(tmp);

			for (int j = i + 1; j < str.size(); j++)
			{
				tmp += str[j];
				sets.insert(tmp);
			}
		}

		set<string>::iterator iter;
		int i = 1;
		bool flag = 0;

		cout << "#" << tc << " ";
		for (iter = sets.begin(), i = 1; iter != sets.end(); iter++, i++)
		{
			if (i == K) {
				cout << *iter << "\n";
				flag = 1;
				break;
			}
		}
		if (!flag) cout << "none\n";
	}
}