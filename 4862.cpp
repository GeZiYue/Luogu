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
#define N 2005
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T1>inline void read(T1&);
template<class T1>inline void write(T1);
int DFS(int);
int f[N];
int a, b;
int main () {
    int t;
    read(a);
    read(b);
    read(t);
    if (a==2&&b==1) {
        while (t--) {
            long long int n;
            read(n);
            long long int ans=3, now=3, f=1, f2=1;
            if (n==1) {
                write(0);
                EL;
                continue;
            }
            if (n==2) {
                write(2);
                EL;
                continue;
            }
            if (n==3) {
                write(3);
                EL;
                continue;
            }
            while (now<n) {
                f=f+f2;
                f2=f-f2;
                now+=f;
                ++ans;
            }
            write(ans);
            EL;
        }
    }else {
        memset(f, -1, sizeof(f));
        f[0]=f[1]=0;
        f[2]=a;
        while (t--) {
            int n;
            read(n);
            write(DFS(n));
            EL;
        }
    }
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
int DFS(int x) {
    if (f[x]!=-1) {
        return f[x];
    }
    int ans=inf;
    for (int i=1; i<x; ++i) {
        ans=min(ans, max(DFS(i)+a, DFS(x-i)+b));
    }
    return f[x]=ans;
}
