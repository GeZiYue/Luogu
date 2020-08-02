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

const int N = 270005;
const int M1 = 167772161, M2 = 998244353, M3 = 1004535809, g = 3;

int pow(int, int, int);

const ll M12 = M1 * 1ll * M2;
const int iv1 = pow(M1, M2 - 2, M2), iv2 = pow(M12 % M3, M3 - 2, M3);

class Int {
public:
  int x, y, z;
  Int(int a = 0) {
    x = a % M1;
    y = a % M2;
    z = a % M3;
  }
  Int(int xx, int yy, int zz) : x(xx), y(yy), z(zz) {}
  friend Int operator + (const Int &, const Int &);
  friend Int operator - (const Int &, const Int &);
  friend Int operator * (const Int &, const Int &);
  operator int();
};
class Poly {
public:
  Int *a;
  int deg;
  Poly() {
    a = new Int[N];
    memset(a, 0, sizeof(Int) * N);
  }
  void NTT(int, bool);
};
int r[N];

int mod;

int main () {
  int n, m;
  read(n), read(m), read(mod);
  Poly f, g;
  f.deg = n, g.deg = m;
  for (int i = 0; i <= n; ++i) {
    int a;
    read(a);
    f.a[i] = a;
  }
  for (int i = 0; i <= m; ++i) {
    int a;
    read(a);
    g.a[i] = a;
  }
  int lim = 1;
  while (lim <= (n + m)) {
    lim <<= 1;
  }
  for (int i = 0; i < lim; ++i) {
    r[i] = (r[i >> 1] >> 1) | ((i & 1) * (lim >> 1));
  }
  f.NTT(lim, false), g.NTT(lim, false);
  for (int i = 0; i < lim; ++i) {
    f.a[i] = f.a[i] * g.a[i];
  }
  f.NTT(lim, true);
  f.deg = n + m;
  for (int i = 0; i <= n + m; ++i) {
    write(int(f.a[i])), SP;
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
Int operator + (const Int &i, const Int &j) {
  return Int(
    (i.x + j.x) % M1,
    (i.y + j.y) % M2,
    (i.z + j.z) % M3
  );
}
Int operator - (const Int &i, const Int &j) {
  return Int(
    (i.x - j.x + M1) % M1,
    (i.y - j.y + M2) % M2,
    (i.z - j.z + M3) % M3
  );
}
Int operator * (const Int &i, const Int &j) {
  return Int(
    i.x * 1ll * j.x % M1,
    i.y * 1ll * j.y % M2,
    i.z * 1ll * j.z % M3
  );
}
Int::operator int() {
  ll a = (y - x + M2) % M2 * 1ll * iv1 % M2 * M1 + x;
  return ((z - a % M3 + M3) % M3 * 1ll * iv2 % M3 * (M12 % mod) % mod + a) % mod;
}
void Poly::NTT(int lim, bool opt) {
  if (opt) {
    std::reverse(a + 1, a + lim);
  }
  for (int i = 0; i < lim; ++i) {
    if (i < r[i]) {
      std::swap(a[i], a[r[i]]);
    }
  }
  for (int l = 1; l < lim; l <<= 1) {
    Int gw = Int(
      pow(g, (M1 - 1) / (l << 1), M1),
      pow(g, (M2 - 1) / (l << 1), M2),
      pow(g, (M3 - 1) / (l << 1), M3)
    );
    for (int i = 0; i < lim; i += (l << 1)) {
      Int gn = 1;
      for (int j = 0; j < l; ++j, gn = gn * gw) {
        Int x = a[i + j], y = a[i + j + l] * gn;
        a[i + j] = x + y;
        a[i + j + l] = x - y;
      }
    }
  }
  if (opt) {
    Int iv(
      pow(lim, M1 - 2, M1),
      pow(lim, M2 - 2, M2),
      pow(lim, M3 - 2, M3)
    );
    for (int i = 0; i < lim; ++i) {
      a[i] = a[i] * iv;
    }
  }
}
