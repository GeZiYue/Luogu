#include <algorithm>
#include <bitset>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
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

template <class T> void read(T &);
template <class T> void write(const T &);

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

const int N = 105;
const int M = 200000;
const int Mod = 1000003;

int pow(int a, int b, int m);
int det(int n);

int a[N][N];
int deg[N];
int fac[M + 5];
int n;

int main() {
  fac[0] = 1;
  for (int i = 1; i <= M; ++i) {
    fac[i] = fac[i - 1] * 1ll * i % Mod;
  }
  int T;
  read(T);
  while (T--) {
    memset(a, 0, sizeof(a));
    read(n);
    for (int i = 1; i <= n; ++i) {
      read(deg[i]);
      a[i][i] = deg[i];
      for (int j = 1; j <= deg[i]; ++j) {
        int v;
        read(v);
        --a[i][v];
      }
    }
    if (n == 1) {
      write(fac[deg[1]]), EL;
      continue;
    }
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= n; ++j) {
        a[i][j] = (a[i][j] + Mod) % Mod;
      }
    }
    int res = deg[1] * 1ll * det(n - 1) % Mod;
    for (int i = 1; i <= n; ++i) {
      res = res * 1ll * fac[deg[i] - 1] % Mod;
    }
    write(res), EL;
  }
  return 0;
}

template <class T> inline void read(T &Re) {
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
template <class T> inline void write(const T &Wr) {
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
int det(int n) {
  int ans = 1;
  for (int i = 1; i <= n; ++i) {
    for (int j = i + 1; j <= n; ++j) {
      while (a[j][i]) {
        int t = a[i][i] / a[j][i];
        for (int k = 1; k <= n; ++k) {
          a[i][k] = (a[i][k] - a[j][k] * 1ll * t % Mod + Mod) % Mod;
        }
        std::swap(a[i], a[j]);
        ans = Mod - ans;
      }
    }
  }
  for (int i = 1; i <= n; ++i) {
    ans = ans * 1ll * a[i][i] % Mod;
  }
  return ans;
}
