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

const int N = 540000;
const int Mod = 998244353, gm = 3;

class Poly {
public:
  int *a, deg;
  Poly(int n = 0) {
    a = new int[n << 1 | 1];
    deg = 0;
    memset(a, 0, sizeof(int) * (n << 1));
  }
  void NTT(int lim, bool opt);
  Poly inv();
  Poly mul(Poly x);
  Poly Tmul(Poly x);
};
int pow(int, int, int);
int r[N];
void getg(int, int, int);
void getans(int, int, int, Poly);

Poly g[N];
int q[N];
int ans[N];
int gw[N];
int n, m;

int main () {
  for (int l = 1; l <= (1 << 18); l <<= 1) {
    int gn = pow(gm, (Mod - 1) / (l << 1), Mod);
    gw[l] = 1;
    for (int i = 1; i < l; ++i) {
      gw[l | i] = gw[l | (i - 1)] * 1ll * gn % Mod;
    }
  }
  read(n), read(m);
  Poly f(n << 2);
  f.deg = max(n, m);
  for (int i = 0; i <= n; ++i) {
    read(f.a[i]);
  }
  for (int i = 1; i <= m; ++i) {
    read(q[i]);
  }
  n = max(n, m);
  getg(1, 1, n);
  int lim = 1;
  while (lim <= n) {
    lim <<= 1;
  }
  Poly gp(lim);
  gp.deg = lim;
  for (int i = 0; i <= n; ++i) {
    gp.a[i] = g[1].a[i];
  }
  gp = gp.inv();
  for (int i = n + 1; i <= gp.deg; ++i) {
    gp.a[i] = 0;
  }
  std::reverse(gp.a, gp.a + n + 1);
  Poly h = gp.mul(f);
  for (int i = 0; i <= n; ++i) {
    h.a[i] = h.a[i + n];
  }
  h.deg = n;
  for (int i = n + 1; i < (n << 1); ++i) {
    h.a[i] = 0;
  }
  getans(1, 1, n, h);
  for (int i = 1; i <= m; ++i) {
    write(ans[i]), EL;
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

int pow(int a, int b, int m) {
  int ans = 1, now = a;
  while (b) {
    if (b & 1) {
      ans = ans * 1ll * now % m;
    }
    now = now * 1ll * now % m;
    b >>= 1;
  }
  return ans;
}
void Poly::NTT(int lim, bool opt) {
  for (int i = 0; i < lim; ++i) {
    if (i < r[i]) {
      std::swap(a[i], a[r[i]]);
    }
  }
  for (int l = 1; l < lim; l <<= 1) {
    for (int i = 0; i < lim; i += (l << 1)) {
      for (int j = 0; j < l; ++j) {
        int x = a[i | j], y = a[i | j | l] * 1ll * gw[l | j] % Mod;
        a[i | j] = (x + y) % Mod;
        a[i | j | l] = (x - y + Mod) % Mod;
      }
    }
  }
  if (opt) {
    std::reverse(a + 1, a + lim);
    int iv = pow(lim, Mod - 2, Mod);
    for (int i = 0; i < lim; ++i) {
      a[i] = a[i] * 1ll * iv % Mod;
    }
  }
}
Poly Poly::inv() {
  Poly A(deg << 2), B(deg << 2);
  A.a[0] = pow(a[0], Mod - 2, Mod);
  int now = 1;
  while ((now >> 1) <= deg) {
    for (int i = 0; i < now; ++i) {
      B.a[i] = a[i];
    }
    int lim = now << 1;
    for (int i = 0; i < lim; ++i) {
      r[i] = (r[i >> 1] >> 1) | ((i & 1) * (lim >> 1));
    }
    A.NTT(lim, false), B.NTT(lim, false);
    for (int i = 0; i < lim; ++i) {
      A.a[i] = A.a[i] * 1ll * (2 - A.a[i] * 1ll * B.a[i] % Mod + Mod) % Mod;
    }
    A.NTT(lim, true);
    for (int i = now; i < lim; ++i) {
      A.a[i] = 0;
    }
    now <<= 1;
  }
  A.deg = deg;
  for (int i = A.deg + 1; i < (now >> 1); ++i) {
    A.a[i] = 0;
  }
  return A;
}
Poly Poly::mul (Poly x) {
  int lim = 1;
  while (lim <= (deg + x.deg)) {
    lim <<= 1;
  }
  for (int i = 0; i < lim; ++i) {
    r[i] = (r[i >> 1] >> 1) | ((i & 1) * (lim >> 1));
  }
  Poly A(lim), B(lim);
  A.deg = deg;
  for (int i = 0; i <= deg; ++i) {
    A.a[i] = a[i];
  }
  B.deg = x.deg;
  for (int i = 0; i <= x.deg; ++i) {
    B.a[i] = x.a[i];
  }
  A.NTT(lim, false), B.NTT(lim, false);
  for (int i = 0; i < lim; ++i) {
    A.a[i] = A.a[i] * 1ll * B.a[i] % Mod;
  }
  A.NTT(lim, true);
  A.deg += B.deg;
  for (int i = A.deg + 1; i < lim; ++i) {
    A.a[i] = 0;
  }
  return A;
}
Poly Poly::Tmul(Poly x) {
  int lim = 1;
  while (lim <= x.deg) {
    lim <<= 1;
  }
  for (int i = 0; i < lim; ++i) {
    r[i] = (r[i >> 1] >> 1) | ((i & 1) * (lim >> 1));
  }
  Poly A(lim), B(lim);
  A.deg = deg;
  for (int i = 0; i <= deg; ++i) {
    A.a[i] = a[deg - i];
  }
  B.deg = x.deg;
  for (int i = 0; i <= x.deg; ++i) {
    B.a[i] = x.a[i];
  }
  A.NTT(lim, false), B.NTT(lim, false);
  for (int i = 0; i < lim; ++i) {
    A.a[i] = A.a[i] * 1ll * B.a[i] % Mod;
  }
  A.NTT(lim, true);
  for (int i = 0; i <= B.deg - A.deg; ++i) {
    A.a[i] = A.a[i + A.deg];
  }
  A.deg = B.deg - A.deg;
  for (int i = A.deg + 1; i < lim; ++i) {
    A.a[i] = 0;
  }
  return A;
}
void getg(int x, int xl, int xr) {
  if (xl == xr) {
    g[x] = Poly(1);
    g[x].a[0] = 1, g[x].a[1] = Mod - q[xl];
    g[x].deg = 1;
    return;
  }
  int xm = (xl + xr) >> 1;
  getg(x << 1, xl, xm);
  getg(x << 1 | 1, xm + 1, xr);
  g[x] = g[x << 1].mul(g[x << 1 | 1]);
}
void getans(int x, int xl, int xr, Poly h) {
  if (xl > m) {
    return;
  }
  if (xl == xr) {
    ans[xl] = h.a[0];
    return;
  }
  int xm = (xl + xr) >> 1;
  Poly hl = g[x << 1 | 1].Tmul(h);
  getans(x << 1, xl, xm, hl);
  Poly hr = g[x << 1].Tmul(h);
  getans(x << 1 | 1, xm + 1, xr, hr);
}
