#include <stdio.h>
#include <queue>

using namespace std;

#define MOD 20171109

int main(int argc, char** argv) {
    priority_queue<int, vector<int>, greater<int>> bigger;
    priority_queue<int, vector<int>, less<int>> smaller;

    int mid, N, A, B, answer;
    int tc, T;
    scanf("%d", &T);

    for (tc = 1; tc <= T; tc++) {
        bigger = priority_queue<int, vector<int>, greater<int>>();
        smaller = priority_queue<int, vector<int>, less<int>>();

        answer = 0;
        scanf("%d %d", &N, &mid);

        for (int i = 0; i < N; i++) {
            scanf("%d %d", &A, &B);

            mid > A ? smaller.push(A) : bigger.push(A);
            mid > B ? smaller.push(B) : bigger.push(B);

            while (smaller.size() > bigger.size()) {
                bigger.push(mid);
                mid = smaller.top();
                smaller.pop();
            }

            while (bigger.size() > smaller.size()) {
                smaller.push(mid);
                mid = bigger.top();
                bigger.pop();
            }

            answer = (answer + mid) % MOD;
        }
        printf("#%d %d\n", tc, answer);
    }
    return 0;
}