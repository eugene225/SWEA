#include <stdio.h>
#include <algorithm>
#include <string.h>

using namespace std;

int L, N;
struct PEAK {
    int begin; //피크 시작
    int end; //피크 끝
    int ADlong; //피크 지속시간
    int sum; //이 피크를 포함한 총 피크시간
};

PEAK peak[100000];

int search(int AD_end) //뭘 찾냐? AD_end 바로 전에 시작된 피크가 몇번째 피크인지
{
    //AD_end: 광고 끝나는 시각. 

    //(MIN, MAX]
    //..tttt/fff.. 파티션일때 마지막 true 찾기 이분탐색

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
    return l; //AD_end 바로 전에 시작된 피크의 index 리턴
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

        int max_val = 0; //광고와 피크시간대가 최대 겹치는 시간

        for (int i = 0; i < N; i++)
        {
            int AD_end = peak[i].begin + L; //광고가 peak[i]의 처음부터 시작해서 끝나는 시각
            int last_peak_idx = search(AD_end);

            //일단 마지막 피크 끝까지 광고를 했다고 치자. i==0 일때 주의
            int total = peak[last_peak_idx].sum - (peak[i].sum - peak[i].ADlong);

            //total 보정
            if (AD_end < peak[last_peak_idx].end) //사실 AD_end이 마지막 피크 도중에 있다면,
                total -= (peak[last_peak_idx].end - AD_end);

            max_val = max(max_val, total);
        }

        printf("#%d %d\n", t, max_val);
    }

    return 0;
}