package 기초학습;

import java.io.*;
import java.util.*;

public class No24 {
	public static int result;
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int T;
		T=sc.nextInt();
				
		for(int test_case = 1; test_case <= T; test_case++)
		{
			int number=sc.nextInt();
			int cnt=sc.nextInt();
			
			char[] numbers = Integer.toString(number).toCharArray();
			result = 0;
			
			if(numbers.length<cnt) cnt = numbers.length;
			dfs(cnt,0, numbers);
				
			System.out.printf("#%d %d%n",test_case, result);
			
		}
		
	}
	
	public static void dfs(int cnt, int start, char[] numbers) {
		
		if(cnt==0) {
			int current = charArrToInt(numbers);
			if(current>result) {
				result = current;
			}
			return;
		}

		for(int i=start; i<numbers.length-1; ++i) {
			for(int j=i+1; j<numbers.length; ++j) {
				int src = Integer.parseInt(String.valueOf(numbers[i]));
				int trg = Integer.parseInt(String.valueOf(numbers[j]));
				
				numbers[i] = (char)(trg+'0');
				numbers[j] = (char)(src+'0');
				dfs(cnt-1, i, numbers);
				numbers[i] = (char)(src+'0');
				numbers[j] = (char)(trg+'0');
				
			}
		}
		
	}
	
	public static int charArrToInt(char[] numbers) {
		return Integer.parseInt(new String(numbers));
	}

}
