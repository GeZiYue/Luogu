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
#define isNum(a) (a >= '0'&&a <= '9')
#define SP putchar(' ')
#define EL putchar('\n')
#define inf 2147483647
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T>inline void read(T&);
template<class T>inline void write(const T&);
typedef const int& ci;
typedef long long ll;
typedef const long long& cll;
int exlucas(cll, cll, ci);
int main () {
    ll n, m;
    int p;
    read(n), read(m), read(p);
    write(exlucas(n, m, p)), EL;
    return 0;
}
template<class T>void read(T &Re) {
    register T k=0;
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
inline ll pow(cll a, ll b, int mod) {
    ll now=a, ans=1;
    while (b) {
        if (b&1) {
            ans=ans*now%mod;
        }
        now=now*now%mod;
        b>>=1;
    }
    return ans;
}
inline int exgcd(ci a, ci b, int &x, int &y) {
    if (!b) {
        x=1, y=0;
        return a;
    }
    int now=exgcd(b, a%b, y, x);
    y-=a/b*x;
    return now;
}
inline int inv(ci a, ci pk) {
    int x, y;
    exgcd(a, pk, x, y);
    return (x+pk)%pk;
}
inline int fact(cll n, ci p, ci pk) {
    if (n<=1) {
        return 1;
    }
    int ans=1;
    for (int i=2; i<=pk; ++i) {
        if (i%p) {
            ans=ans*1ll*i%pk;
        }
    }
    ans=pow(ans, n/pk, pk);
    for (int i=1; i<=n%pk; ++i) {
        if (i%p) {
            ans=ans*1ll*i%pk;
        }
    }
    return ans=ans*1ll*fact(n/p, p, pk)%pk;
}
inline ll get_q(cll n, ci pk) {
    ll ans=0;
    for (ll i=n; i; i/=pk) {
        ans+=i/pk;
    }
    return ans;
}
inline int get_c(cll n, cll m, ci p, ci pk) {
    ll factN=fact(n, p, pk), factM=fact(m, p, pk), factN_M=fact(n-m, p, pk);
    const ll sum=get_q(n, p)-get_q(m, p)-get_q(n-m, p);
    return factN*1ll*pow(p, sum, pk)*inv(factM, pk)%pk*inv(factN_M, pk)%pk;
}
inline int crt(ci c, ci m, ci pk) {
    return inv(m/pk, pk)*1ll*(m/pk)%m*c%m;
}
inline int exlucas(cll n, cll m, ci p) {
    int k=p;
    int ans=0;
    for (int i=2; i*i<=p; ++i) {
        if (k%i==0) {
            int pk=1;
            while (k%i==0) {
                pk*=i;
                k/=i;
            }
            ans=(ans+crt(get_c(n, m, i, pk), p, pk))%p;
        }
    }
    if (k>1) {
        ans=(ans+crt(get_c(n, m, k, k), p, k))%p;
    }
    return (ans%p+p)%p;
}
