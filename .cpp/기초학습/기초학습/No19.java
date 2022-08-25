package 기초학습;

import java.io.*;

public class No19 {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int T = Integer.parseInt(br.readLine());
		
		for(int tc=1;tc<=T;tc++) {
			int N = Integer.parseInt(br.readLine());
			
			int[][] DP = new int[2][N];
			
			int max = 0;
			
			for(int i=0;i<N;i++) DP[0][i] = Integer.parseInt(br.readLine());
			
			for(int i=0;i<N;i++) {
				DP[1][i] = 1;
				
				for(int j=0;j<i;j++) {
					if(DP[0][j] < DP[0][i] && DP[1][i] < DP[1][j]+1) {
						DP[1][i] = DP[1][j]+1;
					}
				}
				if(max < DP[1][i]) max = DP[1][i];
			}
			System.out.println("#"+tc+" "+max);
		}
	}
}
