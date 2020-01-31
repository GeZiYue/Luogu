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

const int N = 270000;
const int Mod = 998244353, g = 3, ig = 332748118;

class Poly {
public:
  int *a;
  int deg;
  Poly() { a = new int[N]; memset(a, 0, sizeof(int) * N); }
  Poly(const Poly &p) {
    a = new int[N];
    memcpy(a, p.a, sizeof(int) * N);
    deg = p.deg;
  }
  void NTT(int, bool);
  Poly inv();
  Poly div(Poly);
  Poly mod(Poly, Poly);
};
int add(int i, int j) { i += j; return i >= Mod ? i - Mod : i; }
int sub(int i, int j) { i -= j; return i < 0 ? i + Mod : i; }
int qpow(int, int);
int r[N];

Poly F, G;
int n, m;

int main () {
  read(n), read(m);
  F.deg = n, G.deg = m;
  for (int i = 0; i <= n; ++i) {
    read(F.a[i]);
  }
  for (int i = 0; i <= m; ++i) {
    read(G.a[i]);
  }
  Poly Q = F.div(G);
  Poly R = F.mod(G, Q);
  for (int i = 0; i <= n - m; ++i) {
    write(Q.a[i]), SP;
  }
  EL;
  for (int i = 0; i <= m - 1; ++i) {
    write(R.a[i]), SP;
  }
  EL;
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

int qpow(int a, int b) {
  int now = a, ans = 1;
  while (b) {
    if (b & 1) {
      ans = ans * 1ll * now % Mod;
    }
    now = now * 1ll * now % Mod;
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
    int gw = qpow(opt ? ig : g, (Mod - 1) / (l << 1));
    for (int i = 0; i < lim; i += (l << 1)) {
      for (int j = 0, gn = 1; j < l; ++j, gn = gn * 1ll * gw % Mod) {
        int x = a[i + j], y = a[i + j + l] * 1ll * gn % Mod;
        a[i + j] = add(x, y);
        a[i + j + l] = sub(x, y);
      }
    }
  }
  if (opt) {
    int iv = qpow(lim, Mod - 2);
    for (int i = 0; i < lim; ++i) {
      a[i] = a[i] * 1ll * iv % Mod;
    }
  }
}
Poly Poly::inv() {
  Poly A, B, ans;
  ans.a[0] = qpow(this->a[0], Mod - 2), ans.deg = this->deg;
  int now = 1;
  while ((now >> 1) <= this->deg) {
    for (int i = 0; i < now; ++i) {
      A.a[i] = this->a[i];
      B.a[i] = ans.a[i];
    }
    int lim = now << 1;
    for (int i = 0; i < lim; ++i) {
      r[i] = (r[i >> 1] >> 1) | ((i & 1) * now);
    }
    A.NTT(lim, false), B.NTT(lim, false);
    for (int i = 0; i < lim; ++i) {
      ans.a[i] = B.a[i] * 1ll * sub(2, int(B.a[i] * 1ll * A.a[i] % Mod)) % Mod;
    }
    ans.NTT(lim, true);
    for (int i = now; i < lim; ++i) {
      ans.a[i] = 0;
    }
    now <<= 1;
  }
  for (int i = ans.deg + 1; i < (now >> 1); ++i) {
    ans.a[i] = 0;
  }
  return ans;
}
Poly Poly::div(Poly gt) {
  Poly f(*this), g(gt);
  std::reverse(f.a, f.a + f.deg + 1);
  std::reverse(g.a, g.a + g.deg + 1);
  for (int i = f.deg - g.deg + 1; i <= g.deg; ++i) {
    g.a[i] = 0;
  }
  g.deg = f.deg - g.deg;
  g = g.inv();
  int lim = 1;
  while (lim <= (f.deg + g.deg)) {
    lim <<= 1;
  }
  for (int i = 0; i < lim; ++i) {
    r[i] = (r[i >> 1] >> 1) | ((i & 1) * (lim >> 1));
  }
  f.NTT(lim, false), g.NTT(lim, false);
  for (int i = 0; i < lim; ++i) {
    g.a[i] = f.a[i] * 1ll * g.a[i] % Mod;
  }
  g.NTT(lim, true);
  std::reverse(g.a, g.a + g.deg + 1);
  for (int i = g.deg + 1; i < lim; ++i) {
    g.a[i] = 0;
  }
  return g;
}
Poly Poly::mod(Poly gt, Poly qt) {
  Poly g(gt), q(qt), ans;
  ans.deg = g.deg - 1;
  int lim = 1;
  while (lim <= this->deg) {
    lim <<= 1;
  }
  for (int i = 0; i < lim; ++i) {
    r[i] = (r[i >> 1] >> 1) | ((i & 1) * (lim >> 1));
  }
  g.NTT(lim, false), q.NTT(lim, false);
  for (int i = 0; i < lim; ++i) {
    g.a[i] = g.a[i] * 1ll * q.a[i] % Mod;
  }
  g.NTT(lim, true);
  for (int i = 0; i <= ans.deg; ++i) {
    ans.a[i] = sub(this->a[i], g.a[i]);
  }
  return ans;
}
