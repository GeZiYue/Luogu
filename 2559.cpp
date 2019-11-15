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
const int M = 20005;

void add(int, int, int);
void Dijkstra(int);

int hed[N], nxt[M], to[M], dis[M], id;
int h[10] = {0, 2, 6, 4, 8, 6, 10, 14};
int delta[N];

int main () {
  for (int i = 1; i <= 7; ++i) {
    int a;
    read(a);
    h[i] /= (a + 1);
  }
  int s, t;
  read(s), read(t);
  int m;
  read(m);
  for (int i = 1; i <= m; ++i) {
    int u, v, ty;
    read(u), read(v), read(ty);
    add(u, v, h[ty]);
    add(v, u, h[ty]);
  }
  Dijkstra(s);
  write(delta[t]), EL;
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
void Dijkstra(int s) {
  for (int i = 1; i <= 100; ++i) {
    delta[i] = iinf;
  }
  delta[s] = 0;
  std::priority_queue<pii, std::vector<pii>, std::greater<pii> > pq;
  pq.push(pii(0, s));
  while (!pq.empty()) {
    int u = pq.top().second;
    int d = pq.top().first;
    pq.pop();
    if (delta[u] != d) {
      continue;
    }
    for (int i = hed[u]; i; i = nxt[i]) {
      int v = to[i];
      if (d + dis[i] < delta[v]) {
        delta[v] = d + dis[i];
        pq.push(pii(delta[v], v));
      }
    }
  }
}
