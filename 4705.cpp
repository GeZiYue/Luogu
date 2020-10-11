#include <algorithm>
#include <bitset>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

#define isNum(a) (a >= '0' && a <= '9')
#define SP putchar(' ')
#define EL putchar('\n')
#define File(a) freopen(a ".in", "r", stdin), freopen(a ".out", "w", stdout)

template <class T> void read(T &);
template <class T> void write(const T &);

typedef long long ll;
typedef unsigned long long ull;
typedef const long long &cll;
typedef const int &ci;
typedef std::pair<int, int> pii;
const int iinf = 2147483647;
const ll llinf = 9223372036854775807ll;
using std::abs;
using std::max;
using std::min;

const int N = 270000;
const int Mod = 998244353, g = 3;

int add(int a, int b) { return (a += b) >= Mod ? a - Mod : a; }
int sub(int a, int b) { return (a -= b) < 0 ? a + Mod : a; }

class Poly {
public:
  int *a, deg;
  Poly() {
    a = new int[N];
    memset(a, 0, sizeof(int) * N);
    deg = 0;
  }
  Poly(int n) {
    a = new int[n << 1 | 1];
    memset(a, 0, sizeof(int) * (n << 1));
    deg = 0;
  }
  void NTT(int lim, bool opt);
  Poly inv();
  Poly drv();
  Poly itg();
  Poly ln();
};
int r[N];

int pow(int a, int b, int m);
Poly solve(int *a, int l, int r);

int a[N], b[N];
int fac[N], ifac[N];
int n, m, t, L;

int main() {
  fac[0] = 1;
  for (int i = 1; i <= 200000; ++i) {
    fac[i] = fac[i - 1] * 1ll * i % Mod;
  }
  ifac[200000] = pow(fac[200000], Mod - 2, Mod);
  for (int i = 199999; i >= 0; --i) {
    ifac[i] = ifac[i + 1] * 1ll * (i + 1) % Mod;
  }
  read(n), read(m);
  for (int i = 1; i <= n; ++i) {
    read(a[i]);
  }
  for (int i = 1; i <= m; ++i) {
    read(b[i]);
  }
  read(t);
  L = max(t, max(n, m));
  Poly f = solve(a, 1, L), g = solve(b, 1, L);
  Poly F, G;
  F.deg = L, G.deg = L;
  for (int i = 0; i <= L; ++i) {
    F.a[i] = f.a[i];
  }
  for (int i = 0; i <= L; ++i) {
    G.a[i] = g.a[i];
  }
  F = F.ln().drv();
  for (int i = L; i >= 1; --i) {
    F.a[i] = sub(0, F.a[i - 1]);
  }
  F.a[0] = n;
  G = G.ln().drv();
  for (int i = L; i >= 1; --i) {
    G.a[i] = sub(0, G.a[i - 1]);
  }
  G.a[0] = m;
  for (int i = 0; i <= L; ++i) {
    F.a[i] = F.a[i] * 1ll * ifac[i] % Mod;
  }
  for (int i = 0; i <= L; ++i) {
    G.a[i] = G.a[i] * 1ll * ifac[i] % Mod;
  }
  int lim = 1;
  while (lim <= (L << 1)) {
    lim <<= 1;
  }
  for (int i = 0; i < lim; ++i) {
    r[i] = (r[i >> 1] >> 1) | ((i & 1) * (lim >> 1));
  }
  F.NTT(lim, false), G.NTT(lim, false);
  for (int i = 0; i < lim; ++i) {
    F.a[i] = F.a[i] * 1ll * G.a[i] % Mod;
  }
  F.NTT(lim, true);
  int iv = pow(n * 1ll * m % Mod, Mod - 2, Mod);
  for (int i = 1; i <= t; ++i) {
    write(F.a[i] * 1ll * iv % Mod * fac[i] % Mod), EL;
  }
  return 0;
}

template <class T> inline void read(T &Re) {
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
template <class T> inline void write(const T &Wr) {
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
    int gn = pow(g, (Mod - 1) / (l << 1), Mod);
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
  B.a[0] = pow(a[0], Mod - 2, Mod);
  int now = 1;
  while (now <= (deg << 1)) {
    for (int i = 0; i < now; ++i) {
      A.a[i] = a[i];
    }
    int lim = now << 1;
    for (int i = 0; i < lim; ++i) {
      r[i] = (r[i >> 1] >> 1) | ((i & 1) * (lim >> 1));
    }
    A.NTT(lim, false), B.NTT(lim, false);
    for (int i = 0; i < lim; ++i) {
      B.a[i] = sub(2, A.a[i] * 1ll * B.a[i] % Mod) * 1ll * B.a[i] % Mod;
    }
    B.NTT(lim, true);
    for (int i = now; i < lim; ++i) {
      B.a[i] = 0;
    }
    now <<= 1;
  }
  B.deg = deg;
  for (int i = B.deg + 1; i < (now >> 1); ++i) {
    B.a[i] = 0;
  }
  return B;
}
Poly Poly::drv() {
  Poly ans;
  ans.deg = deg - 1;
  for (int i = 0; i < deg; ++i) {
    ans.a[i] = a[i + 1] * 1ll * (i + 1) % Mod;
  }
  return ans;
}
Poly Poly::itg() {
  Poly ans;
  ans.deg = deg + 1;
  for (int i = 1; i <= deg + 1; ++i) {
    ans.a[i] = a[i - 1] * 1ll * pow(i, Mod - 2, Mod) % Mod;
  }
  return ans;
}
Poly Poly::ln() {
  Poly A = drv(), B = inv();
  int lim = 1;
  while (lim < (deg << 1)) {
    lim <<= 1;
  }
  for (int i = 0; i < lim; ++i) {
    r[i] = (r[i >> 1] >> 1) | ((i & 1) * (lim >> 1));
  }
  A.NTT(lim, false), B.NTT(lim, false);
  for (int i = 0; i < lim; ++i) {
    A.a[i] = A.a[i] * 1ll * B.a[i] % Mod;
  }
  A.NTT(lim, true);
  A = A.itg();
  return A;
}
Poly solve(int *a, int left, int right) {
  if (left == right) {
    Poly ans(2);
    ans.a[0] = 1;
    ans.a[1] = sub(0, a[left]);
    return ans;
  }
  int mid = (left + right) >> 1;
  Poly A = solve(a, left, mid), B = solve(a, mid + 1, right);
  Poly ans((right - left + 1) << 1);
  ans.deg = right - left + 1;
  int lim = 1;
  while (lim <= (right - left + 1)) {
    lim <<= 1;
  }
  for (int i = 0; i < lim; ++i) {
    r[i] = (r[i >> 1] >> 1) | ((i & 1) * (lim >> 1));
  }
  A.NTT(lim, false), B.NTT(lim, false);
  for (int i = 0; i < lim; ++i) {
    ans.a[i] = A.a[i] * 1ll * B.a[i] % Mod;
  }
  ans.NTT(lim, true);
  return ans;
}
