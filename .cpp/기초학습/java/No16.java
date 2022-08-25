package java;

import java.io.*;
import java.util.*;

class Node{
	private int x,y;
	
	Node(){
		
	}
	
	Node(int x, int y){
		this.x = x;
		this.y = y;
	}
}

public class No16 {
	
	private static int T;
	private static int n,a,b;
	private static int map[][];
	
	private static int dx[] = {0,0,1,-1};
	private static int dy[] = {1,-1,0,0};
	
	private void printMap() {
		System.out.println();
		for(int i=0;i<n;i++) {
			for(int j=0;j<n;j++) {
				System.out.print(map[i][j]+" ");
			}
			System.out.println();
		}
	}

}
