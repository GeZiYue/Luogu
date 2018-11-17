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
using namespace std;
#define isNum(a) (a>='0'&&a<='9')
#define SP putchar (' ')
#define EL putchar ('\n')
#define inf 2147483647
#define N 105
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T1>inline void read(T1&);
template<class T1>inline void write(T1);
int dp[N][N];
int a[N];
int bet[N][N];
int aft[N];
int main () {
    int n, m;
    read(n);
    read(m);
    for (int i=1; i<=n; ++i) {
        read(a[i]);
    }
    for (int i=1; i<=n; ++i) {
        for (int j=1; j<i; ++j) {
            dp[i][1]+=2*abs(a[i]-a[j]);
            for (int k=j+1; k<i; ++k) {
                bet[j][i]+=abs(2*a[k]-a[i]-a[j]);
            }
        }
        for (int j=i+1; j<=n; ++j) {
            aft[i]+=2*abs(a[i]-a[j]);
        }
    }
    int ans1=inf, ans2=inf;
    for (int i=1; i<=n; ++i) {
        for (int j=1; j<=min(i, ans1); ++j) {
            if (j^1) {
                dp[i][j]=inf;
                for (int k=1; k<i; ++k) {
                    if (dp[k][j-1]==inf) {
                        continue;
                    }
                    int now=dp[k][j-1]+bet[k][i];
                    dp[i][j]=min(dp[i][j], now);
                }
            }
            int k=dp[i][j]+aft[i];
            if (k<=m) {
                if (j<ans1) {
                    ans1=j;
                    ans2=k;
                }else {
                    if (j==ans1&&k<=ans2) {
                        ans2=k;
                    }
                }
            }
            if (dp[i][j]>m) {
                dp[i][j]=inf;
            }
        }
    }
    write(ans1), SP, write(ans2), EL;
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
