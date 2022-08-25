package java;

import java.io.*;
import java.util.*;

class No20 {
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int T = Integer.parseInt(br.readLine());
        StringTokenizer st = null;
        for(int tc=1; tc<=T; tc++) {
            st = new StringTokenizer(br.readLine(), " ");
            int n = Integer.parseInt(st.nextToken());
            int k = Integer.parseInt(st.nextToken());
             
            int[][] object = new int[n+1][2];
            int[][] dp = new int[n+1][k+1];
            for(int i=1; i<=n; i++){
                st = new StringTokenizer(br.readLine(), " ");
                object[i][0] = Integer.parseInt(st.nextToken());    // 물건의 부피
                object[i][1] = Integer.parseInt(st.nextToken());    // 물건의 가치
            }
 
            for(int i=0; i<=k; i++){
                dp[0][i] = 0;
            }
 
            for(int i=1; i<=n; i++){
                for(int j=0; j<=k; j++){
                    if(object[i][0] > j)
                        dp[i][j] = dp[i-1][j];
                    else
                        dp[i][j] = Math.max(dp[i-1][j], dp[i-1][j - object[i][0]] + object[i][1]);
                }
            }
            System.out.println("#" + tc + " " + dp[n][k]);
        }
    }
}