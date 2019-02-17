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
#define SP putchar(' ')
#define EL putchar('\n')
#define inf 2147483647
#define N 100005
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T>inline void read(T&);
template<class T>inline void write(const T&);
typedef const int& ci;
int lucas(ci, ci, ci);
int fac[N];
int inv[N];
int main () {
    int t;
    read(t);
    while (t--) {
        int n, m, p;
        read(n), read(m), read(p);
        fac[0]=fac[1]=inv[0]=inv[1]=1;
        for (int i=2; i<=n+m; ++i) {
            fac[i]=fac[i-1]*1ll*i%p;
            inv[i]=(p-p/i)*1ll*inv[p%i]%p;
        }
        for (int i=2; i<=n+m; ++i) {
            inv[i]=inv[i-1]*1ll*inv[i]%p;
        }
        write(lucas(n+m, m, p)), EL;
    }
    return 0;
}
template<class T>void read(T &Re) {
    T k=0;
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
    Re=flag*k;
}
template<class T>void write(const T& Wr) {
    if (Wr<0) {
        putchar('-');
        write(-Wr);
    }else {
        if (Wr<10) {
            putchar(Wr+'0');
        }else {
            write(Wr/10);
            putchar((Wr%10)+'0');
        }
    }
}
int lucas(ci n, ci m, ci p) {
    if (m==0||n==m) {
        return 1;
    }
    if (n<m) {
        return 0;
    }
    if (n<p) {
        return fac[n]*1ll*inv[m]%p*1ll*inv[n-m]%p;
    }
    return lucas(n/p, m/p, p)*1ll*lucas(n%p, m%p, p)%p;
}
