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

namespace Seg_Tree {
  int add[N], ladd;
  int sub[N], lsub;
  class Node {
  public:
    int ls, rs;
    int val;
  };
  int tot;
  Node tre[N * 400];
  void update(int &, int, int, int, int);
  int query(int, int, int);
}
namespace BIT {
  int rot[N];
  void update(int, int, int);
  int query(int, int, int);
}

class Opt {
public:
  int a, b, c;
};
Opt opt[N];
int val[N];
int all[N << 1], len;
int n, m;

int main () {
  read(n), read(m);
  for (int i = 1; i <= n; ++i) {
    read(val[i]);
    all[++len] = val[i];
  }
  for (int i = 1; i <= m; ++i) {
    char ch = getchar();
    while (ch != 'Q' && ch != 'C') {
      ch = getchar();
    }
    read(opt[i].a), read(opt[i].b);
    if (ch == 'Q') {
      read(opt[i].c);
    } else {
      all[++len] = opt[i].b;
    }
  }
  sort(all + 1, all + len + 1);
  len = std::unique(all + 1, all + len + 1) - all - 1;
  for (int i = 1; i <= n; ++i) {
    val[i] = std::lower_bound(all + 1, all + len + 1, val[i]) - all;
    BIT::update(i, val[i], 1);
  }
  for (int i = 1; i <= m; ++i) {
    if (opt[i].c) {
      write(all[BIT::query(opt[i].a, opt[i].b, opt[i].c)]), EL;
    } else {
      opt[i].b = std::lower_bound(all + 1, all + len + 1, opt[i].b) - all;
      BIT::update(opt[i].a, val[opt[i].a], -1);
      BIT::update(opt[i].a, val[opt[i].a] = opt[i].b, 1);
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

void Seg_Tree::update(int &x, int xl, int xr, int pos, int num) {
  if (!x) {
    x = ++tot;
  }
  tre[x].val += num;
  if (xl == xr) {
    return;
  }
  int xm = (xl + xr) >> 1;
  if (pos <= xm) {
    update(tre[x].ls, xl, xm, pos, num);
  } else {
    update(tre[x].rs, xm + 1, xr, pos, num);
  }
}
int Seg_Tree::query(int xl, int xr, int k) {
  if (xl == xr) {
    return xl;
  }
  int num = 0;
  for (int i = 1; i <= ladd; ++i) {
    num += tre[tre[add[i]].ls].val;
  }
  for (int i = 1; i <= lsub; ++i) {
    num -= tre[tre[sub[i]].ls].val;
  }
  int xm = (xl + xr) >> 1;
  if (num >= k) {
    for (int i = 1; i <= ladd; ++i) {
      add[i] = tre[add[i]].ls;
    }
    for (int i = 1; i <= lsub; ++i) {
      sub[i] = tre[sub[i]].ls;
    }
    return query(xl, xm, k);
  } else {
    for (int i = 1; i <= ladd; ++i) {
      add[i] = tre[add[i]].rs;
    }
    for (int i = 1; i <= lsub; ++i) {
      sub[i] = tre[sub[i]].rs;
    }
    return query(xm + 1, xr, k - num);
  }
}
void BIT::update(int x, int pos, int num) {
  while (x <= n) {
    Seg_Tree::update(rot[x], 1, len, pos, num);
    x += x & -x;
  }
}
int BIT::query(int l, int r, int k) {
  using namespace Seg_Tree;
  int x = r;
  ladd = 0;
  while (x) {
    add[++ladd] = rot[x];
    x -= x & -x;
  }
  x = l - 1;
  lsub = 0;
  while (x) {
    sub[++lsub] = rot[x];
    x -= x & -x;
  }
  return Seg_Tree::query(1, len, k);
}
