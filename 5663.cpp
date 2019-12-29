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
typedef unsigned long long ull;
typedef const long long & cll;
typedef const int & ci;
typedef std::pair<int, int> pii;
const int iinf = 2147483647;
const ll llinf = 9223372036854775807ll;
using std::min;
using std::max;
using std::abs;
using std::sort;
const int N = 200005;
const int M = 400005;

void add(int, int);
void Dijkstra(int);

int hed[N], nxt[M], to[M], id;
int del[N];
int n, m, q;

int main () {
  read(n), read(m), read(q);
  for (int i = 1; i <= m; ++i) {
    int u, v;
    read(u), read(v);
    add(u, v + n);
    add(u + n, v);
    add(v, u + n);
    add(v + n, u);
  }
  Dijkstra(1);
  for (int i = 1; i <= q; ++i) {
    int u, num;
    read(u), read(num);
    puts((num >= del[u + ((num & 1) ? n : 0)]) ? "Yes" : "No");
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

void add(int u, int v) {
  nxt[++id] = hed[u];
  hed[u] = id;
  to[id] = v;
}
void Dijkstra(int S) {
  for (int i = 1; i <= (n << 1); ++i) {
    del[i] = iinf;
  }
  del[S] = 0;
  std::priority_queue<pii, std::vector<pii>, std::greater<pii> > pq;
  pq.push(pii(0, S));
  while (!pq.empty()) {
    int u = pq.top().second, d = pq.top().first;
    pq.pop();
    if (d != del[u]) {
      continue;
    }
    for (int i = hed[u]; i; i = nxt[i]) {
      int v = to[i];
      if (d + 1 < del[v]) {
        pq.push(pii(del[v] = d + 1, v));
      }
    }
  }
}
