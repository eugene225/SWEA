package java;

import java.io.*;

public class No17 {
	
	static int N, res, mCnt[][];
	static char map[][];
	//static int[] dx = {-1, -1, 0, 1, 1, 1, 0, -1};
	//static int[] dy = {0, 1, 1, 1, 0, -1, -1, -1};
	
	public static void main(String[] args) throws IOException{
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int T = Integer.parseInt(br.readLine());
		
		for(int test_case=1;test_case<=T;test_case++) {
			N = Integer.parseInt(br.readLine());
			res = 0;
			map = new char[N][N];
			mCnt = new int[N][N];
			
			for(int i=0;i<N;i++) {
				map[i] = br.readLine().toCharArray();
			}
			
			countMine();
			
			for(int i=0;i<N;i++) {
				for(int j=0;j<N;j++) {
					if(mCnt[i][j] == 0 && map[i][j] != '*') {
						click(i, j);
						res++;
					}
				}
			}
			
			for(int i=0;i<N;i++) {
				for(int j=0;j<N;j++) {
					if(mCnt[i][j]>0 && map[i][j] != '*') {
						res++;
					}
				}
			}
			System.out.println("#"+test_case+" "+res);
		}
	}
	
	private 
	
}
