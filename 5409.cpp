#include <algorithm>
#include <bitset>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
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

template <class T>
void read(T &);
template <class T>
void write(const T &);

typedef long long ll;
typedef const long long &cll;
typedef const int &ci;
typedef std::pair<int, int> pii;
const int iinf = 2147483647;
const ll llinf = 9223372036854775807ll;
using std::abs;
using std::max;
using std::min;
using std::sort;
const int N = 280000;
const int Mod = 167772161, g = 3;

class Poly {
 public:
  int *a;
  int deg;
  Poly() {
    a = new int[N];
    memset(a, 0, sizeof(int) * (N - 1));
  }
  void NTT(int, bool) const;
  Poly inv() const;
  Poly drv() const;
  Poly itg() const;
  Poly ln() const;
  Poly exp() const;
};
int pow(int, int, int);
int add(int a, int b) { return (a += b) >= Mod ? a - Mod : a; }
int sub(int a, int b) { return (a -= b) < 0 ? a + Mod : a; }
int r[N];

Poly F;
int fac[N], ifac[N];
int n, m;

int main() {
  read(n), read(m);
  fac[0] = 1;
  for (int i = 1; i <= n; ++i) {
    fac[i] = fac[i - 1] * 1ll * i % Mod;
  }
  ifac[n] = pow(fac[n], Mod - 2, Mod);
  for (int i = n - 1; i >= 0; --i) {
    ifac[i] = ifac[i + 1] * 1ll * (i + 1) % Mod;
  }
  F.deg = n;
  for (int i = 0; i <= n; ++i) {
    F.a[i] = pow(i + 1, Mod - 2, Mod);
  }
  F = F.ln();
  for (int i = 0; i <= n; ++i) {
    F.a[i] = F.a[i] * 1ll * m % Mod;
  }
  F = F.exp();
  for (int i = 0; i <= n; ++i) {
    if (i < m) {
      write(0), SP;
    } else {
      write(F.a[i - m] * 1ll * ifac[m] % Mod * fac[i] % Mod), SP;
    }
  }
  EL;
  return 0;
}

template <class T>
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
template <class T>
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
void Poly::NTT(int lim, bool opt) const {
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
        a[i + j] = add(x, y);
        a[i + j + l] = sub(x, y);
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
Poly Poly::inv() const {
  Poly A, B;
  int now = 1;
  B.a[0] = pow(this->a[0], Mod - 2, Mod);
  while ((now >> 1) <= this->deg) {
    for (int i = 0; i < now; ++i) {
      A.a[i] = this->a[i];
    }
    int lim = now << 1;
    for (int i = 0; i < lim; ++i) {
      r[i] = (r[i >> 1] >> 1) | ((i & 1) * now);
    }
    A.NTT(lim, false), B.NTT(lim, false);
    for (int i = 0; i < lim; ++i) {
      B.a[i] = B.a[i] * 1ll * sub(2, int(A.a[i] * 1ll * B.a[i] % Mod)) % Mod;
    }
    B.NTT(lim, true);
    for (int i = now; i < lim; ++i) {
      B.a[i] = 0;
    }
    now <<= 1;
  }
  B.deg = this->deg;
  for (int i = B.deg + 1; i < (now >> 1); ++i) {
    B.a[i] = 0;
  }
  return B;
}
Poly Poly::drv() const {
  Poly ans;
  ans.deg = this->deg - 1;
  for (int i = 0; i <= ans.deg; ++i) {
    ans.a[i] = this->a[i + 1] * 1ll * (i + 1) % Mod;
  }
  return ans;
}
Poly Poly::itg() const {
  Poly ans;
  ans.deg = this->deg + 1;
  for (int i = 1; i <= ans.deg; ++i) {
    ans.a[i] = this->a[i - 1] * 1ll * pow(i, Mod - 2, Mod) % Mod;
  }
  return ans;
}
Poly Poly::ln() const {
  Poly A = this->drv(), B = this->inv();
  int lim = 1;
  while (lim <= (this->deg << 1)) {
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
  A.deg = this->deg - 1;
  for (int i = A.deg + 1; i < lim; ++i) {
    A.a[i] = 0;
  }
  return A.itg();
}
Poly Poly::exp() const {
  Poly A, B, L;
  B.a[0] = 1;
  int now = 1;
  while ((now >> 1) <= this->deg) {
    for (int i = 0; i < now; ++i) {
      A.a[i] = this->a[i];
    }
    B.deg = now - 1;
    L = B.ln();
    int lim = now << 1;
    for (int i = 0; i < lim; ++i) {
      r[i] = (r[i >> 1] >> 1) | ((i & 1) * now);
    }
    A.NTT(lim, false), B.NTT(lim, false), L.NTT(lim, false);
    for (int i = 0; i < lim; ++i) {
      B.a[i] = B.a[i] * 1ll * sub(add(1, A.a[i]), L.a[i]) % Mod;
    }
    B.NTT(lim, true);
    for (int i = now; i < lim; ++i) {
      B.a[i] = 0;
    }
    now <<= 1;
  }
  B.deg = this->deg;
  for (int i = B.deg + 1; i < (now >> 1); ++i) {
    B.a[i] = 0;
  }
  return B;
}
