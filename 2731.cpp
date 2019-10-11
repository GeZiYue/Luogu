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
const int N = 505;
const int M = 2055;

void dfs(int);

int cnt[N][N];
int deg[N];
int n, m;
std::stack<int> s;

int main () {
  read(m);
  int st = iinf;
  for (int i = 1; i <= m; ++i) {
    int u, v;
    read(u), read(v);
    ++deg[u], ++deg[v];
    ++cnt[u][v], ++cnt[v][u];
    n = max(n, max(u, v));
    st = min(st, min(u, v));
  }
  for (int i = 1; i <= n; ++i) {
    if (deg[i] & 1) {
      st = i;
      break;
    }
  }
  dfs(st);
  while (!s.empty()) {
    write(s.top()), EL;
    s.pop();
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

void dfs(int u) {
  for (int i = 1; i <= n; ++i) {
    if (cnt[u][i]) {
      --cnt[u][i], --cnt[i][u];
      dfs(i);
    }
  }
  s.push(u);
}
