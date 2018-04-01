import java.util.Scanner;
import java.math.BigInteger;
public class j1303{
    public static void main(String args[]){
        Scanner in=new Scanner(System.in);
        BigInteger a,b;
        a=in.nextBigInteger();
        b=in.nextBigInteger();
        System.out.println(a.multiply(b));
        in.close();
    }
}
