#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <complex>
#include <cstdio>
#include <string>
#include <vector>
#include <bitset>
#include <cmath>
#include <queue>
#include <stack>
#include <ctime>
#include <set>
#include <map>

#define isNum(a) (a >= '0' && a <= '9')
#define SP putchar(' ')
#define EL putchar('\n')
#define File(a) freopen(a ".in", "r", stdin), freopen(a ".out", "w", stdout)

template<class T>
void read(T&);
template<class T>
void write(const T&);

typedef long long ll;
typedef unsigned long long ull;
typedef const long long & cll;
typedef const int & ci;
typedef std::pair<int, int> pii;
const int iinf = 2147483647;
const ll llinf = 9223372036854775807ll;
using std::min;
using std::max;
using std::abs;
using std::sort;

const int p[] = {6, 2, 3, 7, 11, 59, 61};

ll mul(ll, ll, ll);
ll pow(ll, ll, ll);
bool miller_rabin(ll);
ll gcd(ll, ll);
ll f(ll, ll, ll);
ll pollard_rho(ll);
void fac(ll);

ll ans;

int main () {
  srand(time(NULL));
  int t;
  read(t);
  while (t--) {
    ll n;
    read(n);
    ans = 1;
    fac(n);
    if (ans == n) {
      puts("Prime");
    } else {
      write(ans), EL;
    }
  }
  return 0;
}

template<class T>
inline void read(T &Re) {
  T k = 0;
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
template<class T>
inline void write(const T &Wr) {
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

ll mul(ll a, ll b, ll m) {
  ll ans = a * b - (ll)((long double)a * b / m + 0.5) * m;
  return ans < 0 ? ans + m : ans;
}
ll pow(ll a, ll b, ll m) {
  ll ans = 1, now = a % m;
  while (b) {
    if (b & 1) {
      ans = mul(ans, now, m);
    }
    now = mul(now, now, m);
    b >>= 1;
  }
  return ans;
}
bool miller_rabin(ll n) {
  if (n <= 1) {
    return false;
  }
  for (int i = 1; i <= p[0]; ++i) {
    if (n % p[i] == 0) {
      return n == p[i];
    }
  }
  ll m = n - 1;
  int r = 0;
  while ((~m) & 1) {
    ++r;
    m >>= 1;
  }
  for (int i = 1; i <= p[0]; ++i) {
    ll x = pow(p[i], m, n);
    for (int j = 0; j < r; ++j) {
      ll y = mul(x, x, n);
      if (y == 1 && x != 1 && x != n - 1) {
        return false;
      }
      x = y;
    }
    if (x != 1) {
      return false;
    }
  }
  return true;
}
ll gcd(ll a, ll b) {
  return b == 0 ? a : gcd(b, a % b);
}
ll f(ll x, ll c, ll m) {
  return (mul(x, x, m) + c) % m;
}
ll pollard_rho(ll n) {
  ll l = 0, r = 0, c = rand() % (n - 1) + 1;
  for (int len = 1; ; len <<= 1, l = r) {
    ll v = 1;
    for (int i = 1; i <= len; ++i) {
      r = f(r, c, n);
      v = mul(v, abs(r - l), n);
      if (i % 128 == 0) {
        ll k = gcd(v, n);
        if (k > 1) {
          return k;
        }
      }
    }
    ll k = gcd(v, n);
    if (k > 1) {
      return k;
    }
  }
}
void fac(ll n) {
  if (n <= ans) {
    return;
  }
  if (miller_rabin(n)) {
    ans = max(ans, n);
    return;
  }
  ll p = n;
  while (p == n) {
    p = pollard_rho(n);
  }
  while (n % p == 0) {
    n /= p;
  }
  fac(n), fac(p);
}
