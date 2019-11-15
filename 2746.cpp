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
const int M = 10005;

void add(int, int);
void tarjan(int);

int n;
int hed[N], nxt[M], to[M], id;

int col[N], ccnt;
bool ins[N];
std::stack<int> sta;
int dfn[N], low[N], cnt;

int indeg[N], outdeg[N];

int main () {
  read(n);
  for (int u = 1; u <= n; ++u) {
    int v;
    read(v);
    while (v) {
      add(u, v);
      read(v);
    }
  }
  for (int i = 1; i <= n; ++i) {
    if (!dfn[i]) {
      tarjan(i);
    }
  }
  for (int u = 1; u <= n; ++u) {
    for (int i = hed[u]; i; i = nxt[i]) {
      int v = to[i];
      if (col[u] ^ col[v]) {
        ++outdeg[col[u]];
        ++indeg[col[v]];
      }
    }
  }
  if (ccnt == 1) {
    write(1), EL, write(0), EL;
    return 0;
  }
  int in = 0, out = 0;
  for (int i = 1; i <= ccnt; ++i) {
    in += indeg[i] == 0;
    out += outdeg[i] == 0;
  }
  write(in), EL, write(max(in, out)), EL;
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
void tarjan(int u) {
  dfn[u] = low[u] = ++cnt;
  ins[u] = true;
  sta.push(u);
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    if (!dfn[v]) {
      tarjan(v);
      low[u] = min(low[u], low[v]);
    } else {
      if (ins[v]) {
        low[u] = min(low[u], dfn[v]);
      }
    }
  }
  if (low[u] == dfn[u]) {
    int i;
    ++ccnt;
    do {
      i = sta.top();
      sta.pop();
      ins[i] = false;
      col[i] = ccnt;
    } while (i != u);
  }
}
