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
#define N 100005
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T>inline void read(T&);
template<class Fir, class... Res>void read(Fir&, Res&...);
template<class T>inline void write(const T&);
template<class Fir, class... Res>void write(const Fir&, const Res&...);
bool Get(int, int);
int Pow2(int);
int op[N], a[N];
int main () {
    int n, m;
    read(n, m);
    for (int i=1; i<=n; ++i) {
        string str;
        cin>>str;
        if (str=="AND") {
            op[i]=1;
        }else {
            if (str=="OR") {
                op[i]=2;
            }else {
                op[i]=3;
            }
        }
        read(a[i]);
    }
    int ans=0;
    for (int i=31; i>=1; --i) {
        bool a1=false, a2=true;
        for (int j=1; j<=n; ++j) {
            if (op[j]==1) {
                a1&=Get(a[j], i);
                a2&=Get(a[j], i);
            }else {
                if (op[j]==2) {
                    a1|=Get(a[j], i);
                    a2|=Get(a[j], i);
                }else {
                    a1^=Get(a[j], i);
                    a2^=Get(a[j], i);
                }
            }
        }
        if (Pow2(i-1)<=m) {
            if (!a1&&a2) {
                m-=Pow2(i-1);
            }
            if (a1|a2) {
                ans+=Pow2(i-1);
            }
        }else {
            if (a1) {
                ans+=Pow2(i-1);
            }
        }
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
bool Get(int a, int k) {
    return (a>>(k-1))&1;
}
int Pow2(int a) {
    return 1<<a;
}
