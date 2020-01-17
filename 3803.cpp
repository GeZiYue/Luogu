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
typedef const long long & cll;
typedef const int & ci;
typedef std::pair<int, int> pii;
const int iinf = 2147483647;
const ll llinf = 9223372036854775807ll;
using std::min;
using std::max;
using std::abs;
using std::sort;
const int N = 2500000;
const int Mod = 998244353;
const int g = 3, gi = 332748118;

int pow(int, int, int);
class Poly {
public:
  int *a;
  int deg;
  Poly() { a = new int[N]; }
  void NTT(int, bool);
  Poly operator *(const Poly &) const;
};

int r[N];
int n, m;

int main () {
  read(n), read(m);
  Poly a, b;
  a.deg = n, b.deg = m;
  for (int i = 0; i <= n; ++i) {
    read(a.a[i]);
  }
  for (int i = 0; i <= m; ++i) {
    read(b.a[i]);
  }
  Poly c = a * b;
  for (int i = 0; i <= c.deg; ++i) {
    write(c.a[i]), SP;
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

int pow(int a, int b, int p) {
  int ans = 1, now = a;
  while (b) {
    if (b & 1) {
      ans = ans * 1ll * now % p;
    }
    now = now * 1ll * now % p;
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
  for (int m = 1; m < lim; m <<= 1) {
    int l = m << 1;
    int gn = pow(opt ? gi : g, (Mod - 1) / l, Mod);
    for (int i = 0; i < lim; i += l) {
      int gw = 1;
      for (int j = 0; j < m; ++j, gw = gw * 1ll * gn % Mod) {
        int x = a[i + j], y = a[i + j + m] * 1ll * gw % Mod;
        a[i + j] = (x + y) % Mod;
        a[i + j + m] = (x - y + Mod) % Mod;
      }
    }
  }
}
Poly Poly::operator *(const Poly &tmp) const {
  int lim = 1;
  while (lim <= deg + tmp.deg) {
    lim <<= 1;
  }
  for (int i = 0; i < lim; ++i) {
    r[i] = (r[i >> 1] >> 1) | ((i & 1) * (lim >> 1));
  }
  Poly a = *this;
  Poly b = tmp;
  a.NTT(lim, false);
  b.NTT(lim, false);
  Poly c;
  c.deg = a.deg + b.deg;
  for (int i = 0; i < lim; ++i) {
    c.a[i] = a.a[i] * 1ll * b.a[i] % Mod;
  }
  c.NTT(lim, true);
  int inv = pow(lim, Mod - 2, Mod);
  for (int i = 0; i <= c.deg; ++i) {
    c.a[i] = c.a[i] * 1ll * inv % Mod;
  }
  return c;
}
