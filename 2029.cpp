#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<queue>
#include<stack>
#include<set>
#include<map>
using namespace std;
#define isNum(a) (a>='0'&&a<='9')
#define SP putchar (' ')
#define EL putchar ('\n')
#define inf 2147483647
#define N 5005
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T1>inline void read(T1&);
template<class T1>inline void write(T1);
int s[N], b[N];
int dp[2][N];
int main () {
    int n, m;
    read(n);
    read(m);
    for (int i=1; i<=n; ++i) {
        read(s[i]);
    }
    for (int i=1; i<=n; ++i) {
        read(b[i]);
    }
    for (int i=1; i<=n; ++i) {
        dp[i&1][0]=dp[~i&1][0]-s[i];
        for (int j=1; j<=i; ++j) {
            if (j%m) {
                dp[i&1][j]=max(dp[~i&1][j-1]+s[i], dp[~i&1][j]-s[i]);
            }else {
                dp[i&1][j]=max(dp[~i&1][j-1]+s[i]+b[i], dp[~i&1][j]-s[i]);
            }
        }
    }
    int ans=0;
    for (int i=0; i<=n; ++i) {
        ans=max(ans, dp[n&1][i]);
    }
    write(ans);
    EL;
    return 0;
}
template<class T1>void read(T1 &r_e_a_d) {
    T1 k=0;
    char ch=getchar();
    int flag=1;
    while (!isNum(ch)) {
        if (ch=='-') {
            flag=-1;
        }
        ch=getchar();
    }
    while (isNum(ch) ) {
        k=(k<<1)+(k<<3)+ch-'0';
        ch=getchar();
    }
    r_e_a_d = flag*k;
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
