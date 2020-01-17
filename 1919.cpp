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
const int N = 2500000;
const int Mod = 998244353, g = 3, gi = 332748118;

int pow(int, int, int);
class Poly {
public:
  int deg;
  int *a;
  Poly() { a = new int[N]; memset(a, 0, sizeof(int) * (N - 1)); }
  void NTT(int, bool);
  Poly operator*(const Poly &) const;
};
int r[N];

int n, m;

int main () {
  Poly a, b;
  {
    char ch = getchar();
    while (!isNum(ch)) {
      ch = getchar();
    }
    n = -1;
    while (isNum(ch)) {
      a.a[++n] = ch - '0';
      ch = getchar();
    }
    std::reverse(a.a, a.a + n + 1);
    a.deg = n;
  }
  {
    char ch = getchar();
    while (!isNum(ch)) {
      ch = getchar();
    }
    m = -1;
    while (isNum(ch)) {
      b.a[++m] = ch - '0';
      ch = getchar();
    }
    std::reverse(b.a, b.a + m + 1);
    b.deg = m;
  }
  Poly c = a * b;
  for (int i = 0, num = 0; i <= c.deg; ++i) {
    c.a[i] += num;
    num = c.a[i] / 10;
    c.a[i] %= 10;
    if (i == c.deg && num) {
      c.a[++c.deg] = 0;
    }
  }
  int al = c.deg;
  while (!c.a[al] && ~al) {
    --al;
  }
  while (~al) {
    putchar(c.a[al--] + '0');
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
  for (int l = 1; l < lim; l <<= 1) {
    int gn = pow(opt ? gi : g, (Mod - 1) / (l << 1), Mod);
    for (int i = 0; i < lim; i += (l << 1)) {
      for (int j = 0, gw = 1; j < l; ++j, gw = gw * 1ll * gn % Mod) {
        int x = a[i + j], y = a[i + j + l] * 1ll * gw % Mod;
        a[i + j] = (x + y) % Mod;
        a[i + j + l] = (x - y + Mod) % Mod;
      }
    }
  }
}
Poly Poly::operator*(const Poly &i) const {
  Poly a = *this, b = i;
  Poly c;
  c.deg = a.deg + b.deg;
  int lim = 1;
  while (lim <= c.deg) {
    lim <<= 1;
  }
  for (int i = 0; i < lim; ++i) {
    r[i] = (r[i >> 1] >> 1) | ((i & 1) * (lim >> 1));
  }
  a.NTT(lim, false);
  b.NTT(lim, false);
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
