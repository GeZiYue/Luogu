#include <bits/stdc++.h>

#define isNum(a) (a >= '0' && a <= '9')
#define SP putchar(' ')
#define EL putchar('\n')
#define File(a) freopen(a ".in", "r", stdin), freopen(a ".out", "w", stdout)

template <class T>
void read(T &);
template <class T>
void write(const T &);

typedef unsigned uint;
typedef long long ll;
typedef unsigned long long ull;
typedef std::pair<int, int> pii;
const int iinf = 2147483647;
const ll llinf = 9223372036854775807ll;

constexpr int N = 530000;
constexpr int Mod = 998244353, g = 3;

class Poly {
 public:
  int *a, deg;
  Poly() {
    a = new int[N];
    memset(a, 0, sizeof(int) * N);
  }
  void NTT(int lim, bool opt);
  Poly inv();
};
int r[N];

int pow(int a, int b, int m);

int a[N];
int fac[N], ifac[N];
int ans[N];
int n;

int main() {
  read(n);
  for (int i = 0; i <= n; ++i) {
    read(a[i]);
  }
  fac[0] = 1;
  for (int i = 1; i <= n + 1; ++i) {
    fac[i] = 1ll * fac[i - 1] * i % Mod;
  }
  ifac[n + 1] = pow(fac[n + 1], Mod - 2, Mod);
  for (int i = n; i >= 0; --i) {
    ifac[i] = 1ll * ifac[i + 1] * (i + 1) % Mod;
  }
  Poly B;
  for (int i = 0; i <= n; ++i) {
    B.a[i] = ifac[i + 1];
  }
  B.deg = n;
  B = B.inv();
  Poly F, G;
  for (int i = 0; i <= n; ++i) {
    F.a[i] = B.a[n - i];
    G.a[i] = 1ll * a[i] * fac[i] % Mod;
  }
  int lim = 1;
  while (lim <= (n << 1)) {
    lim <<= 1;
  }
  for (int i = 0; i < lim; ++i) {
    r[i] = (r[i >> 1] >> 1) | ((i & 1) * (lim >> 1));
  }
  F.NTT(lim, false), G.NTT(lim, false);
  for (int i = 0; i < lim; ++i) {
    F.a[i] = 1ll * F.a[i] * G.a[i] % Mod;
  }
  F.NTT(lim, true);
  for (int i = 0; i <= n; ++i) {
    ans[i + 1] = 1ll * F.a[n + i] * ifac[i + 1] % Mod;
  }
  for (int i = 0; i <= n; ++i) {
    ans[i] = (ans[i] + a[i]) % Mod;
  }
  for (int i = 0; i <= n + 1; ++i) {
    write(ans[i]), SP;
  }
  EL;
  return 0;
}

int pow(int a, int b, int m) {
  int ans = 1, now = a;
  while (b) {
    if (b & 1) {
      ans = 1ll * ans * now % m;
    }
    now = 1ll * now * now % m;
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
      for (int j = 0, gw = 1; j < l; ++j, gw = 1ll * gw * gn % Mod) {
        int x = a[i | j], y = 1ll * a[i | j | l] * gw % Mod;
        a[i | j] = (x + y) % Mod;
        a[i | j | l] = (x - y + Mod) % Mod;
      }
    }
  }
  if (opt) {
    std::reverse(a + 1, a + lim);
    int iv = pow(lim, Mod - 2, Mod);
    for (int i = 0; i < lim; ++i) {
      a[i] = 1ll * a[i] * iv % Mod;
    }
  }
}
Poly Poly::inv() {
  Poly A, B;
  B.a[0] = pow(a[0], Mod - 2, Mod);
  int now = 1;
  while (now <= (deg << 1)) {
    for (int i = 0; i < now; ++i) {
      A.a[i] = a[i];
    }
    int lim = now << 1;
    for (int i = 0; i < lim; ++i) {
      r[i] = (r[i >> 1] >> 1) | ((i & 1) * now);
    }
    A.NTT(lim, false), B.NTT(lim, false);
    for (int i = 0; i < lim; ++i) {
      B.a[i] = (2 - 1ll * B.a[i] * A.a[i] % Mod + Mod) * B.a[i] % Mod;
    }
    B.NTT(lim, true);
    for (int i = now; i < lim; ++i) {
      B.a[i] = 0;
    }
    now <<= 1;
  }
  B.deg = deg;
  for (int i = deg + 1; i < now; ++i) {
    B.a[i] = 0;
  }
  return B;
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
