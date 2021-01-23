#include <bits/stdc++.h>

#define isNum(a) (a >= '0' && a <= '9')
#define SP putchar(' ')
#define EL putchar('\n')
#define File(a) freopen(a ".in", "r", stdin), freopen(a ".out", "w", stdout)

template <class T>
void read(T &);
template <class T>
void write(const T &);

typedef unsigned uint;
typedef long long ll;
typedef unsigned long long ull;
typedef std::pair<int, int> pii;
const int iinf = 2147483647;
const ll llinf = 9223372036854775807ll;

constexpr int N = 1000002;

namespace Seg_Tree {
class Node {
 public:
  int lc, rc, sum;
} tre[N * 50];
int tot, rot[N << 1];
void insert(int &x, int xl, int xr, int ux);
int merge(int x, int y, int xl, int xr);
int query(int x, int xl, int xr, int ql, int qr);
}  // namespace Seg_Tree

class SAM {
 public:
  class Node {
   public:
    int lnk, len, fir, to[26];
  } tre[N << 1];
  int tot, las;
  SAM() : tot(1), las(1) {}
  void clear();
  void extend(int c, int id);
} SAMS, SAMT;

void add(int u, int v);
void dfs(int u);
void getmatch(char *s, int l, int r);

int hed[N << 1], nxt[N << 1], to[N << 1], id;
char S[N], T[N];
int match[N];
int n, m, q;

int main() {
  scanf("%s", S + 1);
  n = strlen(S + 1);
  for (int i = 1; i <= n; ++i) {
    SAMS.extend(S[i] - 'a', i);
    Seg_Tree::insert(Seg_Tree::rot[SAMS.las], 1, n, i);
  }
  for (int i = 2; i <= SAMS.tot; ++i) {
    add(SAMS.tre[i].lnk, i);
  }
  dfs(1);
  read(q);
  for (int i = 1; i <= q; ++i) {
    scanf("%s", T + 1);
    m = strlen(T + 1);
    int l, r;
    read(l), read(r);
    SAMT.clear();
    for (int i = 1; i <= m; ++i) {
      SAMT.extend(T[i] - 'a', i);
    }
    getmatch(T, l, r);
    ll ans = 0;
    for (int i = 2; i <= SAMT.tot; ++i) {
      ans += std::max(
          SAMT.tre[i].len - std::max(SAMT.tre[SAMT.tre[i].lnk].len, match[SAMT.tre[i].fir]), 0);
    }
    write(ans), EL;
  }
  return 0;
}

namespace Seg_Tree {
void insert(int &x, int xl, int xr, int ux) {
  if (!x) {
    x = ++tot;
  }
  ++tre[x].sum;
  if (xl == xr) {
    return;
  }
  int xm = (xl + xr) >> 1;
  if (ux <= xm) {
    insert(tre[x].lc, xl, xm, ux);
  } else {
    insert(tre[x].rc, xm + 1, xr, ux);
  }
}
int merge(int x, int y, int xl, int xr) {
  if (!x || !y) {
    return x + y;
  }
  int now = ++tot;
  tre[now].sum = tre[x].sum + tre[y].sum;
  if (xl == xr) {
    return now;
  }
  int xm = (xl + xr) >> 1;
  tre[now].lc = merge(tre[x].lc, tre[y].lc, xl, xm);
  tre[now].rc = merge(tre[x].rc, tre[y].rc, xm + 1, xr);
  return now;
}
int query(int x, int xl, int xr, int ql, int qr) {
  if (!x) {
    return 0;
  }
  if (ql <= xl && xr <= qr) {
    return tre[x].sum;
  }
  int xm = (xl + xr) >> 1;
  int ans = 0;
  if (ql <= xm) {
    ans += query(tre[x].lc, xl, xm, ql, qr);
  }
  if (qr > xm) {
    ans += query(tre[x].rc, xm + 1, xr, ql, qr);
  }
  return ans;
}
}  // namespace Seg_Tree

void SAM::clear() {
  for (int i = 1; i <= tot; ++i) {
    tre[i].lnk = tre[i].len = tre[i].fir = 0;
    std::fill(tre[i].to, tre[i].to + 26, 0);
  }
  tot = las = 1;
}
void SAM::extend(int c, int id) {
  int now = ++tot;
  tre[now].len = tre[las].len + 1;
  tre[now].fir = id;
  int p = las;
  while (p && !tre[p].to[c]) {
    tre[p].to[c] = now;
    p = tre[p].lnk;
  }
  if (!p) {
    tre[now].lnk = 1;
  } else {
    int q = tre[p].to[c];
    if (tre[q].len == tre[p].len + 1) {
      tre[now].lnk = q;
    } else {
      int cur = ++tot;
      tre[cur].len = tre[p].len + 1, tre[cur].fir = tre[q].fir, tre[cur].lnk = tre[q].lnk;
      std::copy(tre[q].to, tre[q].to + 26, tre[cur].to);
      while (p && tre[p].to[c] == q) {
        tre[p].to[c] = cur;
        p = tre[p].lnk;
      }
      tre[now].lnk = tre[q].lnk = cur;
    }
  }
  las = now;
}

void add(int u, int v) {
  nxt[++id] = hed[u];
  hed[u] = id;
  to[id] = v;
}
void dfs(int u) {
  using namespace Seg_Tree;
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    dfs(v);
    rot[u] = merge(rot[u], rot[v], 1, n);
  }
}
void getmatch(char *s, int l, int r) {
  using namespace Seg_Tree;
  int now = 1, nowl = 0;
  for (int i = 1; i <= m; ++i) {
    while (true) {
      int tmp = SAMS.tre[now].to[s[i] - 'a'];
      if (tmp && query(rot[tmp], 1, n, l + nowl, r)) {
        now = tmp, ++nowl;
        break;
      }
      if (!nowl) {
        break;
      }
      --nowl;
      if (nowl == SAMS.tre[SAMS.tre[now].lnk].len) {
        now = SAMS.tre[now].lnk;
      }
    }
    match[i] = nowl;
  }
}

template <class T>
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
template <class T>
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
