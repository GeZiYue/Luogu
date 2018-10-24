#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<map>
using namespace std;
#define isNum(a) (a>='0'&&a<='9')
#define SP putchar (' ')
#define EL putchar ('\n')
#define inf 2147483647
#define N 10000005
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
typedef long long int ll;
template<class T1>inline void read(T1&);
template<class T1>inline void write(T1);
inline int count(int);
int x[N];
int bit[140000];
int main () {
    for (int i=1; i<(1<<16); ++i) {
        bit[i]=bit[i&(i-1)]+1;
    }
    int n, a, b, c, d;
    read(n);
    read(a);
    read(b);
    read(c);
    read(d);
    read(x[0]);
    int odd=0, even=0;
    for (int i=1; i<=n; ++i) {
        x[i]=((x[i-1]*1ll*a+b)%d*1ll*x[i-1]+c)%d;
        if (count(x[i])&1) {
            ++even;
        }else {
            ++odd;
        }
    }
    ll ans=even*1ll*odd;
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
int count(int x) {
    return bit[x>>16]+bit[x&((1<<16)-1)];
}
