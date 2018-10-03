#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<vector>
using namespace std;
#define isNum(a) (a>='0'&&a<='9')
#define SP putchar (' ')
#define EL putchar ('\n')
#define R register
#define inf 2147483647
#define N 85
#define M 50
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T1>inline void read(T1&);
template<class T1>inline void write(T1);
class BigInteger {
private:
    int Int[M];
    int len;
    void AddLen(int k) {
        len+=k;
    }
public:
    int& operator[](int);
    BigInteger operator+(BigInteger);
    BigInteger operator*(int);
    bool operator>(BigInteger);
    void Write();
    friend BigInteger GetTwoPower(int);
    BigInteger() {
        len=0;
        memset(Int, 0, sizeof(Int));
    }
    BigInteger(int k) {
        len=0;
        memset(Int, 0, sizeof(Int));
        while (k) {
            Int[++len]=k%10;
            k/=10;
        }
    }
};
BigInteger GetTwoPower(int);
BigInteger max(BigInteger, BigInteger);
int a[N];
BigInteger dp[N][N];
int main () {
    int n, m;
    read(n);
    read(m);
    BigInteger ans;
    while (n--) {
        BigInteger k=GetTwoPower(m);
        for (R int i=1; i<=m; i++) {
            read(a[i]);
            dp[i][i]=k*a[i];
        }
        for (R int l=2; l<=m; l++) {
            k=GetTwoPower(m-l+1);
            for (R int i=1; i+l-1<=m; i++) {
                R int j=i+l-1;
                dp[i][j]=max(dp[i][j-1]+k*a[j], dp[i+1][j]+k*a[i]);
            }
        }
        ans=ans+dp[1][m];
    }
    ans.Write();
    EL;
    return 0;
}
template<class T1>void read(T1 &r_e_a_d) {
    T1 k=0;
    char ch=getchar();
    int flag=1;
    while(!isNum(ch)) {
        if (ch=='-') {
            flag=-1;
        }
        ch=getchar();
    }
    while(isNum(ch) ) {
        k=(k<<1)+(k<<3)+ch-'0';
        ch=getchar();
    }
    r_e_a_d=flag*k;
}
template<class T1>void write(T1 w_r_i_t_e) {
    if (w_r_i_t_e<0) {
        putchar('-');
        write(-w_r_i_t_e);
    }else {
        if (w_r_i_t_e<10) {
            putchar(w_r_i_t_e+'0');
        }else {
            write(w_r_i_t_e/10);
            putchar((w_r_i_t_e%10)+'0');
        }
    }
}
int& BigInteger::operator[](int k) {
    return Int[k];
}
BigInteger BigInteger::operator+(BigInteger k) {
    BigInteger ans;
    ans.AddLen(max(len, k.len));
    int num=0;
    for (R int i=1; i<=max(len, k.len); i++) {
        ans[i]=Int[i]+k.Int[i]+num;
        num=ans[i]/10;
        ans[i]%=10;
    }
    if (num) {
        ans.AddLen(1);
        ans[ans.len]=1;
    }
    return ans;
}
BigInteger BigInteger::operator*(int k) {
    BigInteger ans(*this);
    int num=0;
    for (R int i=1; i<=ans.len; i++) {
        ans[i]*=k;
        ans[i]+=num;
        num=ans[i]/10;
        ans[i]%=10;
    }
    while (num) {
        ans.AddLen(1);
        ans[ans.len]=num%10;
        num/=10;
    }
    return ans;
}
bool BigInteger::operator>(BigInteger k) {
    if (len>k.len) {
        return true;
    }else {
        if (len<k.len) {
            return false;
        }
    }
    for (R int i=len; i>=1; i--) {
        if (Int[i]>k.Int[i]) {
            return true;
        }else {
            if (Int[i]<k.Int[i]) {
                return false;
            }
        }
    }
    return false;
}
BigInteger GetTwoPower(int k) {
    BigInteger ans(2);
    for (R int i=2; i<=k; i++) {
        ans=ans*2;
    }
    return ans;
}
void BigInteger::Write() {
    for (R int i=len; i>=1; i--) {
        write(Int[i]);
    }
}
BigInteger max(BigInteger a, BigInteger b) {
    if (a>b) {
        return a;
    }
    return b;
}
