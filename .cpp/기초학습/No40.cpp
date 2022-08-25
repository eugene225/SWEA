#include<iostream>
using namespace std;

constexpr size_t MAX = 1000001;
bool *tf;
int N, P, M;

void search(int last);

int main() {
	int T;
	cin >> T;

	for (int tc = 1; tc <= T; tc++) {
		cin >> N >> P;
		
		tf = new bool[MAX];
		int last = 0;
		for (int i = 0; i < N; i++) {
			int tmp;
			cin >> tmp;
			last = max(last, tmp);
			tf[tmp] = true;
		}
		M = P + 1;
		search(last);
		cout << "#" << tc << " " << M << endl;
	}
}

void search(int last) {
	int start = 1;
	int end = 1;
	int num = 0;

	while (end < last + 1) {
		if (tf[end]) {
			num++;
			end++;
			M = max(M, num);
		}
		else {
			if (P == 0) {
				M = max(M, num);
				if (!tf[start]) P++;
				start++;
				num--;
			}
			else {
				P--;
				num++;
				end++;
			}
		}
	}
}