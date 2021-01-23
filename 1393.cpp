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

constexpr int N = 270005;
constexpr int Mod = 998244353, g = 3;

class Poly {
 public:
  int *a, deg;
  Poly() {
    a = new int[N];
    deg = 0;
  }
  void NTT(int lim, bool opt);
  Poly inv();
};
int r[N];

int pow(int a, int b, int m);

int str[N];
int nxt[N];
int n, m, S;

int main() {
  read(n), read(m), read(S);
  for (int i = 1; i <= S; ++i) {
    read(str[i]);
  }
  Poly c;
  for (int i = 2, j = 0; i <= S; ++i) {
    while (j && str[j + 1] != str[i]) {
      j = nxt[j];
    }
    if (str[j + 1] == str[i]) {
      ++j;
    }
    nxt[i] = j;
  }
  int cur = S;
  while (cur) {
    c.a[S - cur] = 1;
    cur = nxt[cur];
  }
  Poly F1;
  F1.a[0] = 1, F1.a[1] = Mod - m;
  int lim = 1;
  while (lim <= (n << 1)) {
    lim <<= 1;
  }
  for (int i = 0; i < lim; ++i) {
    r[i] = (r[i >> 1] >> 1) | ((i & 1) * (lim >> 1));
  }
  F1.NTT(lim, false), c.NTT(lim, false);
  for (int i = 0; i < lim; ++i) {
    F1.a[i] = 1ll * F1.a[i] * F1.a[i] % Mod * c.a[i] % Mod;
  }
  F1.NTT(lim, true);
  ++F1.a[S], F1.a[S + 1] = (F1.a[S + 1] - m + Mod) % Mod;
  F1.deg = n;
  F1 = F1.inv();
  write(1ll * F1.a[n - S] * pow(m, 1ll * n * (Mod - 2) % (Mod - 1), Mod) % Mod), EL;
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
    int iv = pow(lim, Mod - 2, Mod);
    std::reverse(a + 1, a + lim);
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
    for (int i = now + 1; i < lim; ++i) {
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
