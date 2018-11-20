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
#define M 4000005
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T1>inline void read(T1&);
template<class T1>inline void write(T1);
int cnt[M];
int sum[M];
int dp[M];
int main () {
    int n, m;
    read(n);
    read(m);
    int maxi=0;
    for (int i=1; i<=n; ++i) {
        int a;
        read(a);
        maxi=max(maxi, a);
        ++cnt[a], sum[a]+=a;
    }
    for (int i=1; i<=maxi+m; ++i) {
        cnt[i]+=cnt[i-1], sum[i]+=sum[i-1];
    }
    for (int i=1; i<maxi+m; ++i) {
        if (i>=m&&cnt[i]==cnt[i-m]) {
            dp[i]=dp[i-m];
            continue;
        }
        dp[i]=cnt[i]*i-sum[i];
        for (int j=i-m; j>=max(i-(m<<1)+1, 0); --j) {
            dp[i]=min(dp[i], dp[j]+(cnt[i]-cnt[j])*i-(sum[i]-sum[j]));
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
