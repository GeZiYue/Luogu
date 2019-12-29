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
#define lowbit(x) (x & -x)
const int N = 133340;
const int M = 1000005;

class Node {
public:
  int lc, rc;
  int val;
};

void insert(int, int);
void update(int, int);
int query(int, int);

Node tre[N * 400];
int tot;
std::set<int> s[M];
int a[N];
int rot[N];
int las[N];
int n, m;

int main () {
  read(n), read(m);
  for (int i = 1; i <= n; ++i) {
    read(a[i]);
    insert(i, a[i]);
  }
  for (int i = 1; i <= m; ++i) {
    char ch = getchar();
    while (ch != 'Q' && ch != 'R') {
      ch = getchar();
    }
    if (ch == 'Q') {
      int l, r;
      read(l), read(r);
      write(query(l, r)), EL;
    } else {
      int p, c;
      read(p), read(c);
      update(p, c);
    }
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

void update(int &x, int xl, int xr, int pos, int num) {
  if (!x) {
    x = ++tot;
  }
  tre[x].val += num;
  if (xl == xr) {
    return;
  }
  int xm = (xl + xr) >> 1;
  if (pos <= xm) {
    update(tre[x].lc, xl, xm, pos, num);
  } else {
    update(tre[x].rc, xm + 1, xr, pos, num);
  }
}
int query(int x, int xl, int xr, int q) {
  if (!x) {
    return 0;
  }
  if (xl == xr) {
    return tre[x].val;
  }
  int xm = (xl + xr) >> 1;
  if (q <= xm) {
    return query(tre[x].lc, xl, xm, q);
  } else {
    return query(tre[x].rc, xm + 1, xr, q) + tre[tre[x].lc].val;
  }
}
void update(int x, int pos, int num) {
  while (x <= n) {
    update(rot[x], 0, 133333, pos, num);
    x += lowbit(x);
  }
}
void insert(int x, int c) {
  std::set<int>::iterator it = s[c].upper_bound(x);
  int bef = (it == s[c].begin() ? 0 : *((--it)++));
  update(x, bef, 1);
  las[x] = bef;
  s[c].insert(x);
}
void update(int x, int c) {
  std::set<int>::iterator it = s[a[x]].upper_bound(x);
  if (it != s[a[x]].end()) {
    int nxt = *it;
    update(nxt, x, -1);
    update(nxt, las[x], 1);
    las[nxt] = las[x];
  }
  s[a[x]].erase(x);
  update(x, las[x], -1);
  it = s[c].upper_bound(x);
  int bef = (it == s[c].begin() ? 0 : *((--it)++));
  update(x, bef, 1);
  las[x] = bef;
  if (it != s[c].end()) {
    int nxt = *it;
    update(nxt, bef, -1);
    update(nxt, x, 1);
    las[nxt] = x;
  }
  s[c].insert(x);
  a[x] = c;
}
int query(int l, int r) {
  int i = r;
  int ans = 0;
  while (i) {
    ans += query(rot[i], 0, 133333, l - 1);
    i -= lowbit(i);
  }
  i = l - 1;
  while (i) {
    ans -= query(rot[i], 0, 133333, l - 1);
    i -= lowbit(i);
  }
  return ans;
}
