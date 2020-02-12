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
#include <random>

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
const int Mod = 998244353, g = 3, ig = 332748118;
int si;

class Complex {
public:
  int rel, img;
  Complex (int real = 0, int imag = 0) : rel(real), img(imag) {}
  Complex operator *(const Complex &i) const {
    return Complex(
      (this->rel * 1ll * i.rel % Mod + si * 1ll * this->img % Mod * i.img % Mod) % Mod,
      (this->rel * 1ll * i.img % Mod + this->img * 1ll * i.rel % Mod) % Mod
    );
  }
  Complex operator ^(int b) const {
    Complex now = *this, ans = 1;
    while (b) {
      if (b & 1) {
        ans = ans * now;
      }
      now = now * now;
      b >>= 1;
    }
    return ans;
  }
};
class Poly {
public:
  int *a, deg;
  Poly() { a = new int[N]; deg = 0; memset(a, 0, sizeof(int) * N); }
  Poly(const Poly &i) { a = new int[N]; deg = i.deg; memcpy(a, i.a, sizeof(int) * N); }
  void NTT(int, bool);
  Poly inv();
  Poly sqrt();
};
int qpow(int, int);
int calc(int);
int lg2[N];
int r[20][N];

int main () {
  for (int i = 0; i < 19; ++i) {
    lg2[1 << i] = i;
    for (int j = 0; j < (1 << i); ++j) {
      r[i][j] = (r[i][j >> 1] >> 1) | ((j & 1) << (i - 1));
    }
  }
  int n;
  read(n);
  Poly f;
  f.deg = --n;
  for (int i = 0; i <= f.deg; ++i) {
    read(f.a[i]);
  }
  f = f.sqrt();
  for (int i = 0; i <= f.deg; ++i) {
    write(f.a[i]), SP;
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

int qpow(int a, int b) {
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
int calc(int n) {
  std::mt19937 rnd;
  int a = (rnd() % Mod + Mod) % Mod;
  while (!a || qpow((a * 1ll * a % Mod + Mod - n) % Mod, (Mod - 1) / 2) == 1) {
    a = (rnd() % Mod + Mod) % Mod;
  }
  si = (a * 1ll * a % Mod + Mod - n) % Mod;
  int ans = (Complex(a, 1) ^ ((Mod + 1) / 2)).rel;
  return min(ans, Mod - ans);
}
void Poly::NTT(int lim, bool opt) {
  int dp = lg2[lim];
  for (int i = 0; i < lim; ++i) {
    if (i < r[dp][i]) {
      std::swap(a[i], a[r[dp][i]]);
    }
  }
  for (int l = 1; l < lim; l <<= 1) {
    int k = l << 1;
    int gw = qpow(opt ? ig : g, (Mod - 1) / k);
    for (int i = 0; i < lim; i += k) {
      for (int j = 0, gn = 1; j < l; ++j, gn = gn * 1ll * gw % Mod) {
        int x = a[i + j], y = a[i + j + l] * 1ll * gn % Mod;
        a[i + j] = (x + y) % Mod, a[i + j + l] = (x - y + Mod) % Mod;
      }
    }
  }
}
Poly Poly::inv() {
  static Poly A, B;
  memset(A.a, 0, sizeof(int) * N);
  memset(B.a, 0, sizeof(int) * N);
  B.a[0] = qpow(this->a[0], Mod - 2);
  int now = 1;
  while ((now >> 1) <= this->deg) {
    for (int i = 0; i < now; ++i) {
      A.a[i] = this->a[i];
    }
    int lim = now << 1;
    A.NTT(lim, false), B.NTT(lim, false);
    for (int i = 0; i < lim; ++i) {
      B.a[i] = B.a[i] * 1ll * ((2 - int(B.a[i] * 1ll * A.a[i] % Mod) + Mod) % Mod) % Mod;
    }
    B.NTT(lim, true);
    int iv = qpow(lim, Mod - 2);
    for (int i = 0; i < now; ++i) {
      B.a[i] = B.a[i] * 1ll * iv % Mod;
    }
    memset(B.a + now, 0, sizeof(int) * now);
    now <<= 1;
  }
  B.deg = this->deg;
  return B;
}
Poly Poly::sqrt() {
  Poly A, B, I;
  B.a[0] = calc(this->a[0]);
  int now = 1;
  while ((now >> 1) <= this->deg) {
    for (int i = 0; i < now; ++i) {
      A.a[i] = this->a[i];
    }
    B.deg = now - 1;
    I = B.inv();
    int lim = now << 1;
    A.NTT(lim, false), B.NTT(lim, false), I.NTT(lim, false);
    for (int i = 0; i < lim; ++i) {
      B.a[i] = (B.a[i] + int(A.a[i] * 1ll * I.a[i] % Mod)) % Mod * 499122177ll % Mod;
    }
    B.NTT(lim, true);
    int iv = qpow(lim, Mod - 2);
    for (int i = 0; i < now; ++i) {
      B.a[i] = B.a[i] * 1ll * iv % Mod;
    }
    memset(B.a + now, 0, sizeof(int) * now);
    now <<= 1;
  }
  B.deg = this->deg;
  return B;
}
