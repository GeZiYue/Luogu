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
const int N = 55;

bool ok[N][N][35];
unsigned int dis[N][N];

int main () {
  int n, m;
  read(n), read(m);
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      dis[i][j] = iinf;
    }
  }
  for (int i = 1; i <= m; ++i) {
    int u, v;
    read(u), read(v);
    ok[u][v][0] = true;
    dis[u][v] = 1;
  }
  for (int l = 1; l <= 32; ++l) {
    for (int k = 1; k <= n; ++k) {
      for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
          if (ok[i][k][l - 1] && ok[k][j][l - 1]) {
            ok[i][j][l] = true;
            dis[i][j] = 1;
          }
        }
      }
    }
  }
  for (int k = 1; k <= n; ++k) {
    for (int i = 1; i <= n; ++i) {
      if (i == k) {
        continue;
      }
      for (int j = 1; j <= n; ++j) {
        if (j == k || j == i) {
          continue;
        }
        dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
      }
    }
  }
  write(dis[1][n]), EL;
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
