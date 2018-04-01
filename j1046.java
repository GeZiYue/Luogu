import java.util.Scanner;
public class j1046{
    public static void main(String[] args){
        Scanner in=new Scanner(System.in);
        int[]a=new int[105];
        int n=10,m,i,ans=0;
        for(i=1;i<=n;i++){
            a[i]=in.nextInt();
        }
        m=in.nextInt();
        m+=30;
        for(i=1;i<=n;i++){
            if(a[i]<=m){
                ans++;
            }
        }
        System.out.println(ans);
        in.close();
    }
}
