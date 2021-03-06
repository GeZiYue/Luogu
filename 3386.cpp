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
const int M = 1000005;

void add(int, int);
bool essay(int);

int hed[N], nxt[M], to[M], id;
int mat[N];
bool use[N];
int ans;

int main () {
  int n, m, e;
  read(n), read(m), read(e);
  for (int i = 1; i <= e; ++i) {
    int u, v;
    read(u), read(v);
    if (u > n || v > m) {
      continue;
    }
    add(u, v);
  }
  for (int i = 1; i <= n; ++i) {
    memset(use, false, sizeof(use));
    ans += essay(i);
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

void add(int u, int v) {
  nxt[++id] = hed[u];
  hed[u] = id;
  to[id] = v;
}
bool essay(int u) {
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    if (!use[v]) {
      use[v] = true;
      if (!mat[v] || essay(mat[v])) {
        mat[v] = u;
        return true;
      }
    }
  }
  return false;
}
