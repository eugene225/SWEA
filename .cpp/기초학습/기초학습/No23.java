package 기초학습;

import java.io.*;
import java.util.*;

public class No23 {
    public static void main(String args[]) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        
        int T;
        T = Integer.parseInt(br.readLine());
        for(int tc = 1; tc <= T; tc++)
        {
            int n = Integer.parseInt(br.readLine());
            
            int [][] students = new int [n][2];
            int [] visited = new int[201];
            
            for (int i=0;i<n;i++){
            	StringTokenizer st = new StringTokenizer(br.readLine());
                int s = (Integer.parseInt(st.nextToken())+1)/2;
                int e = (Integer.parseInt(st.nextToken())+1)/2;
                
                if (s>e){
                    int tmp = s;
                    s = e;
                    e = tmp;
                }
                
                students[i][0] = s;
                students[i][1] = e;
                
                int cnt = 0;
                for (int j=s; j<e+1; j++) {
                    visited[j] += 1;
                }
            }
            
            int time = 0;
            for (int i=0; i<201; i++){
                if (visited[i] > time){
                    time = visited[i];
                }
            }
            
            System.out.printf("#%d %d\n",tc,time);
        }
    }
}
