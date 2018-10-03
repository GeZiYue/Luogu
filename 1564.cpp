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
#define N 2505
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T1>inline void read(T1&);
template<class T1>inline void write(T1);
int sum1[N], sum2[N], dp[N];
int main () {
    int n, m;
    read(n);
    read(m);
    for (R int i=1; i<=n; i++) {
        int a;
        read(a);
        sum1[i]=sum1[i-1]+(a==1);
        sum2[i]=sum2[i-1]+(a==2);
    }
    for (R int i=1; i<=n; i++) {
        dp[i]=i;
        for (R int j=1; j<i; j++) {
            if ((sum1[i]-sum1[j-1]==0) ||
            (sum2[i]-sum2[j-1]==0) ||
            (abs((sum1[i]-sum1[j-1])-(sum2[i]-sum2[j-1]))<=m)) {
                dp[i]=min(dp[i], dp[j-1]+1);
            }
        }
    }
    write(dp[n]);
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
