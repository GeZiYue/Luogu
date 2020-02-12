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
const int Mod = 998244353, g = 3, ig = 332748118, iv2 = 499122177;

class Poly {
public:
  int deg, *a;
  Poly() {
    a = new int[N];
    memset(a, 0, sizeof(int) * N);
  }
  void NTT(int, bool);
  Poly inv();
  Poly sqrt();
  Poly drv();
  Poly itg();
  Poly asin();
  Poly atan();
};
int pow(int, int, int);
int r[N];

int main () {
  int n, ty;
  Poly f;
  read(n), read(ty);
  f.deg = --n;
  for (int i = 0; i <= n; ++i) {
    read(f.a[i]);
  }
  Poly ans;
  if (ty) {
    ans = f.atan();
  } else {
    ans = f.asin();
  }
  for (int i = 0; i <= n; ++i) {
    write(ans.a[i]), SP;
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
    int gw = pow(opt ? ig : g, (Mod - 1) / (l << 1), Mod);
    for (int i = 0; i < lim; i += (l << 1)) {
      for (int j = 0, gn = 1; j < l; ++j, gn = gn * 1ll * gw % Mod) {
        int x = a[i + j], y = a[i + j + l] * 1ll * gn % Mod;
        a[i + j] = (x + y) % Mod;
        a[i + j + l] = (x - y + Mod) % Mod;
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
Poly Poly::inv() {
  Poly A, B;
  B.a[0] = pow(this->a[0], Mod - 2, Mod);
  int now = 1;
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
      B.a[i] = B.a[i] * 1ll * ((2 - B.a[i] * 1ll * A.a[i] % Mod + Mod) % Mod) % Mod;
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
Poly Poly::sqrt() {
  Poly A, B, I;
  B.a[0] = this->a[0];
  int now = 1;
  while ((now >> 1) <= this->deg) {
    for (int i = 0; i < now; ++i) {
      A.a[i] = this->a[i];
    }
    B.deg = now - 1;
    I = B.inv();
    int lim = now << 1;
    for (int i = 0; i < lim; ++i) {
      r[i] = (r[i >> 1] >> 1) | ((i & 1) * now);
    }
    A.NTT(lim, false), B.NTT(lim, false), I.NTT(lim, false);
    for (int i = 0; i < lim; ++i) {
      B.a[i] = iv2 * 1ll * ((B.a[i] + A.a[i] * 1ll * I.a[i] % Mod) % Mod) % Mod;
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
Poly Poly::drv() {
  Poly ans;
  ans.deg = this->deg - 1;
  for (int i = 0; i <= ans.deg; ++i) {
    ans.a[i] = this->a[i + 1] * 1ll * (i + 1) % Mod;
  }
  return ans;
}
Poly Poly::itg() {
  Poly ans;
  ans.deg = this->deg + 1;
  for (int i = 0; i <= ans.deg; ++i) {
    ans.a[i] = this->a[i - 1] * 1ll * pow(i, Mod - 2, Mod) % Mod;
  }
  return ans;
}
Poly Poly::asin() {
  int lim = 1;
  while (lim <= (this -> deg << 1)) {
    lim <<= 1;
  }
  Poly ans;
  for (int i = 0; i <= this->deg; ++i) {
    ans.a[i] = this->a[i];
  }
  for (int i = 0; i < lim; ++i) {
    r[i] = (r[i >> 1] >> 1) | ((i & 1) * (lim >> 1));
  }
  ans.NTT(lim, false);
  for (int i = 0; i < lim; ++i) {
    ans.a[i] = ans.a[i] * 1ll * ans.a[i] % Mod;
  }
  ans.NTT(lim, true);
  ans.deg = this->deg;
  for (int i = 0; i <= ans.deg; ++i) {
    if (ans.a[i]) {
      ans.a[i] = Mod - ans.a[i];
    }
  }
  ans.a[0] = (ans.a[0] + 1) % Mod;
  for (int i = ans.deg + 1; i < lim; ++i) {
    ans.a[i] = 0;
  }
  ans = ans.sqrt().inv();
  Poly tmp = this->drv();
  for (int i = 0; i < lim; ++i) {
    r[i] = (r[i >> 1] >> 1) | ((i & 1) * (lim >> 1));
  }
  ans.NTT(lim, false), tmp.NTT(lim, false);
  for (int i = 0; i < lim; ++i) {
    ans.a[i] = ans.a[i] * 1ll * tmp.a[i] % Mod;
  }
  ans.NTT(lim, true);
  for (int i = ans.deg + 1; i < lim; ++i) {
    ans.a[i] = 0;
  }
  return ans.itg();
}
Poly Poly::atan() {
  int lim = 1;
  while (lim <= (this -> deg << 1)) {
    lim <<= 1;
  }
  Poly ans;
  ans.deg = this->deg;
  for (int i = 0; i < this->deg; ++i) {
    ans.a[i] = this->a[i];
  }
  for (int i = 0; i < lim; ++i) {
    r[i] = (r[i >> 1] >> 1) | ((i & 1) * (lim >> 1));
  }
  ans.NTT(lim, false);
  for (int i = 0; i < lim; ++i) {
    ans.a[i] = ans.a[i] * 1ll * ans.a[i] % Mod;
  }
  ans.NTT(lim, true);
  ans.deg = this->deg;
  ans.a[0] = (ans.a[0] + 1) % Mod;
  for (int i = ans.deg + 1; i < lim; ++i) {
    ans.a[i] = 0;
  }
  ans = ans.inv();
  Poly tmp = this->drv();
  for (int i = 0; i < lim; ++i) {
    r[i] = (r[i >> 1] >> 1) | ((i & 1) * (lim >> 1));
  }
  ans.NTT(lim, false), tmp.NTT(lim, false);
  for (int i = 0; i < lim; ++i) {
    ans.a[i] = ans.a[i] * 1ll * tmp.a[i] % Mod;
  }
  ans.NTT(lim, true);
  for (int i = ans.deg + 1; i < lim; ++i) {
    ans.a[i] = 0;
  }
  return ans.itg();
}
