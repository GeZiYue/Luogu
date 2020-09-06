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

const int N = 20005;
const int M = 100005;
const int Mod = 998244353, g = 3;

class Poly {
public:
  int *a;
  Poly() {
    a = new int[M];
    memset(a, 0, sizeof(int) * M);
  }
  void NTT(int lim, bool opt);
};
int r[M];

int pow(int a, int b, int m);

int pw[N], dw[N], fac[N], ifac[N];
int f[N];
int n, m, p;

int main () {
  read(n), read(m), read(p);
  int lim = 1;
  while (lim <= (m << 1)) {
    lim <<= 1;
  }
  for (int i = 1; i < lim; ++i) {
    r[i] = (r[i >> 1] >> 1) | ((i & 1) * (lim >> 1));
  }
  pw[0] = 1;
  dw[0] = 1;
  fac[0] = 1;
  for (int i = 1; i <= m; ++i) {
    pw[i] = pw[i - 1] * 1ll * p % Mod;
    dw[i] = dw[i - 1] * 1ll * (n - i + 1) % Mod;
    fac[i] = fac[i - 1] * 1ll * i % Mod;
  }
  ifac[m] = pow(fac[m], Mod - 2, Mod);
  for (int i = m - 1; i >= 0; --i) {
    ifac[i] = ifac[i + 1] * 1ll * (i + 1) % Mod;
  }
  for (int i = 0; i <= m; ++i) {
    read(f[i]);
  }
  Poly F, G;
  for (int i = 0; i <= m; ++i) {
    F.a[i] = f[i] * 1ll * ifac[i] % Mod;
    G.a[i] = ((i & 1) ? (Mod - ifac[i]) : ifac[i]);
  }
  F.NTT(lim, false), G.NTT(lim, false);
  for (int i = 0; i < lim; ++i) {
    F.a[i] = F.a[i] * 1ll * G.a[i] % Mod;
  }
  F.NTT(lim, true);
  int ans = 0;
  for (int i = 0; i <= m; ++i) {
    ans = (ans + F.a[i] * 1ll * pw[i] % Mod * dw[i] % Mod) % Mod;
  }
  write(ans), EL;
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
    int gn = pow(g, (Mod - 1) / (l << 1), Mod);
    for (int i = 0; i < lim; i += (l << 1)) {
      for (int j = 0, gw = 1; j < l; ++j, gw = gw * 1ll * gn % Mod) {
        int x = a[i + j], y = a[i + j + l] * 1ll * gw % Mod;
        a[i + j] = (x + y) % Mod;
        a[i + j + l] = (x - y + Mod) % Mod;
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
