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
#define inf 2147483647
#define N 10005
#define M 105
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T1>inline void read(T1&);
template<class T1>inline void write(T1);
class Class {
public:
    int begin, end, abi;
    friend bool operator<(Class, Class);
}c[M];
int dp[N][M];
int lasmin[M];
int main () {
    int n, m, t;
    read(t);
    read(n);
    read(m);
    for (int i=1; i<=n; i++) {
        int begin, last, abi;
        read(begin);
        read(last);
        read(abi);
        c[i].begin=begin;
        c[i].end=begin+last;
        c[i].abi=abi;
    }
    sort(c+1, c+n+1);
    for (int i=1; i<=100; i++) {
        lasmin[i]=inf;
    }
    for (int i=1; i<=m; i++) {
        int need, last;
        read(need);
        read(last);
        lasmin[need]=min(lasmin[need], last);
    }
    memset(dp, -1, sizeof(dp));
    for (int i=0; i<=t; i++) {
        dp[i][1]=0;
    }
    int ans=0;
    for (int i=0, j=1; i<=t; i++) {
        if (c[j].end==i) {
            for (int k=1; k<=100; k++) {
                dp[i][c[j].abi]=max(dp[i][c[j].abi], dp[c[j].begin][k]);
            }
            for (int k=1; k<=c[j].abi; k++) {
                dp[i][k]=max(dp[i][k], dp[i][c[j].abi]);
            }
            j++;
        }
        for (int k=1; k<=100; k++) {
            if (i-lasmin[k]>=0&&dp[i-lasmin[k]][k]!=-1) {
                dp[i][k]=max(dp[i][k], dp[i-lasmin[k]][k]+1);
                ans=max(ans, dp[i][k]);
            }
        }
    }
    write(ans);
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
bool operator<(Class i, Class j) {
    return i.end<j.end;
}
