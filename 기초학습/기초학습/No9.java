import java.io.*;
import java.util.*;

public class middle{
    public static char tree[];
    public static int len;

    public static void inOrder(int cur){
        if(cur>len) return;
        inOrder(cur*2);
        System.out.print(tree[cur]);
        inOrder(cur*2+1);
    }

    public static void main(String[] args) throws Exception{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st;

        for(int test_case=1;test_case<=10;test_case++){
            len = Integer.parseInt(br.readLine());
            tree = new char[len+1];

            for(int i=1;i<=len;i++){
                st = new StringTokenizer(br.readLine());
                int node = Integer.parseInt(st.nextToken());
                tree[node] = st.nextToken().charAt(0);
            }

            System.out.print("#"+test_case+" ");
            inOrder(1);
            System.out.println();
        }
    }
}