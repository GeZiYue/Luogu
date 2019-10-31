#include <unordered_set>
#include <unordered_map>
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
typedef const long long & cll;
typedef const int & ci;
typedef std::pair<int, int> pii;
const int iinf = 2147483647;
const ll llinf = 9223372036854775807ll;
using std::min;
using std::max;
using std::abs;
using std::sort;
const int N = 105;

bool check(int);

int d1[N], d2[N];
int dp[2][N];
int n, m;

int main () {
  read(n), read(m);
  for (int i = 1; i <= n; ++i) {
    read(d1[i]), read(d2[i]);
  }
  int l = 1, r = (int)1e6;
  int ans = 0;
  while (l <= r) {
    int mid = (l + r) >> 1;
    if (check(mid)) {
      ans = mid;
      r = mid - 1;
    } else {
      l = mid + 1;
    }
  }
  write(ans), EL;
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

bool check(int x) {
  int now = 0;
  for (int i = 1; i <= m; ++i) {
    dp[now][i] = -1e5;
  }
  dp[now][0] = 0;
  for (int i = 1; i <= n; ++i) {
    now ^= 1;
    for (int j = 0; j <= m; ++j) {
      dp[now][j] = -1e5;
    }
    for (int j = 0; j * d1[i] <= x; ++j) {
      for (int k = j; k <= m; ++k) {
        dp[now][k] = max(dp[now][k], dp[now ^ 1][k - j] + (x - j * d1[i]) / d2[i]);
      }
    }
  }
  return dp[now][m] >= m;
}
