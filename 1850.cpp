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
const int N = 2005;
const int M = 305;
const int dinf = 30001;
const double finf = 40000001;

int dis[M][M];
int c[N], d[N];
double k[N], f[N][N][2];

int main () {
  int n, m, v, e;
  read(n), read(m), read(v), read(e);
  for (int i = 1; i <= n; ++i) {
    read(c[i]);
  }
  for (int i = 1; i <= n; ++i) {
    read(d[i]);
  }
  for (int i = 1; i <= n; ++i) {
    scanf("%lf", &k[i]);
  }
  for (int i = 1; i <= v; ++i) {
    for (int j = 1; j <= v; ++j) {
      if (i ^ j) {
        dis[i][j] = dinf;
      }
    }
  }
  for (int i = 1; i <= e; ++i) {
    int u, v, w;
    read(u), read(v), read(w);
    dis[u][v] = dis[v][u] = min(dis[v][u], w);
  }
  for (int k = 1; k <= v; ++k) {
    for (int i = 1; i <= v; ++i) {
      if (i == k) {
        continue;
      }
      for (int j = 1; j <= v; ++j) {
        if (j == k || j == i) {
          continue;
        }
        dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
      }
    }
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j <= m; ++j) {
      f[i][j][0] = f[i][j][1] = finf;
    }
  }
  f[1][0][0] = f[1][1][1] = 0;
  for (int i = 2; i <= n; ++i) {
    f[i][0][0] = f[i - 1][0][0] + dis[c[i - 1]][c[i]];
    for (int j = 1; j <= min(i, m); ++j) {
      f[i][j][0] = min(
        f[i - 1][j][0] + dis[c[i - 1]][c[i]],
        f[i - 1][j][1] + k[i - 1] * dis[d[i - 1]][c[i]] + (1 - k[i - 1]) * (dis[c[i - 1]][c[i]])
      );
      f[i][j][1] = min(
        f[i - 1][j - 1][0] + k[i] * dis[c[i - 1]][d[i]] + (1 - k[i]) * dis[c[i - 1]][c[i]],
        f[i - 1][j - 1][1] +
        k[i - 1] * k[i] * dis[d[i - 1]][d[i]] +
        (1 - k[i - 1]) * k[i] * dis[c[i - 1]][d[i]] +
        k[i - 1] * (1 - k[i]) * dis[d[i - 1]][c[i]] +
        (1 - k[i - 1]) * (1 - k[i]) * dis[c[i - 1]][c[i]]
      );
    }
  }
  double ans = finf;
  for (int i = 0; i <= m; ++i) {
    ans = min(ans, min(f[n][i][0], f[n][i][1]));
  }
  printf("%.2lf\n", ans);
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
