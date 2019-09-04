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
const int N = 1005;
const int M = 21005;

void add(int, int, int);
bool SPFA(int);

int hed[N], nxt[M], to[M], dis[M], id;
ll delta[N];
int cnt[N];
bool vis[N];
int Point;

int main () {
  int n, ml, md;
  read(n), read(ml), read(md);
  for (int i = 1; i < n; ++i) {
    add(i + 1, i, 0);
    add(0, i, 0);
  }
  for (int i = 1; i <= ml; ++i) {
    int a, b, d;
    read(a), read(b), read(d);
    add(a, b, d);
  }
  for (int i = 1; i <= md; ++i) {
    int a, b, d;
    read(a), read(b), read(d);
    add(b, a, -d);
  }
  Point = n;
  if (!SPFA(0)) {
    puts("-1");
    return 0;
  }
  SPFA(1);
  if (delta[n] == llinf) {
    puts("-2");
  } else {
    write(delta[n] - delta[1]), EL;
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

void add(int u, int v, int w) {
  nxt[++id] = hed[u];
  hed[u] = id;
  to[id] = v;
  dis[id] = w;
}
bool SPFA(int S) {
  for (int i = 1; i <= Point; ++i) {
    delta[i] = llinf;
    vis[i] = false;
    cnt[i] = 0;
  }
  delta[S] = 0;
  vis[S] = true;
  cnt[S] = 1;
  std::queue<int> q;
  q.push(S);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    vis[u] = false;
    for (int i = hed[u]; i; i = nxt[i]) {
      int v = to[i];
      if (delta[u] + dis[i] < delta[v]) {
        delta[v] = delta[u] + dis[i];
        if (++cnt[v] == Point) {
          return false;
        }
        if (!vis[v]) {
          vis[v] = true;
          q.push(v);
        }
      }
    }
  }
  return true;
}
