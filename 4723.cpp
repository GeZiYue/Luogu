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

const int N = 130000;
const int Mod = 998244353, g0 = 3;

int add(int a, int b) { return a + b > Mod ? a + b - Mod : a + b; }
int sub(int a, int b) { return a < b ? a - b + Mod : a - b; }
class Poly {
public:
  int *a, deg;
  Poly() {
    a = new int[N];
    std::fill(a, a + N, 0);
    deg = 0;
  }
  Poly(const Poly &f) {
    a = new int[N];
    std::copy(f.a, f.a + N, a);
    deg = f.deg;
  }
  void NTT(int lim, bool opt);
  Poly inv();
  void modp(const Poly &p, const Poly &irp);
};
int pow(int a, int b, int m);
int r[N];

Poly f;
Poly g, irg;
int st[N];
int Lim;
int n, k;

int main () {
  read(n), read(k);
  f.deg = k;
  for (int i = 1; i <= k; ++i) {
    read(f.a[k - i]);
    if (f.a[k - i] < 0) {
      f.a[k - i] += Mod;
    }
    f.a[k - i] = Mod - f.a[k - i];
  }
  for (int i = 0; i < k; ++i) {
    read(st[i]);
    if (st[i] < 0) {
      st[i] += Mod;
    }
  }
  if (n < k) {
    write(st[n]), EL;
    return 0;
  }
  Lim = 1;
  while (Lim <= (k << 1)) {
    Lim <<= 1;
  }
  f.a[k] = 1;
  irg.deg = g.deg = f.deg;
  std::copy(f.a, f.a + f.deg + 1, g.a);
  std::reverse_copy(f.a, f.a + f.deg + 1, irg.a);
  irg.deg = (Lim >> 1) - 1;
  irg = irg.inv();
  for (int i = 0; i < Lim; ++i) {
    r[i] = (r[i >> 1] >> 1) | ((i & 1) * (Lim >> 1));
  }
  g.NTT(Lim, false), irg.NTT(Lim, false);
  Poly ans, now;
  ans.a[0] = now.a[1] = 1;
  while (n) {
    ans.deg = now.deg = Lim - 1;
    if (n & 1) {
      ans.NTT(Lim, false), now.NTT(Lim, false);
      for (int i = 0; i < Lim; ++i) {
        ans.a[i] = ans.a[i] * 1ll * now.a[i] % Mod;
      }
      ans.NTT(Lim, true), now.NTT(Lim, true);
      ans.modp(g, irg);
    }
    now.NTT(Lim, false);
    for (int i = 0; i < Lim; ++i) {
      now.a[i] = now.a[i] * 1ll * now.a[i] % Mod;
    }
    now.NTT(Lim, true);
    now.modp(g, irg);
    for (int i = 0; i < Lim; ++i) {
      write(now.a[i]), SP;
    }EL;
    n >>= 1;
  }
  int res = 0;
  for (int i = 0; i < k; ++i) {
    res = add(res, st[i] * 1ll * ans.a[i] % Mod);
  }
  write(res), EL;
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
    int gn = pow(g0, (Mod - 1) / (l << 1), Mod);
    for (int i = 0; i < lim; i += (l << 1)) {
      for (int j = 0, gw = 1; j < l; ++j, gw = gw * 1ll * gn % Mod) {
        int x = a[i | j], y = a[i | j | l] * 1ll * gw % Mod;
        a[i | j] = add(x, y);
        a[i | j | l] = sub(x, y);
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
  Poly A, B;
  A.a[0] = pow(a[0], Mod - 2, Mod);
  int now = 1;
  while (now <= (deg << 1)) {
    for (int i = 0; i < now; ++i) {
      B.a[i] = a[i];
    }
    int lim = now << 1;
    for (int i = 0; i < lim; ++i) {
      r[i] = (r[i >> 1] >> 1) | ((i & 1) * (lim >> 1));
    }
    A.NTT(lim, false), B.NTT(lim, false);
    for (int i = 0; i < lim; ++i) {
      A.a[i] = sub(2, A.a[i] * 1ll * B.a[i] % Mod) * 1ll * A.a[i] % Mod;
    }
    A.NTT(lim, true);
    for (int i = now; i < lim; ++i) {
      A.a[i] = 0;
    }
    now <<= 1;
  }
  A.deg = deg;
  for (int i = deg + 1; i < (now >> 1); ++i) {
    A.a[i] = 0;
  }
  return A;
}
void Poly::modp(const Poly &p, const Poly &irp) {
  while (a[deg] == 0) {
    --deg;
  }
  if (deg < p.deg) {
    return;
  }
  Poly f(*this), g(p), irg(irp);
  std::reverse(f.a, f.a + f.deg + 1);
  Poly ans;
  f.NTT(Lim, false);
  for (int i = 0; i < Lim; ++i) {
    ans.a[i] = f.a[i] * 1ll * irp.a[i] % Mod;
  }
  ans.NTT(Lim, true);
  ans.deg = f.deg - g.deg;
  for (int i = ans.deg + 1; i < Lim; ++i) {
    ans.a[i] = 0;
  }
  std::reverse(ans.a, ans.a + ans.deg + 1);
  for (int i = 0; i < ans.deg; ++i) {
  }
  ans.NTT(Lim, false);
  for (int i = 0; i < Lim; ++i) {
    ans.a[i] = ans.a[i] * 1ll * g.a[i] % Mod;
  }
  ans.NTT(Lim, true);
  for (int i = 0; i < g.deg; ++i) {
    this->a[i] = sub(p.a[i], ans.a[i]);
  }
  this->deg = g.deg;
  for (int i = this->deg + 1; i < Lim; ++i) {
    this->a[i] = 0;
  }
}
