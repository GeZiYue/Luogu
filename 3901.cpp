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
const int N = 100005;

class Query {
public:
  int l, r, id;
  bool operator < (const Query &i) const;
};

void add(int);
void del(int);

int exi[N], cnt;
int a[N];
Query q[N];
bool ans[N];
int n, m, Block;

int main () {
  read(n), read(m);
  Block = (int)sqrt(n);
  for (int i = 1; i <= n; ++i) {
    read(a[i]);
  }
  for (int i = 1; i <= m; ++i) {
    read(q[i].l), read(q[i].r);
    q[i].id = i;
  }
  sort(q + 1, q + m + 1);
  int l = 0, r = 0;
  for (int i = 1; i <= m; ++i) {
    while (l > q[i].l) {
      add(--l);
    }
    while (r < q[i].r) {
      add(++r);
    }
    while (l < q[i].l) {
      del(l++);
    }
    while (r > q[i].r) {
      del(r--);
    }
    ans[q[i].id] = cnt == (q[i].r - q[i].l + 1);
  }
  for (int i = 1; i <= m; ++i) {
    puts(ans[i] ? "Yes" : "No");
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

inline bool Query::operator < (const Query &i) const {
  return l / Block == i.l / Block ? r < i.r : l < i.l;
}
void add(int x) {
  if (!exi[a[x]]++) {
    ++cnt;
  }
}
void del(int x) {
  if (!--exi[a[x]]) {
    --cnt;
  }
}
