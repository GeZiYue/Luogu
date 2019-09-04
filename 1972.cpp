#include <unordered_set>
#include <unordered_map>
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
typedef const long long & cll;
typedef const int & ci;
typedef std::pair<int, int> pii;
const int iinf = 2147483647;
const ll llinf = 9223372036854775807ll;
using std::min;
using std::max;
using std::abs;
using std::sort;
const int N = 1000005;

class Query {
public:
  int l, r;
  int id;
  bool operator < (const Query &i) const {
    return r < i.r;
  }
}q[N];

void update(int, int);
int query(int);
int query(int, int);

int BIT[N];
int pre[N];
int las[N];
int ans[N];
int n;

int main () {
  read(n);
  for (int i = 1; i <= n; ++i) {
    int a;
    read(a);
    pre[i] = las[a];
    las[a] = i;
  }
  int m;
  read(m);
  for (int i = 1; i <= m; ++i) {
    read(q[i].l), read(q[i].r);
    q[i].id = i;
  }
  sort(q + 1, q + m + 1);
  int now = 0;
  for (int i = 1; i <= m; ++i) {
    while (now < q[i].r) {
      ++now;
      update(now, 1);
      if (pre[now]) {
        update(pre[now], -1);
      }
    }
    ans[q[i].id] = query(q[i].l, q[i].r);
  }
  for (int i = 1; i <= m; ++i) {
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

void update(int x, int num) {
  while (x <= n) {
    BIT[x] += num;
    x += x & -x;
  }
}
int query(int x) {
  int ans = 0;
  while (x) {
    ans += BIT[x];
    x -= x & -x;
  }
  return ans;
}
int query(int l, int r) {
  return query(r) - query(l - 1);
}
