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
const int N = 5005;
const int M = 100005;

void add(int, int);
void dfs(int);

int hed[N], nxt[M], to[M], id;
int dfn[N], low[N], cnt;
bool ins[N];
std::vector<std::vector<int> > v;
std::stack<int> st;

int main () {
  int n, m;
  read(n), read(m);
  for (int i = 1; i <= m; ++i) {
    int u, v, type;
    read(u), read(v), read(type);
    add(u, v);
    if (type ^ 1) {
      add(v, u);
    }
  }
  for (int i = 1; i <= n; ++i) {
    if (!dfn[i]) {
      dfs(i);
    }
  }
  for (auto i : v) {
    sort(i.begin(), i.end());
  }
  std::vector<int> ans = v[0];
  for (int i = 1; i < (int)v.size(); ++i) {
    ans = [](const std::vector<int> &i, const std::vector<int> &j) {
      if (i.size() < j.size()) {
        return j;
      }
      if (i.size() > j.size()) {
        return i;
      }
      int now = i.size();
      for (int k = 0; k < now; ++k) {
        if (i[k] < j[k]) {
          return i;
        }
        if (i[k] > j[k]) {
          return j;
        }
      }
      return i;
    }(ans, v[i]);
  }
  sort(ans.begin(), ans.end());
  write(ans.size()), EL;
  for (auto i : ans) {
    write(i), SP;
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

void add(int u, int v) {
  nxt[++id] = hed[u];
  hed[u] = id;
  to[id] = v;
}
void dfs(int u) {
  dfn[u] = low[u] = ++cnt;
  st.push(u);
  ins[u] = true;
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    if (dfn[v]) {
      if (ins[v]) {
        low[u] = min(low[u], dfn[v]);
      }
    } else {
      dfs(v);
      low[u] = min(low[u], low[v]);
    }
  }
  if (low[u] == dfn[u]) {
    std::vector<int> now;
    int i;
    do {
      i = st.top();
      st.pop();
      ins[i] = false;
      now.push_back(i);
    } while(i != u);
    v.push_back(now);
  }
}
