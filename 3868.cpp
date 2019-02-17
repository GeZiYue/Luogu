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
#define N 15
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T>inline void read(T&);
template<class T>inline void write(const T&);
typedef __int128 ull;
ull exgcd(ull, ull, ull&, ull&);
ull a[N], m[N];
int main () {
    int n;
    read(n);
    for (int i=1; i<=n; ++i) {
        read(a[i]);
    }
    ull M=1;
    for (int i=1; i<=n; ++i) {
        read(m[i]);
        M*=m[i];
    }
    ull ans=0;
    for (int i=1; i<=n; ++i) {
        ull mi=M/m[i], x, y;
        exgcd(mi, m[i], x, y);
        ull ti=(x+m[i])%m[i];
        ans=(ans+a[i]%M*mi%M*ti%M)%M;
    }
    write((ans%M+M)%M), EL;
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
ull exgcd(ull a, ull b, ull &x, ull &y) {
    if (b==0) {
        x=1, y=0;
        return a;
    }
    ull now=exgcd(b, a%b, y, x);
    y-=a/b*x;
    return now;
}
