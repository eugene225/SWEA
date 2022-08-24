#include<iostream>
#include<cstring>

using namespace std;
typedef unsigned long long ll;

ll A, B, K;
ll DIV;

ll myMod(ll n) {

    if (n == 0) return 1;

    ll tmp = myMod(n >> 1);
    tmp *= tmp;
    tmp %= DIV;

    if (n & 1) {
        tmp <<= 1;
        tmp %= DIV;
    }

    return tmp;
}

ll run() {
    ll res = (A * myMod(K)) % DIV;
    return min(res, DIV - res);
}

int main(int argc, char** argv)
{
    int T;
    cin >> T;

    for (int tc = 1; tc <= T; ++tc) {
        cin >> A >> B >> K;
        DIV = A + B;
        cout << '#' << tc << ' ' << run() << '\n';
    }
    return 0;
}