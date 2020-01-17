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
const int N = 300005;

void add(int, int);
void solve(int, int, int, int);

class Query {
public:
  int id, hed;
  ll ned;
};
class Chg {
public:
  int l, r;
  int num;
};

Query q[N];
Chg c[N];
int nxt[N];
ll BIT[N << 1];
int ans[N];
int n, m, k;

int main () {
  read(n), read(m);
  for (int i = 1; i <= m; ++i) {
    int a;
    read(a);
    add(i, a);
  }
  for (int i = 1; i <= n; ++i) {
    read(q[i].ned);
    q[i].id = i;
  }
  read(k);
  for (int i = 1; i <= k; ++i) {
    read(c[i].l), read(c[i].r), read(c[i].num);
    if (c[i].l > c[i].r) {
      c[i].r += m;
    }
  }
  solve(1, k + 1, 1, n);
  for (int i = 1; i <= n; ++i) {
    if (ans[i] == k + 1) {
      puts("NIE");
    } else {
      write(ans[i]), EL;
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

inline void add(int x, int a) {
  nxt[x] = q[a].hed;
  q[a].hed = x;
}
inline void update(int x, int num) {
  while (x <= (m << 1)) {
    BIT[x] += num;
    x += x & -x;
  }
}
inline void update(int l, int r, int num) {
  update(l, num), update(r + 1, -num);
}
inline ll query(int x) {
  ll ans = 0;
  while (x) {
    ans += BIT[x];
    x -= x & -x;
  }
  return ans;
}
void solve(int l, int r, int ql, int qr) {
  if (ql > qr) {
    return;
  }
  if (l == r) {
    for (int i = ql; i <= qr; ++i) {
      ans[q[i].id] = l;
    }
    return;
  }
  int mid = (l + r) >> 1;
  for (int i = l; i <= mid; ++i) {
    update(c[i].l, c[i].r, c[i].num);
  }
  int i = ql, j = qr;
  while (true) {
    while (i <= qr) {
      ll now = 0;
      for (int tmp = q[i].hed; tmp && now < q[i].ned; tmp = nxt[tmp]) {
        now += query(tmp) + query(tmp + m);
      }
      if (now >= q[i].ned) {
        ++i;
      } else {
        break;
      }
    }
    while (j >= ql) {
      ll now = 0;
      for (int tmp = q[j].hed; tmp && now < q[j].ned; tmp = nxt[tmp]) {
        now += query(tmp) + query(tmp + m);
      }
      if (now < q[j].ned) {
        --j;
      } else {
        break;
      }
    }
    if (i >= j) {
      break;
    } else {
      std::swap(q[i], q[j]);
      ++i, --j;
    }
  }
  int qmid = i - 1;
  solve(mid + 1, r, qmid + 1, qr);
  for (int i = l; i <= mid; ++i) {
    update(c[i].l, c[i].r, -c[i].num);
  }
  solve(l, mid, ql, qmid);
}
