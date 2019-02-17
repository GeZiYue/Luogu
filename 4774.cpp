#include <iostream>
#include <cstdio>
#include <cmath>
#include <string>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#define isNum(a) (a >= '0' && a <= '9')
#define SP putchar(' ')
#define EL putchar('\n')
#define inf 2147483647
#define File(a) freopen(a ".in", "r", stdin), freopen(a ".out", "w", stdout)

template <class T>
inline void read(T &);
template <class T>
inline void write(const T &);

const int N = 100005;
typedef const int &ci;
typedef long long int ll;
typedef const long long &cll;

ll gcd(cll, cll);
ll exgcd(cll, cll, ll&, ll&);
inline ll inv(cll, cll);
ll mult(cll, ll, cll);
inline bool excrt(ci);

ll a[N];
ll m[N];
ll w[N];
ll c[N];

int main() {
    int t;
    read(t);
    while (t--) {
        int n, r;
        read(n), read(r);
        for (int i = 1; i <= n; ++i) {
            read(c[i]);
        }
        bool flag=1;
        for (int i = 1; i <= n; ++i) {
            read(m[i]);
            flag &= (m[i] == 1);
        }
        for (int i = 1; i <= n; ++i) {
            read(w[i]);
        }
        std::multiset<ll> s;
        ll maxi=0;
        for (int i = 1; i <= r; ++i) {
            ll now;
            read(now);
            s.insert(now);
        }
        for (int i = 1; i <= n; ++i) {
            std::multiset<ll>::iterator it = s.upper_bound(c[i]);
            if (it != s.begin()) {
                --it;
            }
            a[i] = *it;
            maxi=std::max(maxi, (c[i] + a[i] - 1) / a[i]);
            s.erase(it);
            s.insert(w[i]);
        }
        if (flag) {
            write(maxi), EL;
            goto con;
        }
        for (int i = 1; i <= n; ++i) {
            ll k1 = gcd(a[i], c[i]);
            ll k2 = gcd(k1, m[i]);
            a[i] /= k1;
            c[i] /= k1;
            m[i] /= k2;
            c[i] = mult(c[i], inv(a[i], m[i]), m[i]);
        }
        for (int i = 2; i <= n; ++i) {
            if (!excrt(i)) {
                puts("-1");
                goto con;
                break;
            }
        }
        while (c[n] < maxi) {
            c[n] += m[n];
        }
        write(c[n]), EL;
        con:;
    }
    return 0;
}

template <class T>
void read(T &Re) {
    register T k = 0;
    char ch = getchar();
    int flag = 1;
    while (!isNum(ch)) {
        if (ch == '-') {
            flag = -1;
        }
        ch = getchar();
    }
    while (isNum(ch)) {
        k = (k << 1) + (k << 3) + ch - '0';
        ch = getchar();
    }
    Re = flag * k;
}
template <class T>
void write(const T &Wr) {
    if (Wr < 0) {
        putchar('-');
        write(-Wr);
    } else {
        if (Wr < 10) {
            putchar(Wr + '0');
        } else {
            write(Wr / 10);
            putchar((Wr % 10) + '0');
        }
    }
}

ll gcd(cll a, cll b) {
    return !b ? a : gcd(b, a % b);
}
ll mult(cll a, ll b, cll p) {
    if (b<0) {
        return -mult(a, -b, p);
    }
    ll ans = 0, now = a;
    while (b) {
        if (b & 1) {
            ans = (ans + now) % p;
        }
        now = (now + now) % p;
        b >>= 1;
    }
    return ans;
}
ll exgcd(cll a, cll b, ll &x, ll &y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    ll now = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return now;
}
ll inv(cll a, cll b) {
    ll x, y;
    exgcd(a, b, x, y);
    return (x + b) % b;
}
bool excrt(ci i) {
    const ll c1 = c[i - 1], c2 = c[i], m1 = m[i - 1], m2 = m[i];
    const ll k = gcd(m1, m2);
    if ((c2 - c1) % k) {
        return false;
    }
    m[i] = m1 / k * m2;
    c[i] = (mult(mult((c2 - c1) / k, inv(m1 / k, m2 / k), m[i]), m1, m[i]) + c1) % m[i];
    c[i] = (c[i] + m[i]) % m[i];
    return true;
}
