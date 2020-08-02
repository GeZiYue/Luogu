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

const int N = 530000;
const int Mod = 167772161, g = 3;

class Polynomial {
public:
  int deg, *a;
  Polynomial() {
    a = new int[N];
    memset(a, 0, sizeof(int) * N);
  }
  void NTT(int, bool);
};
int r[N];
int pow(int, int, int);
Polynomial solve(int);

int fac[N], ifac[N];
int omega[26];
int siz;

int main () {
  int n;
  read(n);
  int lim = 1;
  while (lim <= (n << 1)) {
    lim <<= 1;
  }
  siz = __builtin_ctz(lim);
  omega[25] = pow(g, (Mod - 1) >> 25, Mod);
  for (int i = 24; i >= 0; --i) {
    omega[i] = omega[i + 1] * 1ll * omega[i + 1] % Mod;
  }
  for (int i = 0; i < lim; ++i) {
    r[i] = (r[i >> 1] >> 1) | ((i & 1) * (lim >> 1));
  }
  fac[0] = 1;
  for (int i = 1; i <= lim; ++i) {
    fac[i] = fac[i - 1] * 1ll * i % Mod;
  }
  ifac[lim] = pow(fac[lim], Mod - 2, Mod);
  for (int i = lim - 1; i >= 0; --i) {
    ifac[i] = ifac[i + 1] * 1ll * (i + 1) % Mod;
  }
  Polynomial ans = solve(n);
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

int pow(int a, int b, int m) {
  int ans = 1, now = a % m;
  while (b) {
    if (b & 1) {
      ans = ans * 1ll * now % m;
    }
    now = now * 1ll * now % m;
    b >>= 1;
  }
  return ans;
}
void Polynomial::NTT(int lim, bool opt) {
  if (opt) {
    std::reverse(a + 1, a + lim);
  }
  int tp = siz - __builtin_ctz(lim);
  for (int i = 0; i < lim; ++i) {
    if (i < (r[i] >> tp)) {
      std::swap(a[i], a[r[i] >> tp]);
    }
  }
  for (int l = 1, t = 1; l < lim; l <<= 1, ++t) {
    int gw = omega[t];
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
void calc(const Polynomial &f, int n, int lim, Polynomial &g) {
  Polynomial h;
  memset(g.a + n + 1, 0, sizeof(int) * (lim - n));
  g.a[0] = 1, h.a[0] = f.a[0];
  for (int i = 1; i <= n; ++i) {
    g.a[i] = g.a[i - 1] * 1ll * n % Mod;
    h.a[i] = f.a[i] * 1ll * fac[i] % Mod;
  }
  for (int i = 1; i <= n; ++i) {
    g.a[i] = g.a[i] * 1ll * ifac[i] % Mod;
  }
  std::reverse(g.a, g.a + n + 1);
  g.NTT(lim, false), h.NTT(lim, false);
  for (int i = 0; i < lim; ++i) {
    g.a[i] = g.a[i] * 1ll * h.a[i] % Mod;
  }
  g.NTT(lim, true);
  for (int i = 0; i <= n; ++i) {
    g.a[i] = g.a[i + n] * 1ll * ifac[i] % Mod;
  }
  memset(g.a + n + 1, 0, sizeof(int) * (lim - n));
}
Polynomial solve(int n) {
  std::stack<bool> S;
  while (n) {
    S.push(n & 1);
    n >>= 1;
  }
  int lim = 1;
  Polynomial A, B;
  n = A.a[1] = S.top();
  S.pop();
  while (!S.empty()) {
    while (lim <= (n << 1)) {
      lim <<= 1;
    }
    calc(A, n, lim, B);
    A.NTT(lim, false), B.NTT(lim, false);
    for (int i = 0; i < lim; ++i) {
      A.a[i] = A.a[i] * 1ll * B.a[i] % Mod;
    }
    A.NTT(lim, true);
    n <<= 1;
    if (!S.top()) {
      S.pop();
      continue;
    }
    S.pop();
    A.a[n + 1] = A.a[n];
    for (int i = n; i > 0; --i) {
      A.a[i] = (A.a[i - 1] + A.a[i] * 1ll * n % Mod) % Mod;
    }
    A.a[0] = A.a[0] * 1ll * n % Mod;
    ++n;
  }
  A.deg = n;
  return A;
}
