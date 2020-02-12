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
const int Mod = 998244353, g = 3, ig = 332748118, poi = 86583718, ivi = 911660635, iv2 = 499122177;

int pow(int, int, int);
class Poly {
public:
  int deg, *a;
  Poly() { a = new int[N]; memset(a, 0, sizeof(int) * N); }
  void NTT(int, bool);
  Poly inv();
  Poly drv();
  Poly itg();
  Poly ln();
  Poly exp();
  Poly sin();
  Poly cos();
};
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
    ans = f.cos();
  } else {
    ans = f.sin();
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
  for (int i = 1; i <= ans.deg; ++i) {
    ans.a[i] = this->a[i - 1] * 1ll * pow(i, Mod - 2, Mod) % Mod;
  }
  return ans;
}
Poly Poly::ln() {
  Poly A = this->drv(), B = this->inv();
  int lim = 1;
  while (lim <= A.deg + B.deg) {
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
Poly Poly::exp() {
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
      B.a[i] = B.a[i] * 1ll * (((1 + A.a[i]) % Mod - L.a[i] + Mod) % Mod) % Mod;
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
Poly Poly::sin() {
  Poly A, B;
  for (int i = 0; i <= this->deg; ++i) {
    A.a[i] = this->a[i] * 1ll * poi % Mod;
  }
  A.deg = this->deg;
  A = A.exp();
  B = A.inv();
  for (int i = 0; i <= A.deg; ++i) {
    A.a[i] = ((A.a[i] - B.a[i] + Mod) % Mod) * 1ll * iv2 % Mod * ivi % Mod;
  }
  return A;
}
Poly Poly::cos() {
  Poly A, B;
  for (int i = 0; i <= this->deg; ++i) {
    A.a[i] = this->a[i] * 1ll * poi % Mod;
  }
  A.deg = this->deg;
  A = A.exp();
  B = A.inv();
  for (int i = 0; i <= A.deg; ++i) {
    A.a[i] = ((A.a[i] + B.a[i]) % Mod) * 1ll * iv2 % Mod;
  }
  return A;
}
