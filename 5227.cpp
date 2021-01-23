#include <bits/stdc++.h>

#define isNum(a) (a >= '0' && a <= '9')
#define SP putchar(' ')
#define EL putchar('\n')
#define File(a) freopen(a ".in", "r", stdin), freopen(a ".out", "w", stdout)

template <typename T>
void read(T &);
template <typename T>
void write(const T &);

typedef unsigned uint;
typedef long long ll;
typedef unsigned long long ull;
typedef std::pair<int, int> pii;
const int iinf = 2147483647;
const ll llinf = 9223372036854775807ll;

constexpr int N = 100005;
constexpr int M = 200005;

namespace Seg_Tree {
std::vector<pii> edg[N << 2];
std::stack<std::tuple<int, int, int> > St[25];
int fa[N], len[N], tot;
void update(int x, int xl, int xr, int ul, int ur, pii c);
void query(int x, int xl, int xr, int dep);
}  // namespace Seg_Tree

bool ans[N];
int u[M], v[M];
std::vector<int> del[M];
int n, m, q;

int main() {
  read(n), read(m);
  for (int i = 1; i <= m; ++i) {
    read(u[i]), read(v[i]);
  }
  read(q);
  for (int i = 1; i <= m; ++i) {
    del[i].push_back(0);
  }
  for (int i = 1; i <= q; ++i) {
    int c;
    read(c);
    while (c--) {
      int e;
      read(e);
      del[e].push_back(i);
    }
  }
  for (int i = 1; i <= m; ++i) {
    del[i].push_back(q + 1);
  }
  for (int i = 1; i <= n; ++i) {
    Seg_Tree::fa[i] = i;
  }
  Seg_Tree::tot = n;
  for (int i = 1; i <= m; ++i) {
    for (int j = 0; j < static_cast<int>(del[i].size()) - 1; ++j) {
      if (del[i][j] < del[i][j + 1] - 1) {
        Seg_Tree::update(1, 1, q, del[i][j] + 1, del[i][j + 1] - 1, {u[i], v[i]});
      }
    }
  }
  Seg_Tree::query(1, 1, q, 0);
  for (int i = 1; i <= q; ++i) {
    puts(ans[i] ? "Connected" : "Disconnected");
  }
  return 0;
}

namespace Seg_Tree {
int find(int x) { return fa[x] == x ? x : find(fa[x]); }
void update(int x, int xl, int xr, int ul, int ur, pii c) {
  if (ul <= xl && xr <= ur) {
    edg[x].push_back(c);
    return;
  }
  int xm = (xl + xr) >> 1;
  if (ul <= xm) {
    update(x << 1, xl, xm, ul, ur, c);
  }
  if (ur > xm) {
    update(x << 1 | 1, xm + 1, xr, ul, ur, c);
  }
}
void enter(int x, int dep) {
  for (auto E : edg[x]) {
    int u, v;
    std::tie(u, v) = E;
    int fu = find(u), fv = find(v);
    if (fu ^ fv) {
      if (len[fu] >= len[fv]) {
        St[dep].emplace(fu, fv, len[fu]);
        fa[fv] = fu;
        if (len[fv] == len[fu]) {
          ++len[fu];
        }
      } else {
        St[dep].emplace(fv, fu, len[fv]);
        fa[fu] = fv;
      }
      --tot;
    }
  }
}
void leave(int dep) {
  while (!St[dep].empty()) {
    int u, v, sz;
    std::tie(u, v, sz) = St[dep].top();
    fa[v] = v;
    len[u] = sz;
    St[dep].pop();
    ++tot;
  }
}
void query(int x, int xl, int xr, int dep) {
  enter(x, dep);
  if (xl == xr) {
    ans[xl] = (tot == 1);
    leave(dep);
    return;
  }
  int xm = (xl + xr) >> 1;
  query(x << 1, xl, xm, dep + 1);
  query(x << 1 | 1, xm + 1, xr, dep + 1);
  leave(dep);
}
}  // namespace Seg_Tree

template <typename T>
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
template <typename T>
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
