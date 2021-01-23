#include <bits/stdc++.h>

#define isNum(a) (a >= '0' && a <= '9')
#define SP putchar(' ')
#define EL putchar('\n')
#define File(a) freopen(a ".in", "r", stdin), freopen(a ".out", "w", stdout)

template <typename T>
void read(T &);
template <typename T>
void write(const T &);

typedef unsigned uint;
typedef long long ll;
typedef unsigned long long ull;
typedef std::pair<int, int> pii;
const int iinf = 2147483647;
const ll llinf = 9223372036854775807ll;

constexpr int N = 2100000;
constexpr int Mod = 998244353, g = 3;
constexpr int B = 66000;
typedef std::vector<int> Poly;

int C2(int n) { return 1ll * n * (n - 1) / 2 % (Mod - 1); }
int pow(int a, int b, int m);
void NTT(Poly &p, int lim, bool opt);
int pc(int n);
int ipc(int n);

int pwc[B], pwb[B];
int ipwc[B], ipwb[N];
int r[N], rt[N];
int a[N];
int n, c, m;

int main() {
  read(n), read(c), read(m);
  int ic = pow(c, Mod - 2, Mod);
  pwc[0] = 1, ipwc[0] = 1;
  for (int i = 1; i <= 65536; ++i) {
    pwc[i] = 1ll * pwc[i - 1] * c % Mod;
    ipwc[i] = 1ll * ipwc[i - 1] * ic % Mod;
  }
  pwb[0] = 1, ipwb[0] = 1;
  for (int i = 1; i < 65536; ++i) {
    pwb[i] = 1ll * pwb[i - 1] * pwc[65536] % Mod;
    ipwb[i] = 1ll * ipwb[i - 1] * ipwc[65536] % Mod;
  }
  --n;
  int lim = 1;
  while (lim < (n + m)) {
    lim <<= 1;
  }
  for (int l = 1; l < lim; l <<= 1) {
    int gn = pow(g, (Mod - 1) / (l << 1), Mod);
    rt[l] = 1;
    for (int i = 1; i < l; ++i) {
      rt[l | i] = 1ll * rt[l | (i - 1)] * gn % Mod;
    }
  }
  for (int i = 0; i < lim; ++i) {
    r[i] = (r[i >> 1] >> 1) | ((i & 1) * (lim >> 1));
  }
  Poly p1(lim), p2(lim);
  for (int i = 0; i <= n; ++i) {
    read(a[i]);
    p1[n - i] = 1ll * a[i] * ipc(C2(i)) % Mod;
  }
  for (int i = 0; i <= n + m; ++i) {
    p2[i] = pc(C2(i));
  }
  NTT(p1, lim, false), NTT(p2, lim, false);
  for (int i = 0; i < lim; ++i) {
    p1[i] = 1ll * p1[i] * p2[i] % Mod;
  }
  NTT(p1, lim, true);
  for (int i = 0; i < m; ++i) {
    write(1ll * p1[i + n] * ipc(C2(i)) % Mod), SP;
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
int pc(int n) { return 1ll * pwb[n >> 16] * pwc[n & 65535] % Mod; }
int ipc(int n) { return 1ll * ipwb[n >> 16] * ipwc[n & 65535] % Mod; }
void NTT(Poly &p, int lim, bool opt) {
  for (int i = 0; i < lim; ++i) {
    if (i < r[i]) {
      std::swap(p[i], p[r[i]]);
    }
  }
  for (int l = 1; l < lim; l <<= 1) {
    for (int i = 0; i < lim; i += (l << 1)) {
      for (int j = 0; j < l; ++j) {
        int x = p[i | j], y = 1ll * rt[l | j] * p[i | j | l] % Mod;
        p[i | j] = (x + y) % Mod;
        p[i | j | l] = (x - y + Mod) % Mod;
      }
    }
  }
  if (opt) {
    std::reverse(p.begin() + 1, p.begin() + lim);
    int iv = pow(lim, Mod - 2, Mod);
    for (int i = 0; i < lim; ++i) {
      p[i] = 1ll * p[i] * iv % Mod;
    }
  }
}

template <typename T>
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
template <typename T>
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
