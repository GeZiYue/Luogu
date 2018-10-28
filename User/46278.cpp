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
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
typedef long long int ll;
template<class T1>inline void read(T1&);
template<class T1>inline void write(T1);
int exgcd(int, int, int&, int&);
map<int, int>p;
int main () {
    ll b, k;
    read(b);
    read(k);
    int x, y;
    if (exgcd(b, k, x, y)!=1) {
        puts("Let's go Blue Jays!");
        return 0;
    }
    ll m=int(sqrt(b*1.0))+2;
    int t=1;
    for (int i=0; i<m; ++i) {
        if (!p[t]) {
            p[t]=i;
        }
        t=(t*k)%b;
    }
    ll D=1;
    for (int i=0; ; ++i) {
        exgcd(D, b, x, y);
        x=(x*1ll+b)%b;
        y=p[x];
        if (y!=0) {
            write(i*m+y);
            EL;
            return 0;
        }
        D=(D*t)%b;
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
int exgcd(int a, int b, int& x, int& y) {
    if (b==0) {
        x=1;
        y=0;
        return a;
    }
    int now=exgcd(b, a%b, y, x);
    y-=a/b*x;
    return now;
}
