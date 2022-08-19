#define MOD 1000000007

#include <iostream>
#include <string>
#include <cstring>

using namespace std;

long long DP[1001][16];

int main(int argc, char** argv)
{
	int test_case;
	int T;

	cin >> T;
	
	for (test_case = 1; test_case <= T; ++test_case)
	{
		string in; cin >> in;
		int len = in.length();
		memset(DP, 0, sizeof(DP));

		for (int i = 0; i < len; i++)
		{
			int admin = 1 << (in[i] - 'A');

			for (int j = 1; j < 16; j++)
			{
				if (i == 0)
				{
					if ((j & admin) != 0 && (j & 1) != 0)
					{
						DP[i][j] = 1;
					}
				}
				else
					if (DP[i - 1][j] != 0)
						for (int k = 1; k < 16; k++)
							if ((k & j) != 0 && (k & admin) != 0)
							{
								DP[i][k] += DP[i - 1][j];
								DP[i][k] %= MOD;
							}
			}
		}

		long long out = 0;
		for (int i = 1; i < 16; i++)
		{
			out += DP[len - 1][i];
			out %= MOD;
		}

		cout << '#' << test_case << ' ' << out << '\n';
	}
	return 0;
}