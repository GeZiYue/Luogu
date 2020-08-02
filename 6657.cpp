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

const int N = 2000005;
const int M = 105;
const int Mod = 998244353;

int pow(int a, int b, int m);
int C(int n, int m);
int det(int n);

int fac[N], ifac[N];
int a[M], b[M];
int f[M][M];
int n, m;

int main () {
  fac[0] = 1;
  for (int i = 1; i <= 2000000; ++i) {
    fac[i] = fac[i - 1] * 1ll * i % Mod;
  }
  ifac[2000000] = pow(fac[2000000], Mod - 2, Mod);
  for (int i = 1999999; i >= 0; --i) {
    ifac[i] = ifac[i + 1] * 1ll * (i + 1) % Mod;
  }
  int t;
  read(t);
  while (t--) {
    read(n), read(m);
    for (int i = 1; i <= m; ++i) {
      read(a[i]), read(b[i]);
    }
    for (int i = 1; i <= m; ++i) {
      for (int j = 1; j <= m; ++j) {
        f[i][j] = C(b[j] - a[i] + n - 1, n - 1);
      }
    }
    write(det(m)), EL;
  }
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
int C(int n, int m) {
  if (n < m) {
    return 0;
  }
  return fac[n] * 1ll * ifac[m] % Mod * ifac[n - m] % Mod;
}
int det(int n) {
  int ans = 1;
  bool flag = false;
  for (int i = 1; i <= n; ++i) {
    int now = 0;
    for (int j = i; j <= n; ++j) {
      if (f[j][i]) {
        now = j;
        break;
      }
    }
    if (!now) {
      return 0;
    }
    if (now != i) {
      std::swap(f[i], f[now]);
      flag ^= 1;
    }
    int iv = pow(f[i][i], Mod - 2, Mod);
    for (int j = i + 1; j <= n; ++j) {
      int kj = f[j][i] * 1ll * iv % Mod;
      for (int k = i; k <= n; ++k) {
        f[j][k] = (f[j][k] - f[i][k] * 1ll * kj % Mod + Mod) % Mod;
      }
    }
    ans = ans * 1ll * f[i][i] % Mod;
  }
  if (flag) {
    ans = Mod - ans;
  }
  return ans;
}
