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
#define N 10005
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T>inline void read(T&);
template<class Fir, class... Res>void read(Fir&, Res&...);
template<class T>inline void write(const T&);
template<class Fir, class... Res>void write(const Fir&, const Res&...);
class Line {
public:
    int v;
    bool mod;
}a[N<<1];
int now[2];
int main () {
    int n, m;
    read(n, m);
    --n, --m;
    for (int i=1; i<=n; ++i) {
        read(a[i].v);
        a[i].mod=1;
    }
    for (int i=n+1; i<=n+m; ++i) {
        read(a[i].v);
        a[i].mod=0;
    }
    sort(a+1, a+n+m+1, [](const Line& a, const Line& b) {
        return a.v>b.v;
    });
    int ans=0;
    for (int i=1; i<=n+m; ++i) {
        ans+=a[i].v*(now[!a[i].mod]+1);
        ++now[a[i].mod];
    }
    write(ans);
    EL;
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
