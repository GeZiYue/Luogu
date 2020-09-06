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
#include <ctime>
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

const int N = 505;
const int inf = 1000000000;

void extend(int v);
void bfs(int u);

int dis[N][N];
int lx[N], ly[N];
bool vx[N], vy[N];
int slack[N];
int pre[N], matchx[N], matchy[N];
int n, m;

int main () {
  read(n), read(m);
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      dis[i][j] = -inf;
    }
  }
  for (int i = 1; i <= m; ++i) {
    int u, v, w;
    read(u), read(v), read(w);
    dis[u][v] = w;
  }
  for (int i = 1; i <= n; ++i) {
    lx[i] = 0;
    for (int j = 1; j <= n; ++j) {
      lx[i] = max(lx[i], dis[i][j]);
    }
  }
  for (int i = 1; i <= n; ++i) {
    bfs(i);
  }
  ll res = 0;
  for (int i = 1; i <= n; ++i) {
    res += dis[matchy[i]][i];
  }
  write(res), EL;
  for (int i = 1; i <= n; ++i) {
    write(matchy[i]), SP;
  }
  EL;
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

void extend(int v) {
  while (v) {
    int las = matchx[pre[v]];
    matchy[v] = pre[v];
    matchx[pre[v]] = v;
    v = las;
  }
}
void bfs(int s) {
  std::fill(vx + 1, vx + n + 1, 0);
  std::fill(vy + 1, vy + n + 1, 0);
  std::fill(slack + 1, slack + n + 1, inf);
  std::queue<int> q;
  q.push(s);
  while (true) {
    while (!q.empty()) {
      int u = q.front();
      vx[u] = true;
      q.pop();
      for (int i = 1; i <= n; ++i) {
        if (vy[i]) {
          continue;
        }
        int delta = lx[u] + ly[i] - dis[u][i];
        if (delta <= slack[i]) {
          pre[i] = u;
          if (delta == 0) {
            if (!matchy[i]) {
              extend(i);
              return;
            } else {
              vy[i] = true;
              q.push(matchy[i]);
            }
          } else {
            slack[i] = delta;
          }
        }
      }
    }
    int a = inf;
    for (int i = 1; i <= n; ++i) {
      if (!vy[i]) {
        a = min(a, slack[i]);
      }
    }
    if (a == iinf) {
      return;
    }
    for (int i = 1; i <= n; ++i) {
      if (vx[i]) {
        lx[i] -= a;
      }
      if (vy[i]) {
        ly[i] += a;
      } else {
        slack[i] -= a;
      }
    }
    for (int i = 1; i <= n; ++i) {
      if (!vy[i]) {
        if (slack[i] == 0) {
          if (!matchy[i]) {
            extend(i);
            return;
          } else {
            vy[i] = true;
            q.push(matchy[i]);
          }
        }
      }
    }
  }
}
