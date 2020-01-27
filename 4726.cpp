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
const int N = 280000;
const int Mod = 998244353, g = 3, gi = 332748118;

class Poly {
public:
  int *a;
  int deg;
  Poly() { a = new int[N]; memset(a, 0, sizeof(int) * (N - 1)); }
  void NTT(int, bool) const;
  Poly inv() const;
  Poly drv() const;
  Poly itg() const;
  Poly ln(int = 0) const;
  Poly exp() const;
};
int pow(int, int, int);
int add(int a, int b) { a += b; if (a >= Mod) {a -= Mod;} return a; }
int sub(int a, int b) { a -= b; if (a < 0) {a += Mod;} return a; }
int r[19][N];
int n;

int main () {
  read(n);
  for (int i = 0; i <= 18 && (1 << (i - 1)) <= (n << 1); ++i) {
    for (int j = 0; j < (1 << i); ++j) {
      r[i][j] = (r[i][j >> 1] >> 1) | ((j & 1) * (1 << (i - 1)));
    }
  }
  Poly f;
  f.deg = --n;
  for (int i = 0; i <= n; ++i) {
    read(f.a[i]);
  }
  Poly g = f.exp();
  for (int i = 0; i <= n; ++i) {
    write(g.a[i]), SP;
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
void Poly::NTT(int dep, bool opt) const {
  int lim = 1 << dep;
  for (int i = 0; i < lim; ++i) {
    if (i < r[dep][i]) {
      std::swap(a[i], a[r[dep][i]]);
    }
  }
  for (int l = 1; l < lim; l <<= 1) {
    int gn = pow(opt ? gi : g, (Mod - 1) / (l << 1), Mod);
    for (int i = 0; i < lim; i += (l << 1)) {
      for (int j = 0, gw = 1; j < l; ++j, gw = gw * 1ll * gn % Mod) {
        int x = a[i + j], y = a[i + j + l] * 1ll * gw % Mod;
        a[i + j] = add(x, y);
        a[i + j + l] = sub(x, y);
      }
    }
  }
  if (opt) {
    int iv = pow(lim, Mod - 2, Mod);
    for (int i = 0; i < lim; ++i) {
      a[i] = a[i] * 1ll * iv % Mod;
    }
  }
}
Poly Poly::inv() const {
  Poly A, B;
  Poly ans;
  ans.a[0] = pow(this->a[0], Mod - 2, Mod);
  int dep = 0;
  while ((1 << (dep - 1)) <= this->deg) {
    ++dep;
    int lim = 1 << dep;
    for (int i = 0; i < (lim >> 1); ++i) {
      A.a[i] = this->a[i];
      B.a[i] = ans.a[i];
    }
    A.NTT(dep, false), B.NTT(dep, false);
    for (int i = 0; i < lim; ++i) {
      ans.a[i] = B.a[i] * 1ll * sub(2, int(A.a[i] * 1ll * B.a[i] % Mod)) % Mod;
    }
    ans.NTT(dep, true);
    for (int i = (lim >> 1); i < lim; ++i) {
      ans.a[i] = 0;
    }
  }
  ans.deg = this->deg;
  return ans;
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
Poly Poly::ln(int dep) const {
  Poly A = this->drv(), B = this->inv();
  if (!dep) {
    while ((1 << dep) <= (this->deg << 1)) {
      ++dep;
    }
  }
  int lim = 1 << dep;
  A.NTT(dep, false), B.NTT(dep, false);
  for (int i = 0; i < lim; ++i) {
    A.a[i] = A.a[i] * 1ll * B.a[i] % Mod;
  }
  A.NTT(dep, true);
  A.deg = this->deg - 1;
  for (int i = A.deg + 1; i < lim; ++i) {
    A.a[i] = 0;
  }
  return A.itg();
}
Poly Poly::exp() const {
  Poly A, B, L;
  Poly ans;
  ans.a[0] = 1;
  int dep = 0;
  while ((1 << (dep - 1)) <= this->deg) {
    ++dep;
    int lim = 1 << dep;
    for (int i = 0; i < (lim >> 1); ++i) {
      A.a[i] = this->a[i];
      B.a[i] = ans.a[i];
    }
    B.deg = (lim >> 1) - 1;
    L = B.ln(dep);
    A.NTT(dep, false), B.NTT(dep, false), L.NTT(dep, false);
    for (int i = 0; i < lim; ++i) {
      ans.a[i] = B.a[i] * 1ll * sub(add(1, A.a[i]), L.a[i]) % Mod;
    }
    ans.NTT(dep, true);
    for (int i = (lim >> 1); i < lim; ++i) {
      ans.a[i] = 0;
    }
  }
  ans.deg = this->deg;
  return ans;
}
