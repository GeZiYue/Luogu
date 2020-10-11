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

const int N = 7505;

int pow(int a, int b, int m);
int calc(int i);

int dp[N];
int C[N][N];
int fac[N];
bool isp[N];
int flag[N];
int n, Mod, mod;

int main() {
  read(n), read(Mod);
  mod = Mod - 1;
  fac[0] = 1;
  for (int i = 1; i <= n; ++i) {
    fac[i] = fac[i - 1] * 1ll * i % mod;
  }
  C[0][0] = 1;
  for (int i = 1; i <= n; ++i) {
    C[i][0] = 1;
    for (int j = 1; j <= i; ++j) {
      C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
    }
  }
  isp[1] = true;
  for (int i = 2; i <= n; ++i) {
    if (!isp[i]) {
      for (int j = i * 2; j <= n; j += i) {
        isp[j] = true;
      }
      for (int j = i; j <= n; j *= i) {
        flag[j] = i;
      }
    }
  }
  int ans = 1;
  for (int i = 2; i <= n; ++i) {
    if (flag[i]) {
      ans = ans * 1ll * pow(flag[i], calc(i), Mod) % Mod;
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
int calc(int px) {
  int m = n / px;
  dp[0] = mod - 1;
  for (int i = 1; i <= m; ++i) {
    dp[i] = 0;
    for (int j = 1; j <= i; ++j) {
      dp[i] = (dp[i] -
               dp[i - j] * 1ll * C[i * px - 1][j * px - 1] % mod *
                   fac[j * px - 1] % mod +
               mod) %
              mod;
    }
  }
  int ans = 0;
  for (int i = 1; i <= m; ++i) {
    ans =
        (ans + dp[i] * 1ll * C[n][i * px] % mod * fac[n - i * px] % mod) % mod;
  }
  return ans;
}
