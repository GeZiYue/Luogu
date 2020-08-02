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

const int N = 100005;

namespace ACAM {
  int to[N][26];
  int fa[N];
  int fail[N];
  int end[N];
  int id = 1;
  int tot;
  void insert(char);
  void build();

}
namespace Graph {
  int hed[N], nxt[N], to[N], id;
  void add(int, int);
}
namespace BIT {
  int sum[N];
  void update(int, int);
  int query(int);
}

void dfs(int);

std::vector<int> qry[N];
int x[N];
int dfn[N], siz[N], id;
int ans[N];
char ch[N];

int main () {
  scanf("%s", ch + 1);
  int n = strlen(ch + 1);
  for (int i = 1; i <= n; ++i) {
    ACAM::insert(ch[i]);
  }
  ACAM::build();
  dfs(1);
  int q;
  read(q);
  for (int i = 1; i <= q; ++i) {
    int y;
    read(x[i]), read(y);
    qry[y].push_back(i);
  }
  int now = 1, y = 0;
  for (int i = 1; i <= n; ++i) {
    if (ch[i] == 'P') {
      ++y;
      for (auto id : qry[y]) {
        int u = ACAM::end[x[id]];
        ans[id] = BIT::query(dfn[u] + siz[u] - 1) - BIT::query(dfn[u] - 1);
      }
    } else {
      if (ch[i] == 'B') {
        BIT::update(dfn[now], -1);
        now = ACAM::fa[now];
      } else {
        now = ACAM::to[now][ch[i] - 'a'];
        BIT::update(dfn[now], 1);
      }
    }
  }
  for (int i = 1; i <= q; ++i) {
    write(ans[i]), EL;
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

void ACAM::insert(char ch) {
  static int now = 1;
  if (ch == 'P') {
    end[++tot] = now;
  } else {
    if (ch == 'B') {
      now = fa[now];
    } else {
      if (!to[now][ch - 'a']) {
        to[now][ch - 'a'] = ++id;
        fa[id] = now;
      }
      now = to[now][ch - 'a'];
    }
  }
}
void ACAM::build() {
  std::queue<int> q;
  for (int i = 0; i < 26; ++i) {
    if (to[1][i]) {
      fail[to[1][i]] = 1;
      q.push(to[1][i]);
    } else {
      to[1][i] = 1;
    }
  }
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    Graph::add(fail[u], u);
    for (int i = 0; i < 26; ++i) {
      int &v = to[u][i];
      if (v) {
        fail[v] = to[fail[u]][i];
        q.push(v);
      } else {
        v = to[fail[u]][i];
      }
    }
  }
}
void Graph::add(int u, int v) {
  nxt[++id] = hed[u];
  hed[u] = id;
  to[id] = v;
}
void BIT::update(int x, int num) {
  while (x <= ACAM::id) {
    sum[x] += num;
    x += x & -x;
  }
}
int BIT::query(int x) {
  int ans = 0;
  while (x) {
    ans += sum[x];
    x -= x & -x;
  }
  return ans;
}
void dfs(int u) {
  dfn[u] = ++id;
  siz[u] = 1;
  for (int i = Graph::hed[u]; i; i = Graph::nxt[i]) {
    int v = Graph::to[i];
    dfs(v);
    siz[u] += siz[v];
  }
}
