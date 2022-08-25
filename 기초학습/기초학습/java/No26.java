package java;

import java.io.*;
import java.util.*;
 
public class No26{
	
	private static String B;
	private static String S;
	private static int[] P = new int[100001];
	
	private static void CalcP() {
		P[0] = 0;
		for(int i=1; i<=S.length();i++) {
			int j = P[i-1];
			while(j>0) {
				if(S.charAt(i) == S.charAt(j)) break;
				j = P[j-1];
			}
			if(S.charAt(i) == S.charAt(j)) P[i] = j+1;
			else P[i] = 0;
		}
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder sb = new StringBuilder();
		
		int T = Integer.parseInt(br.readLine());
		for(int tc = 1; tc <= T; tc++) {
			
			B = br.readLine();
			S = br.readLine();
			
			CalcP();
			
			int piv=0, cnt=0, ans=0;
			while(piv != B.length()) {
				if(B.charAt(piv) == S.charAt(cnt)) {
					if(cnt+1 != S.length()) {
						ans++;
						cnt = P[cnt];
					}else cnt++;
					piv++;
				}else if(cnt>0) cnt = P[cnt-1];
				else piv++;
			}
			sb.append("#").append(tc).append(" ").append(ans).append("\n");
		}
	}
}