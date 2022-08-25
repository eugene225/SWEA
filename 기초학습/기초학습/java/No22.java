package java;

import java.io.*;
import java.util.*;

public class No22 {
	
	private static int money;
	
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int T = Integer.parseInt(br.readLine());
		StringBuilder sb = new StringBuilder();
		
		for(int tc=1; tc<=T; tc++) {
			money = Integer.parseInt(br.readLine());
			int cnt50000=0;
			int cnt10000=0;
			int cnt5000=0;
			int cnt1000=0;
			int cnt500=0;
			int cnt100=0;
			int cnt50=0;
			int cnt10=0;
			
			cnt50000 = money/50000;
			money -= 50000*cnt50000;
			
			cnt10000 = money/10000;
			money -= 10000*cnt10000;
			
			cnt5000 = money/5000;
			money -= 5000*cnt5000;
			
			cnt1000 = money/1000;
			money -= 1000*cnt1000;
			
			cnt500 = money/500;
			money -= 500*cnt500;
			
			cnt100 = money/100;
			money -= 100*cnt100;
			
			cnt50 = money/50;
			money -= 50*cnt50;
			
			cnt10 = money/10;
			money -= 10*cnt10;
			
			sb.append("#"+tc+"\n"+cnt50000+" "+cnt10000+" "+cnt5000+" "+cnt1000+" "+cnt500+" "+cnt100+" "+cnt50+" "+cnt10+"\n");
		}
		
		System.out.print(sb);
	}
}
