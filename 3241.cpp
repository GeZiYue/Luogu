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
#include <ctime>
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

const int N = 150005;
const int M = 300005;
typedef std::pair<int, ll> pil;

class Info {
public:
  int age;
  ll dis1, dis2;
  int num;
  Info(int age = 0, ll dis1 = 0, ll dis2 = 0, int num = 0) : age(age), dis1(dis1), dis2(dis2), num(num) {}
  friend bool operator < (Info i, Info j) {
    return i.age < j.age;
  }
};

void add(int, int, int);
void calc(int, int, int);
void getrot(int, int);
void dfs(int);
Info calc(std::vector<Info> &, int, int);

int hed[N], nxt[M], to[M], dis[M], id;
int age[N];
int fa[N];
int dep[N];
int siz[N];
int ssum, rot, mis;
bool vis[N];
int len[20][N];
std::vector<Info> cnt[N];
int n, q, A;

int main () {
  read(n), read(q), read(A);
  for (int i = 1; i <= n; ++i) {
    read(age[i]);
  }
  for (int i = 1; i < n; ++i) {
    int u, v, w;
    read(u), read(v), read(w);
    add(u, v, w);
    add(v, u, w);
  }
  ssum = n;
  mis = iinf;
  getrot(1, 0);
  dep[rot] = 1;
  dfs(rot);
  ll lastans = 0;
  for (int i = 1; i <= q; ++i) {
    int u, a, b;
    read(u), read(a), read(b);
    int l = (a + lastans) % A, r = (b + lastans) % A;
    if (l > r) {
      l ^= r ^= l ^= r;
    }
    int lx = u, fx = fa[u];
    ll ans = 0;
    while (lx) {
      Info now = calc(cnt[lx], l, r);
      ans += now.dis1 + now.num * 1ll * len[dep[lx]][u];
      if (fx) {
        ans -= now.dis2 + now.num * 1ll * len[dep[fx]][u];
      }
      lx = fx;
      fx = fa[fx];
    }
    write(lastans = ans), EL;
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

void add(int u, int v, int w) {
  nxt[++id] = hed[u];
  hed[u] = id;
  to[id] = v;
  dis[id] = w;
}
void calc(int u, int fat, int root) {
  cnt[root].push_back(Info(age[u], len[dep[root]][u], len[dep[root] - 1][u], 1));
  siz[u] = 1;
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    if (v != fat && !vis[v]) {
      len[dep[root]][v] = len[dep[root]][u] + dis[i];
      calc(v, u, root);
      siz[u] += siz[v];
    }
  }
}
void getrot(int u, int fat) {
  siz[u] = 1;
  int maxg = 0;
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    if (v != fat && !vis[v]) {
      getrot(v, u);
      siz[u] += siz[v];
      maxg = max(maxg, siz[v]);
    }
  }
  maxg = max(maxg, ssum - siz[u]);
  if (maxg < mis) {
    mis = maxg;
    rot = u;
  }
}
void dfs(int u) {
  vis[u] = true;
  calc(u, 0, u);
  sort(cnt[u].begin(), cnt[u].end());
  for (int i = 1; i < (int)cnt[u].size(); ++i) {
    cnt[u][i].dis1 += cnt[u][i - 1].dis1;
    cnt[u][i].dis2 += cnt[u][i - 1].dis2;
    cnt[u][i].num += cnt[u][i - 1].num;
  }
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    if (!vis[v]) {
      ssum = siz[v];
      mis = iinf;
      getrot(v, 0);
      dep[rot] = dep[u] + 1;
      fa[rot] = u;
      dfs(rot);
    }
  }
}
Info calc(std::vector<Info> &v, int l, int r) {
  std::vector<Info>::iterator il = std::lower_bound(v.begin(), v.end(), Info(l, 0, 0, 0));
  std::vector<Info>::iterator ir = std::lower_bound(v.begin(), v.end(), Info(r + 1, 0, 0, 0));
  if (il == ir) {
    return Info(0, 0, 0, 0);
  }
  if (ir == v.begin()) {
    return Info(0, 0, 0, 0);
  }
  --ir;
  Info i(0, 0, 0, 0);
  if (il == v.begin()) {
    i.dis1 = ir->dis1;
    i.dis2 = ir->dis2;
    i.num = ir->num;
  } else {
    --il;
    i.dis1 = ir->dis1 - il->dis1;
    i.dis2 = ir->dis2 - il->dis2;
    i.num = ir->num - il->num;
  }
  return i;
}
