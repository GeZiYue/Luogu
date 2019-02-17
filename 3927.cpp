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
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T>inline void read(T&);
template<class T>inline void write(const T&);
typedef long long int ll;
int main () {
    ll n, m;
    read(n), read(m);
    ll k=m;
    ll ans=inf*1ll*inf;
    for (ll i=2; i*i<=k; ++i) {
        if (k%i==0) {
            int cnt=0;
            while (k%i==0) {
                k/=i;
                ++cnt;
            }
            ll now=0;
            for (ll j=i; ; j*=i) {
                now+=n/j;
                if (n/j<i) {
                    break;
                }
            }
            ans=min(ans, now/cnt);
        }
    }
    if (k^1) {
        ll now=0;
        for (ll i=k; ; i*=k) {
            now+=n/i;
            if (n/i<k) {
                break;
            }
        }
        ans=min(ans, now);
    }
    write(ans), EL;
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
