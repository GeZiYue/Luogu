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
#define N 505
#define M 100505
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T1>inline void read(T1&);
template<class T1>inline void write(T1);
int a[M];
int b[N];
int c[N];
int dp[M];
int main () {
    int n, m;
    read(n);
    read(m);
    for (int i=1; i<=n; ++i) {
        read(b[i]);
    }
    sort(b+1, b+n+1);
    c[1]=m;
    ++a[c[1]];
    int maxi=0;
    int mini=c[1];
    for (int i=2; i<=n; ++i) {
        if (b[i]>b[i-1]+(m<<1)) {
            c[i]=c[i-1]+(m<<1);
        }else {
            c[i]=c[i-1]+b[i]-b[i-1];
        }
        ++a[c[i]];
        maxi=max(maxi, c[i]);
    }
    memset(dp, 0, sizeof(dp));
    dp[mini]=0;
    for (int i=mini+1; i<maxi+m; ++i) {
        int now=0;
        for (int j=i-1; j>i-m; --j) {
            now+=(i-j)*a[j];
        }
        dp[i]=inf;
        for (int j=i-m; j>=max(0, i-(m<<1)); --j) {
            dp[i]=min(dp[i], dp[j]+now);
            now+=(i-j)*a[j];
        }
    }
    int ans=inf;
    for (int i=maxi; i<maxi+m; ++i) {
        ans=min(ans, dp[i]);
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
    while (isNum(ch)) {
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
