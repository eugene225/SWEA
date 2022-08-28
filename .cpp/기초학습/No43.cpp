#include <stdio.h>
#include <algorithm>
#include <string.h>

using namespace std;

int L, N;
struct PEAK {
    int begin; //��ũ ����
    int end; //��ũ ��
    int ADlong; //��ũ ���ӽð�
    int sum; //�� ��ũ�� ������ �� ��ũ�ð�
};

PEAK peak[100000];

int search(int AD_end) //�� ã��? AD_end �ٷ� ���� ���۵� ��ũ�� ���° ��ũ����
{
    //AD_end: ���� ������ �ð�. 

    //(MIN, MAX]
    //..tttt/fff.. ��Ƽ���϶� ������ true ã�� �̺�Ž��

    int l = 0;
    int r = N - 1;

    l--;

    while (l != r)
    {
        int mid = r - (r - l) / 2;

        if (peak[mid].begin < AD_end) //true
            l = mid;
        else //false
            r = mid - 1;
    }
    return l; //AD_end �ٷ� ���� ���۵� ��ũ�� index ����
}

int main()
{
    int TC;
    scanf("%d", &TC);

    for (int t = 1; t <= TC; t++)
    {
        memset(peak, 0, sizeof(peak));
        scanf("%d %d", &L, &N);

        int temp = 0;
        for (int i = 0; i < N; i++)
        {
            int a, b;
            scanf("%d %d", &a, &b);

            temp += (b - a);

            peak[i].begin = a;
            peak[i].end = b;
            peak[i].ADlong = b - a;
            peak[i].sum = temp;
        }

        int max_val = 0; //����� ��ũ�ð��밡 �ִ� ��ġ�� �ð�

        for (int i = 0; i < N; i++)
        {
            int AD_end = peak[i].begin + L; //���� peak[i]�� ó������ �����ؼ� ������ �ð�
            int last_peak_idx = search(AD_end);

            //�ϴ� ������ ��ũ ������ ���� �ߴٰ� ġ��. i==0 �϶� ����
            int total = peak[last_peak_idx].sum - (peak[i].sum - peak[i].ADlong);

            //total ����
            if (AD_end < peak[last_peak_idx].end) //��� AD_end�� ������ ��ũ ���߿� �ִٸ�,
                total -= (peak[last_peak_idx].end - AD_end);

            max_val = max(max_val, total);
        }

        printf("#%d %d\n", t, max_val);
    }

    return 0;
}