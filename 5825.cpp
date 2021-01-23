#include <algorithm>
#include <bitset>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <iterator>
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
typedef unsigned long long ull;
typedef const long long &cll;
typedef const int &ci;
typedef std::pair<int, int> pii;
const int iinf = 2147483647;
const ll llinf = 9223372036854775807ll;
using std::abs;
using std::max;
using std::min;

constexpr int N = 530000;
constexpr int Mod = 998244353, g = 3;
constexpr int sgn[] = {1, Mod - 1};

class Poly {
 public:
  int *a, deg;
  Poly() {
    deg = 0;
    a = new int[N];
    memset(a, 0, sizeof(int) * N);
  }
  void NTT(int lim, bool opt);
};
int r[N];

int pow(int a, int b, int m);
int C(int n, int m);

int fac[N], ifac[N];
int n;

int main() {
  read(n);
  fac[0] = 1;
  for (int i = 1; i <= n + 1; ++i) {
    fac[i] = fac[i - 1] * 1ll * i % Mod;
  }
  ifac[n + 1] = pow(fac[n + 1], Mod - 2, Mod);
  for (int i = n; i >= 0; --i) {
    ifac[i] = ifac[i + 1] * 1ll * (i + 1) % Mod;
  }
  Poly F, G;
  for (int i = 0; i <= n; ++i) {
    F.a[i] = C(n + 1, i) * 1ll * sgn[i & 1] % Mod;
  }
  for (int i = 0; i <= n; ++i) {
    G.a[i] = pow(i + 1, n, Mod);
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
    F.a[i] = F.a[i] * 1ll * G.a[i] % Mod;
  }
  F.NTT(lim, true);
  for (int i = 0; i <= n; ++i) {
    write(F.a[i]), SP;
  }
  EL;
  return 0;
}

int pow(int a, int b, int m) {
  int ans = 1, now = a;
  while (b) {
    if (b & 1) {
      ans = ans * 1ll * now % m;
    }
    now = now * 1ll * now % m;
    b >>= 1;
  }
  return ans;
}
int C(int n, int m) { return fac[n] * 1ll * ifac[m] % Mod * ifac[n - m] % Mod; }

void Poly::NTT(int lim, bool opt) {
  for (int i = 0; i < lim; ++i) {
    if (i < r[i]) {
      std::swap(a[i], a[r[i]]);
    }
  }
  for (int l = 1; l < lim; l <<= 1) {
    int gn = pow(g, (Mod - 1) / (l << 1), Mod);
    for (int i = 0; i < lim; i += (l << 1)) {
      for (int j = 0, gw = 1; j < l; ++j, gw = gw * 1ll * gn % Mod) {
        int x = a[i | j], y = a[i | j | l] * 1ll * gw % Mod;
        a[i | j] = (x + y) % Mod;
        a[i | j | l] = (x - y + Mod) % Mod;
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
