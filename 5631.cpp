#include <algorithm>
#include <bitset>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

#define isNum(a) (a >= '0' && a <= '9')
#define SP putchar(' ')
#define EL putchar('\n')
#define File(a) freopen(a ".in", "r", stdin), freopen(a ".out", "w", stdout)

template <class T> void read(T &);
template <class T> void write(const T &);

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
using std::sort;

const int N = 1000005;
const int M = 2000005;

int find(int u);
void merge(int u, int v);
void del(int u, int v);
void solve(int l, int r, int pos);

std::tuple<int, int, int> Edg[M];
int fa[N], siz[N];
pii sta[N];
int top;
int n, m;

int main() {
  read(n), read(m);
  for (int i = 1; i <= m; ++i) {
    int u, v, p;
    read(u), read(v), read(p);
    Edg[i] = std::tie(u, v, p);
  }
  std::iota(fa + 1, fa + n + 1, 1);
  std::fill(siz + 1, siz + n + 1, 1);
  std::sort(Edg + 1, Edg + m + 1,
            [](std::tuple<int, int, int> i, std::tuple<int, int, int> j) {
              return std::get<2>(i) < std::get<2>(j);
            });
  solve(0, std::get<2>(Edg[m]) + 1, 1);
  return 0;
}

template <class T> inline void read(T &Re) {
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
template <class T> inline void write(const T &Wr) {
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

int find(int u) { return (fa[u] == u) ? u : (fa[u] = find(fa[u])); }
void merge(int u, int v) {
  int fu = find(u), fv = find(v);
  if (fu == fv) {
    return;
  }
  if (siz[fu] < siz[fv]) {
    siz[fv] += siz[fu];
    fa[fu] = fv;
    sta[++top] = pii(fu, fv);
  } else {
    siz[fu] += siz[fv];
    fa[fv] = fu;
    sta[++top] = pii(fv, fu);
  }
}
void del(int u, int v) {
  siz[v] -= siz[u];
  fa[u] = u;
}
void solve(int l, int r, int pos) {
  if (l == r) {
    if (siz[find(1)] == n) {
      write(l), EL;
      exit(0);
    }
    return;
  }
  int mid = (l + r) >> 1;
  int tmp = pos, las = top;
  for (; std::get<2>(Edg[pos]) <= r && pos <= m; ++pos) {
    if (std::get<2>(Edg[pos]) > mid) {
      merge(std::get<0>(Edg[pos]), std::get<1>(Edg[pos]));
    }
  }
  solve(l, mid, tmp);
  while (top > las) {
    del(sta[top].first, sta[top].second);
    --top;
  }
  pos = tmp;
  for (; std::get<2>(Edg[pos]) <= mid && pos <= m; ++pos) {
    merge(std::get<0>(Edg[pos]), std::get<1>(Edg[pos]));
  }
  solve(mid + 1, r, pos);
  while (top > las) {
    del(sta[top].first, sta[top].second);
    --top;
  }
}
