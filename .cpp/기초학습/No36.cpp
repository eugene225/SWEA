#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

bool compare(string A, string B) {
    if (A.length() < B.length())
        return true;
    else if (A.length() == B.length())
        return A < B;
    else if (A.length() > B.length())
        return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int T, N;
    string name;
    vector<string> names;

    cin >> T;

    for (int tc = 1; tc <= T; tc++) {
        cin >> N;
        names.resize(N);

        for (int i = 0; i < N; i++) {
            cin >> names[i];
        }
        sort(names.begin(), names.end(), compare);

        cout << "#" << tc << "\n";
        cout << names[0] << "\n";
        for (int i = 1; i < names.size(); i++) {
            if (names[i] != names[i - 1]) cout << names[i] << "\n";
        }
    }
    return 0;
}