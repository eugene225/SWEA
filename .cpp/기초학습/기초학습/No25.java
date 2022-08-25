package 기초학습;

import java.io.*;
import java.util.*;

public class No25 {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int T = Integer.parseInt(br.readLine());
		for(int tc=1; tc<=T; tc++) {
			StringTokenizer st = new StringTokenizer(br.readLine());
			int N = Integer.parseInt(st.nextToken());
			int M = Integer.parseInt(st.nextToken());
			
			PriorityQueue<String> a = new PriorityQueue<String>();
			PriorityQueue<String> b = new PriorityQueue<String>();
			
			st  = new StringTokenizer(br.readLine());
			for(int i=0; i<N; i++) a.add(st.nextToken());
			
			st  = new StringTokenizer(br.readLine());
			for(int i=0; i<M; i++) b.add(st.nextToken());
			
			int count = 0;
			while(true) {
				if(a.isEmpty() || b.isEmpty()) break;
				
				String str1 = a.peek();
				String str2 = b.peek();
				
				int c = str1.compareTo(str2);
				if( c < 0 ) {
					a.poll();
					continue;
				}
				if( c > 0 ) {
					b.poll();
					continue;
				}
				
				count++;
				a.poll();
				b.poll();
			}
			System.out.println("#"+tc+" "+count);
		}
	}
}
