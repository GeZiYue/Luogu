#include <algorithm>
#include <bitset>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
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
typedef const long long &cll;
typedef const int &ci;
typedef std::pair<int, int> pii;
const int iinf = 2147483647;
const ll llinf = 9223372036854775807ll;
using std::abs;
using std::max;
using std::min;
using std::sort;

const int N = 305;
const int Mod = 1000000007;

void add(int &a, int b) {
  a += b;
  if (a >= Mod) {
    a -= Mod;
  }
}
void sub(int &a, int b) {
  a -= b;
  if (a < 0) {
    a += Mod;
  }
}
int pow(int a, int b, int m);
int C(int n, int m);

int fac[N], ifac[N];
int inv[N];
int val[N];
bool vis[N];
int a[N], cnt;
int dp[N][N];
int n;

int main() {
  read(n);
  fac[0] = 1;
  for (int i = 1; i <= n; ++i) {
    fac[i] = fac[i - 1] * 1ll * i % Mod;
  }
  ifac[n] = pow(fac[n], Mod - 2, Mod);
  for (int i = n - 1; i >= 0; --i) {
    ifac[i] = ifac[i + 1] * 1ll * (i + 1) % Mod;
  }
  for (int i = 1; i <= n; ++i) {
    read(val[i]);
  }
  for (int i = 1; i <= n; ++i) {
    if (!vis[i]) {
      vis[i] = true;
      a[++cnt] = 1;
      for (int j = i + 1; j <= n; ++j) {
        if (!vis[j]) {
          ll tmp = val[i] * 1ll * val[j];
          ll sq = sqrt(tmp);
          if (sq * sq == tmp) {
            vis[j] = true;
            ++a[cnt];
          }
        }
      }
    }
  }
  int m = n;
  n = cnt;
  dp[0][0] = 1;
  for (int i = 1, s = 0; i <= n; ++i) {
    s += a[i];
    for (int j = i; j <= s; ++j) {
      for (int k = 1; k <= j && k <= a[i]; ++k) {
        add(dp[i][j], dp[i - 1][j - k] * 1ll * C(a[i] - 1, k - 1) % Mod *
                          fac[a[i]] % Mod * ifac[k] % Mod);
      }
    }
  }
  int ans = 0;
  for (int i = n; i <= m; ++i) {
    int now = fac[i] * 1ll * dp[n][i] % Mod;
    if ((m - i) & 1) {
      sub(ans, now);
    } else {
      add(ans, now);
    }
  }
  write(ans), EL;
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
int C(int n, int m) { return fac[n] * 1ll * ifac[m] % Mod * ifac[n - m] % Mod; }
