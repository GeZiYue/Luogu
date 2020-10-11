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

const int N = 505;

bool match(int x);
bool check(int x);

bool ok[N][N], f[N][N];
bool vis[N];
int mat[N];
int val[N];
int n, m;

int main() {
  read(m), read(n);
  for (int i = 1; i <= n; ++i) {
    read(val[i]);
    int k;
    read(k);
    for (int j = 1; j <= k; ++j) {
      int v;
      read(v);
      ok[i][v] = true;
    }
  }
  for (int k = 1; k <= n; ++k) {
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= n; ++j) {
        ok[i][j] |= (ok[i][k] & ok[k][j]);
      }
    }
  }
  int tot;
  std::vector<int> V;
  for (int i = 1; i <= n; ++i) {
    V.push_back(val[i]);
  }
  std::sort(V.begin(), V.end());
  V.erase(std::unique(V.begin(), V.end()), V.end());
  tot = V.size();
  for (int i = 1; i <= n; ++i) {
    val[i] = std::lower_bound(V.begin(), V.end(), val[i]) - V.begin() + 1;
  }
  int l = 0, r = tot + 1;
  int ans = 0;
  while (l <= r) {
    int mid = (l + r) >> 1;
    if (check(mid)) {
      ans = mid;
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }
  if (ans > tot) {
    puts("AK");
  } else {
    write(V[ans - 1]), EL;
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

bool match(int x) {
  for (int i = 1; i <= n; ++i) {
    if (x == i) {
      continue;
    }
    if (f[x][i] && !vis[i]) {
      vis[i] = true;
      if (!mat[i] || match(mat[i])) {
        mat[i] = x;
        return true;
      }
    }
  }
  return false;
}
bool check(int x) {
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      if (val[i] < x && val[j] < x) {
        f[i][j] = ok[i][j];
      } else {
        f[i][j] = false;
      }
    }
  }
  int ans = 0;
  memset(mat, false, sizeof(mat));
  for (int i = 1; i <= n; ++i) {
    if (val[i] < x) {
      memset(vis, false, sizeof(vis));
      ++ans;
      ans -= match(i);
    }
  }
  return ans <= m + 1;
}
