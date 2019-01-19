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
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T>inline void read(T&);
template<class Fir, class... Res>void read(Fir&, Res&...);
template<class T>inline void write(const T&);
template<class Fir, class... Res>void write(const Fir&, const Res&...);
typedef long long int ll;
typedef const ll& cl;
ll exgcd(cl, cl, ll&, ll&);
int main () {
    ll x, y, m, n, l;
    read(x, y, m, n, l);
    if (m>n) {
        m^=n^=m^=n;
        x^=y^=x^=y;
    }
    ll s=x-y, v=n-m;
    ll t, a;
    ll k=exgcd(v, l, t, a);
    if (s%k) {
        puts("Impossible");
    }else {
        write((t*(s/k)+(l/k))%(l/k));
        EL;
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
template<class Fir, class... Res>void read(Fir& Fi, Res&... Re) {
    read(Fi);
    read(Re...);
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
template<class Fir, class... Res>void write(const Fir& Fi, const Res&... Re) {
    write(Fi);
    putchar(' ');
    write(Re...);
}
ll exgcd(cl a, cl b, ll& x, ll& y) {
    if (b==0) {
        x=1;
        y=0;
        return a;
    }
    ll k=exgcd(b, a%b, y, x);
    y-=(a/b)*x;
    return k;
}
