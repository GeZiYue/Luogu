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

const int N = 100005;
const int M = 200005;

void update(int x, int xl, int xr, int ul, int ur, int num);
void dfs(int x, int xl, int xr);

std::stack<pii> S;
int fa[M], siz[M];
std::vector<int> V[N << 2];
int u[M], v[M];
int n, m, k;

int main () {
  read(n), read(m), read(k);
  for (int i = 1; i <= m; ++i) {
    int l, r;
    read(u[i]), read(v[i]), read(l), read(r);
    if (l == r) {
      continue;
    }
    ++l;
    update(1, 1, k, l, r, i);
  }
  for (int i = 1; i <= n; ++i) {
    fa[i] = i;
    fa[i + n] = i + n;
    siz[i] = siz[i + n] = 1;
  }
  dfs(1, 1, k);
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

int find(int x) {
  return fa[x] == x ? x : find(fa[x]);
}
void merge(int x, int y) {
  int fx = find(x), fy = find(y);
  if (siz[fx] < siz[fy]) {
    S.push(pii(fx, fy));
    fa[fx] = fy;
    siz[fy] += siz[fx];
  } else {
    S.push(pii(fy, fx));
    fa[fy] = fx;
    siz[fx] += siz[fy];
  }
}
void update(int x, int xl, int xr, int ul, int ur, int num) {
  if (ul <= xl && xr <= ur) {
    V[x].push_back(num);
    return;
  }
  int xm = (xl + xr) >> 1;
  if (xm >= ul) {
    update(x << 1, xl, xm, ul, ur, num);
  }
  if (xm < ur) {
    update(x << 1 | 1, xm + 1, xr, ul, ur, num);
  }
}
void dfs(int x, int xl, int xr) {
  int tmp = S.size();
  bool flag = true;
  for (auto i : V[x]) {
    int ui = u[i], vi = v[i];
    if (find(ui) == find(vi)) {
      for (int j = xl; j <= xr; ++j) {
        puts("No");
      }
      flag = false;
      break;
    }
    merge(ui, vi + n), merge(vi, ui + n);
  }
  if (flag) {
    if (xl == xr) {
      puts("Yes");
      return;
    }
    int xm = (xl + xr) >> 1;
    dfs(x << 1, xl, xm);
    dfs(x << 1 | 1, xm + 1, xr);
  }
  while (S.size() > tmp) {
    siz[S.top().second] -= siz[S.top().first];
    fa[S.top().first] = S.top().first;
    S.pop();
  }
}
