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

bool vis[N];
int a[N], cnt;
int dp[2][N][N];
int n;

int main() {
  read(n);
  for (int i = 1; i <= n; ++i) {
    read(a[i]);
  }
  for (int i = 1; i <= n; ++i) {
    if (!vis[i]) {
      vis[i] = true;
      ++cnt;
      for (int j = i + 1; j <= n; ++j) {
        if (!vis[j]) {
          ll tmp = a[i] * 1ll * a[j];
          ll sq = sqrt(tmp);
          if (sq * sq == tmp) {
            vis[j] = true;
            a[j] = cnt;
          }
        }
      }
      a[i] = cnt;
    }
  }
  std::sort(a + 1, a + n + 1);
  dp[0][0][0] = 1;
  int pre = 0, cur = 1;
  for (int i = 1, now = 0; i <= n; ++i) {
    memset(dp[cur], 0, sizeof(dp[cur]));
    if (a[i] != a[i - 1]) {
      for (int j = 0; j < i; ++j) {
        for (int k = 0; k <= j; ++k) {
          add(dp[cur][j][0], dp[pre][k][j - k] * 1ll * (i - j) % Mod);
        }
        for (int k = 0; k <= j + 1; ++k) {
          add(dp[cur][j][0], dp[pre][k][j - k + 1] * 1ll * (j + 1) % Mod);
        }
      }
      now = 0;
    } else {
      for (int j = 0; j < i; ++j) {
        for (int k = 1; k <= now; ++k) {
          add(dp[cur][j][k], dp[pre][j][k - 1] * 1ll * (2 * now - k + 1) % Mod);
        }
        for (int k = 0; k <= now; ++k) {
          add(dp[cur][j][k], dp[pre][j + 1][k] * 1ll * (j + 1) % Mod);
        }
        for (int k = 0; k <= now; ++k) {
          if (i - 2 * now + k - j > 0) {
            add(dp[cur][j][k],
                dp[pre][j][k] * 1ll * (i - 2 * now + k - j) % Mod);
          }
        }
      }
    }
    ++now;
    pre ^= 1, cur ^= 1;
  }
  write(dp[pre][0][0]), EL;
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
