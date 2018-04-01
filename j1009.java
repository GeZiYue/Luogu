import java.util.Scanner;
import java.math.BigInteger;
public class j1009{
    public static void main(String[] args) {
        Scanner in=new Scanner(System.in);
        BigInteger ans,now;
        int n,i;
        ans=BigInteger.ZERO;
        now=BigInteger.ONE;
        n=in.nextInt();
        for(i=1;i<=n;i++){
            now=now.multiply(BigInteger.valueOf(i));
            ans=ans.add(now);
        }
        System.out.println(ans);
        in.close();
    }
}
