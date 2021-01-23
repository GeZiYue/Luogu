#include <bits/stdc++.h>

#define isNum(a) (a >= '0' && a <= '9')
#define SP putchar(' ')
#define EL putchar('\n')
#define File(a) freopen(a ".in", "r", stdin), freopen(a ".out", "w", stdout)
template <class T>
void read(T &);
template <class T>
void write(const T &);
typedef long long ll;
typedef unsigned long long ull;
typedef const long long &cll;
typedef const int &ci;
typedef std::pair<int, int> pii;
const int iinf = 2147483647;
const ll llinf = 9223372036854775807ll;
using std::abs;
using std::max;
using std::min;

constexpr int N = 600005;

namespace SAM {
class Node {
 public:
  int to[26];
  int len, lnk, siz;
  int max1, max2, min1, min2;
} tre[N];
int tot = 1, las = 1;
int hed[N], nxt[N], to[N], id;
ll anss[N], ansm[N];
void extend(int c, int v);
void add(int u, int v);
void upd(int u, int v);
void dfs(int u);
void build();
};  // namespace SAM

int val[N];
char ch[N];
int n;

int main() {
  read(n);
  scanf("%s", ch + 1);
  for (int i = 1; i <= n; ++i) {
    read(val[i]);
  }
  using namespace SAM;
  for (int i = 0; i <= n; ++i) {
    ansm[i] = -iinf * 1ll * iinf;
  }
  for (int i = n; i >= 1; --i) {
    extend(ch[i] - 'a', val[i]);
  }
  tre[1].max1 = tre[1].max2 = -iinf, tre[1].min1 = tre[1].min2 = iinf;
  build();
  for (int i = n - 1; i >= 0; --i) {
    anss[i] += anss[i + 1];
    if (anss[i] == 0) {
      ansm[i] = 0;
    }
    if (anss[i + 1]) {
      ansm[i] = max(ansm[i], ansm[i + 1]);
    }
  }
  for (int i = 0; i < n; ++i) {
    write(anss[i]), SP, write(ansm[i]), EL;
  }
  return 0;
}

void SAM::extend(int c, int v) {
  int now = ++tot;
  tre[now].len = tre[las].len + 1;
  tre[now].siz = 1;
  tre[now].max1 = tre[now].min1 = v;
  tre[now].max2 = -iinf, tre[now].min2 = iinf;
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
      tre[cur].len = tre[p].len + 1;
      tre[cur].lnk = tre[q].lnk;
      tre[cur].max1 = tre[cur].max2 = -iinf;
      tre[cur].min1 = tre[cur].min2 = iinf;
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
void SAM::add(int u, int v) {
  nxt[++id] = hed[u];
  hed[u] = id;
  to[id] = v;
}
void SAM::upd(int u, int v) {
  if (tre[v].max2 > tre[u].max1) {
    tre[u].max2 = tre[u].max1;
    tre[u].max1 = tre[v].max2;
  } else {
    if (tre[v].max2 > tre[u].max2) {
      tre[u].max2 = tre[v].max2;
    }
  }
  if (tre[v].max1 > tre[u].max1) {
    tre[u].max2 = tre[u].max1;
    tre[u].max1 = tre[v].max1;
  } else {
    if (tre[v].max1 > tre[u].max2) {
      tre[u].max2 = tre[v].max1;
    }
  }
  if (tre[v].min2 < tre[u].min1) {
    tre[u].min2 = tre[u].min1;
    tre[u].min1 = tre[v].min2;
  } else {
    if (tre[v].min2 < tre[u].min2) {
      tre[u].min2 = tre[v].min2;
    }
  }
  if (tre[v].min1 < tre[u].min1) {
    tre[u].min2 = tre[u].min1;
    tre[u].min1 = tre[v].min1;
  } else {
    if (tre[v].min1 < tre[u].min2) {
      tre[u].min2 = tre[v].min1;
    }
  }
}
void SAM::dfs(int u) {
  ull cnt = 0;
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    dfs(v);
    tre[u].siz += tre[v].siz;
    cnt += tre[v].siz * 1ll * tre[v].siz;
    upd(u, v);
  }
  if (tre[u].siz < 2) {
    return;
  }
  anss[tre[u].len] += (tre[u].siz * 1ll * tre[u].siz - cnt) / 2;
  ansm[tre[u].len] =
      max({ansm[tre[u].len], tre[u].max1 * 1ll * tre[u].max2, tre[u].min1 * 1ll * tre[u].min2});
}
void SAM::build() {
  for (int i = 2; i <= tot; ++i) {
    add(tre[i].lnk, i);
  }
  dfs(1);
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
