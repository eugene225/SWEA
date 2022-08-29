#include<iostream>
#include<string>

#define MAX 100001

using namespace std;

struct node {
    int min;
    int max;
    int x;

    void node_init() {
        min = max = x;
    }
};

struct segment_tree {
    int size;
    int arr[MAX];
    node segtree[2 * MAX];

    void init() {
        for (int i = 0; i < size; ++i) {
            segtree[i + size].x = arr[i];
            segtree[i + size].node_init();
        }

        for (int i = size - 1; i != 0; --i) {
            segtree[i].min = segtree[i << 1].min < segtree[i << 1 | 1].min ? segtree[i << 1].min : segtree[i << 1 | 1].min;
            segtree[i].max = segtree[i << 1].max > segtree[i << 1 | 1].max ? segtree[i << 1].max : segtree[i << 1 | 1].max;
            segtree[i].x = segtree[i].max - segtree[i].min;
        }
    }

    void update(int i, int x) {
        segtree[i + size].x = x;
        segtree[i + size].node_init();
        i += size;

        while (i >>= 1) {
            segtree[i].min = segtree[i << 1].min < segtree[i << 1 | 1].min ? segtree[i << 1].min : segtree[i << 1 | 1].min;
            segtree[i].max = segtree[i << 1].max > segtree[i << 1 | 1].max ? segtree[i << 1].max : segtree[i << 1 | 1].max;
            segtree[i].x = segtree[i].max - segtree[i].min;
        }
    }

    int rangeQuery(int l, int r) {

        int min = 100000001, max = -1;

        for (l += size, r += size; l != r; l >>= 1, r >>= 1) {
            if (l & 1) {
                max = segtree[l].max > max ? segtree[l].max : max;
                min = segtree[l].min < min ? segtree[l].min : min;
                l++;
            }
            if (r & 1) {
                --r;
                max = segtree[r].max > max ? segtree[r].max : max;
                min = segtree[r].min < min ? segtree[r].min : min;
            }
        }
        return max - min;
    }
};

segment_tree st;

int main(int argc, char** argv)
{
    int T;
    int arrLen, queryCnt, op;
    int ans;

    scanf("%d", &T);

    for (int tc = 1; tc <= T; ++tc)
    {
        scanf("%d %d", &arrLen, &queryCnt);
        st.size = arrLen;

        for (int i = 0; i < arrLen; i++) {
            scanf("%d", &st.arr[i]);
        }


        st.init();
        int a, x, l, r;
        printf("#%d ", tc);

        for (int i = 0; i < queryCnt; i++) {
            scanf("%d", &op);

            switch (op) {
            case 0:
                scanf("%d %d", &a, &x);
                st.update(a, x);
                break;
            case 1:
                scanf("%d %d", &l, &r);
                ans = st.rangeQuery(l, r);
                printf("%d ", ans);
                break;
            }
        }
        printf("\n");

    }
    return 0;
}