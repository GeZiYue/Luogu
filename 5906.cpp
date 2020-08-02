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

const int N = 200005;

class Query {
public:
  int l, r, id;
  bool friend operator < (Query, Query);
};

int Bl[N], Br[N], tot;
Query Q[N];
int pos[N];
int a[N];
int all[N], id;
int la[N], ra[N];
int las[N];
int Ans[N];
int cl[N], cnt;
int Block;
int n, q;

int main () {
  read(n);
  for (int i = 1; i <= n; ++i) {
    read(a[i]);
    all[++id] = a[i];
  }
  read(q);
  for (int i = 1; i <= q; ++i) {
    read(Q[i].l), read(Q[i].r);
    Q[i].id = i;
  }
  Block = int(sqrt(n));
  tot = n / Block;
  for (int i = 1; i <= tot; ++i) {
    Bl[i] = (i - 1) * Block + 1;
    Br[i] = i * Block;
  }
  if (Br[tot] < n) {
    ++tot;
    Bl[tot] = Br[n / Block] + 1;
    Br[tot] = n;
  }
  for (int i = 1; i <= tot; ++i) {
    for (int j = Bl[i]; j <= Br[i]; ++j) {
      pos[j] = i;
    }
  }
  sort(all + 1, all + id + 1);
  id = std::unique(all + 1, all + id + 1) - all - 1;
  for (int i = 1; i <= n; ++i) {
    a[i] = std::lower_bound(all + 1, all + id + 1, a[i]) - all;
  }
  sort(Q + 1, Q + q + 1);
  int l = 1, r = 0, ql, lb = 0;
  int ans = 0;
  for (int i = 1; i <= q; ++i) {
    if (pos[Q[i].l] == pos[Q[i].r]) {
      int res = 0;
      for (int j = Q[i].l; j <= Q[i].r; ++j) {
        if (!las[a[j]]) {
          las[a[j]] = j;
        } else {
          res = max(res, j - las[a[j]]);
        }
      }
      for (int j = Q[i].l; j <= Q[i].r; ++j) {
        las[a[j]] = 0;
      }
      Ans[Q[i].id] = res;
      continue;
    }
    if (pos[Q[i].l] != lb) {
      for (int j = 1; j <= cnt; ++j) {
        la[cl[j]] = ra[cl[j]] = 0;
      }
      cnt = 0;
      ans = 0;
      lb = pos[Q[i].l];
      r = Br[lb];
      l = Br[lb] + 1;
    }
    while (r < Q[i].r) {
      ++r;
      ra[a[r]] = r;
      if (!la[a[r]]) {
        la[a[r]] = r;
        cl[++cnt] = a[r];
      } else {
        ans = max(ans, r - la[a[r]]);
      }
    }
    int tmp = ans;
    while (l > Q[i].l) {
      --l;
      if (!ra[a[l]]) {
        ra[a[l]] = l;
      } else {
        ans = max(ans, ra[a[l]] - l);
      }
    }
    Ans[Q[i].id] = ans;
    ans = tmp;
    while (l <= Br[lb]) {
      if (ra[a[l]] == l) {
        ra[a[l]] = 0;
      }
      ++l;
    }
  }
  for (int i = 1; i <= q; ++i) {
    write(Ans[i]), EL;
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

bool operator < (Query i, Query j) {
  if (pos[i.l] == pos[j.l]) {
    return i.r < j.r;
  }
  return i.l < j.l;
}
