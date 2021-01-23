#include <bits/stdc++.h>

#define isNum(a) (a >= '0' && a <= '9')
#define SP putchar(' ')
#define EL putchar('\n')
#define File(a) freopen(a ".in", "r", stdin), freopen(a ".out", "w", stdout)

template <class T>
void read(T &);
template <class T>
void write(const T &);

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

constexpr int N = 270000;
constexpr int Mod = 167772161, g = 3;

class Poly {
 public:
  int *a;
  int deg;
  Poly() {
    a = new int[N];
    memset(a, 0, sizeof(int) * (N - 1));
  }
  void NTT(int lim, bool opt);
  Poly inv();
  Poly drv();
  Poly itg();
  Poly ln();
  Poly exp();
  Poly pow(int k);
};
int r[N];

int add(int a, int b) { return (a += b) >= Mod ? a - Mod : a; }
int sub(int a, int b) { return (a -= b) < 0 ? a + Mod : a; }
int qpow(int, int);

Poly A;
int fac[N], ifac[N];
int n, k;

int main() {
  read(n), read(k);
  if (n < k) {
    for (int i = 0; i <= n; ++i) {
      write(0), SP;
    }
    EL;
    return 0;
  }
  fac[0] = 1;
  for (int i = 1; i <= n; ++i) {
    fac[i] = fac[i - 1] * 1ll * i % Mod;
  }
  ifac[n] = qpow(fac[n], Mod - 2);
  for (int i = n - 1; i >= 0; --i) {
    ifac[i] = ifac[i + 1] * 1ll * (i + 1) % Mod;
  }
  Poly F;
  F.deg = n - k;
  for (int i = 0; i <= n - k; ++i) {
    F.a[i] = ifac[i + 1];
  }
  Poly G = F.pow(k);
  for (int i = 0; i < k; ++i) {
    write(0), SP;
  }
  for (int i = k; i <= n; ++i) {
    write(G.a[i - k] * 1ll * fac[i] % Mod * ifac[k] % Mod), SP;
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
void Poly::NTT(int lim, bool opt) {
  for (int i = 0; i < lim; ++i) {
    if (i < r[i]) {
      std::swap(a[i], a[r[i]]);
    }
  }
  for (int l = 1; l < lim; l <<= 1) {
    int gw = qpow(g, (Mod - 1) / (l << 1));
    for (int i = 0; i < lim; i += (l << 1)) {
      for (int j = 0, gn = 1; j < l; ++j, gn = gn * 1ll * gw % Mod) {
        int x = a[i + j], y = a[i + j + l] * 1ll * gn % Mod;
        a[i + j] = add(x, y);
        a[i + j + l] = sub(x, y);
      }
    }
  }
  if (opt) {
    std::reverse(a + 1, a + lim);
    int iv = qpow(lim, Mod - 2);
    for (int i = 0; i < lim; ++i) {
      a[i] = a[i] * 1ll * iv % Mod;
    }
  }
}
Poly Poly::inv() {
  Poly A, B, ans;
  int now = 1;
  ans.a[0] = qpow(this->a[0], Mod - 2);
  ans.deg = this->deg;
  while ((now >> 1) <= deg) {
    for (int i = 0; i < now; ++i) {
      A.a[i] = this->a[i];
      B.a[i] = ans.a[i];
    }
    int lim = now << 1;
    for (int i = 0; i < lim; ++i) {
      r[i] = (r[i >> 1] >> 1) | ((i & 1) * now);
    }
    A.NTT(lim, false), B.NTT(lim, false);
    for (int i = 0; i < lim; ++i) {
      ans.a[i] = B.a[i] * 1ll * sub(2, int(B.a[i] * 1ll * A.a[i] % Mod)) % Mod;
    }
    ans.NTT(lim, true);
    for (int i = now; i < lim; ++i) {
      ans.a[i] = 0;
    }
    now <<= 1;
  }
  for (int i = ans.deg + 1; i < (now >> 1); ++i) {
    ans.a[i] = 0;
  }
  return ans;
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
    ans.a[i] = this->a[i - 1] * 1ll * qpow(i, Mod - 2) % Mod;
  }
  return ans;
}
Poly Poly::ln() {
  Poly A = this->inv(), B = this->drv();
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
  for (int i = this->deg; i < lim; ++i) {
    A.a[i] = 0;
  }
  return A.itg();
}
Poly Poly::exp() {
  Poly A, B, L, ans;
  int now = 1;
  ans.a[0] = 1, ans.deg = this->deg;
  while ((now >> 1) <= this->deg) {
    for (int i = 0; i < now; ++i) {
      A.a[i] = this->a[i];
      B.a[i] = ans.a[i];
    }
    B.deg = now - 1;
    L = B.ln();
    int lim = now << 1;
    for (int i = 0; i < lim; ++i) {
      r[i] = (r[i >> 1] >> 1) | ((i & 1) * now);
    }
    A.NTT(lim, false), B.NTT(lim, false), L.NTT(lim, false);
    for (int i = 0; i < lim; ++i) {
      ans.a[i] = B.a[i] * 1ll * sub(add(1, A.a[i]), L.a[i]) % Mod;
    }
    ans.NTT(lim, true);
    for (int i = now; i < lim; ++i) {
      ans.a[i] = 0;
    }
    now <<= 1;
  }
  for (int i = ans.deg + 1; i < (now >> 1); ++i) {
    ans.a[i] = 0;
  }
  return ans;
}
Poly Poly::pow(int k) {
  Poly ans = this->ln();
  for (int i = 0; i <= ans.deg; ++i) {
    ans.a[i] = ans.a[i] * 1ll * k % Mod;
  }
  return ans.exp();
}
