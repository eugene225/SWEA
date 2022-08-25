package java;

import java.io.*;
import java.util.*;

public class No12 {
	
	private static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	private static int T;
	private static int V,E,a,b;
	private static int size;
	private static Node[] tree;
	private static boolean[] visited;
	private static StringBuilder sb = new StringBuilder();
	
	public static void main(String args[]) throws Exception{
		T = Integer.parseInt(br.readLine());
		
		for(int test_case=1; test_case<=T; test_case++) {
			StringTokenizer st = new StringTokenizer(br.readLine());
			V = Integer.parseInt(st.nextToken());
			E = Integer.parseInt(st.nextToken());
			a = Integer.parseInt(st.nextToken());
			b = Integer.parseInt(st.nextToken());
			
			tree = new Node[V+1];
			visited = new boolean[V+1];
			
			for(int i=1;i<=V;i++) {
				tree[i] = new Node(i);
			}
			
			//tree create
			st = new StringTokenizer(br.readLine());
			for(int i=0;i<E;i++) {
				int parent = Integer.parseInt(st.nextToken());
				int child = Integer.parseInt(st.nextToken());
				if(tree[parent].left == 0) tree[parent].left = child;
				else tree[parent].right = child;
				tree[child].parent = parent;
			}
			
			int commonParent = 1;
			while(true) {
				if(a!=1) {
					int parent = tree[a].parent;
					if(visited[parent]) {
						commonParent = parent;
						break;
					}
					visited[parent] = true;
					a = parent;
				}
				
				if(b!=1) {
					int parent = tree[b].parent;
					if(visited[parent]) {
						commonParent = parent;
						break;
					}
					visited[parent] = true;
					b = parent;
				}
			}
			size = 0;
			getNode(tree[commonParent]);
			sb.append("#").append(test_case).append(" ").append(commonParent).append(" ").append(size).append("\n");
		}
		System.out.print(sb);
	}
	
	static void getNode(Node node) {
		size++;
		if(node.left != 0) getNode(tree[node.left]);
		if(node.right != 0) getNode(tree[node.right]);
	}

	private static class Node{
		int data;
		int left,right,parent;
		
		Node(int data){
			this.data = data;
			this.parent = 0;
			this.right = 0;
			this.left = 0;
		}
	}
}
