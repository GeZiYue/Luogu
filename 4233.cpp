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
const int Mod = 998244353, gi = 3;

int add(int a, int b) { return (a += b) >= Mod ? a - Mod : a; }
int sub(int a, int b) { return (a -= b) < 0 ? a + Mod : a; }
int pow(int a, int b, int m);
class Poly {
public:
  int *a, deg;
  Poly() {
    a = new int[N];
    memset(a, 0, N);
    deg = 0;
  }
  void NTT(int lim, bool opt);
  Poly inv();
};
int r[N];

Poly F, G;
int f[N], g[N];
int fac[N], ifac[N];
int n;

int main() {
  read(n);
  fac[0] = 1;
  for (int i = 1; i <= n; ++i) {
    fac[i] = fac[i - 1] * 1ll * i % Mod;
  }
  ifac[n] = pow(fac[n], Mod - 2, Mod);
  for (int i = n - 1; i >= 0; --i) {
    ifac[i] = ifac[i + 1] * 1ll * (i + 1) % Mod;
  }
  F.deg = G.deg = n;
  g[0] = 1, g[1] = 1;
  for (int i = 2; i <= n; ++i) {
    int tmp = i * 1ll * (i - 1) / 2 % (Mod - 1);
    g[i] = pow(2, tmp, Mod);
  }
  for (int i = 0; i <= n; ++i) {
    G.a[i] = g[i] * 1ll * ifac[i] % Mod;
  }
  G = G.inv();
  for (int i = 0; i <= n; ++i) {
    F.a[i] = sub(0, G.a[i]);
  }
  ++F.a[0];
  for (int i = 0; i <= n; ++i) {
    f[i] = F.a[i] * 1ll * fac[i] % Mod;
  }
  if (n >= 1) {
    write(1), EL;
  }
  if (n >= 2) {
    write(-1), EL;
  }
  for (int i = 3; i <= n; ++i) {
    int tmp = (i * 1ll * (i - 1) / 2 - i) % (Mod - 1);
    write(fac[i - 1] * 1ll * pow(2, tmp, Mod) % Mod * pow(f[i], Mod - 2, Mod) %
          Mod),
        EL;
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
    int gn = pow(gi, (Mod - 1) / (l << 1), Mod);
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
      r[i] = (r[i >> 1] >> 1) | ((i & 1) * now);
    }
    A.NTT(lim, false), B.NTT(lim, false);
    for (int i = 0; i < lim; ++i) {
      B.a[i] = sub(2, B.a[i] * 1ll * A.a[i] % Mod) * 1ll * B.a[i] % Mod;
    }
    B.NTT(lim, true);
    for (int i = now; i < lim; ++i) {
      B.a[i] = 0;
    }
    now <<= 1;
  }
  B.deg = deg;
  for (int i = deg + 1; i < (now >> 1); ++i) {
    B.a[i] = 0;
  }
  return B;
}
