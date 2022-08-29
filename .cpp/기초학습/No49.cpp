#include <iostream>
#include <climits>
using namespace std;

long long n;
long long q;
long long a[100000];
long long seg[200000];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int tc = 1; tc <= T; tc++) {
        cout << "#" << tc << " ";
        cin >> n >> q;

        for (int i = 0; i < n; i++) {
            if (i & 1) {
                cin >> a[i];
                a[i] = -a[i];
            }
            else {
                cin >> a[i];
            }
        }

        for (int i = 0; i < n; i++) {
            seg[i + n] = a[i];
        }

        for (int i = n - 1; i > 0; i--) {
            seg[i] = seg[i << 1] + seg[(i << 1) | 1];
        }

        for (int i = 0; i < q; i++) {
            int cmd;
            cin >> cmd;

            if (cmd == 0) {
                long long i;
                long long x;
                cin >> i >> x;

                if (i & 1) {
                    seg[i += n] = -x;
                }
                else {
                    seg[i += n] = x;
                }

                while (i >>= 1) {
                    seg[i] = seg[i << 1] + seg[(i << 1) | 1];
                }
            }
            else if (cmd == 1) {
                int l;
                int r;
                cin >> l >> r;

                bool minus = false;
                if (l & 1) minus = true;

                long long ret = 0;
                for (l += n, r += n; l != r; l >>= 1, r >>= 1) {
                    if (l & 1) {
                        ret += seg[l++];
                    }
                    if (r & 1) {
                        ret += seg[--r];
                    }
                }

                if (minus) {
                    ret = -ret;
                }

                cout << ret << " ";
            }
            else {
                //wrong cmd
            }
        }
        cout << "\n";
    }

}