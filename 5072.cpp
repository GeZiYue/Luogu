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
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_set>
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

const int N = 100005;
const int M = 350;

class Query {
public:
  int l, r, p, id;
} Q[N];

int add(int a, int b, int p) { return (a += b) >= p ? (a - p) : a; }
void add(int x);
void del(int x);
int pow2(int x, int p);

int Block;
int p2[M], pB2[M];
int cnt[N];
ll sum[N];
int a[N];
int ans[N];
std::unordered_set<int> S;
int n, q;

int main() {
  read(n), read(q);
  Block = sqrt(n);
  for (int i = 1; i <= n; ++i) {
    read(a[i]);
  }
  for (int i = 1; i <= q; ++i) {
    read(Q[i].l), read(Q[i].r), read(Q[i].p);
    Q[i].id = i;
  }
  std::sort(Q + 1, Q + q + 1, [&](Query i, Query j) {
    return (i.l / Block == j.l / Block)
               ? (((i.l / Block) & 1) ? (i.r < j.r) : (i.r > j.r))
               : (i.l < j.l);
  });
  int l = 1, r = 0;
  for (int i = 1; i <= q; ++i) {
    while (l > Q[i].l) {
      add(--l);
    }
    while (r < Q[i].r) {
      add(++r);
    }
    while (l < Q[i].l) {
      del(l++);
    }
    while (r > Q[i].r) {
      del(r--);
    }
    p2[0] = 1;
    for (int j = 1; j <= Block; ++j) {
      p2[j] = add(p2[j - 1], p2[j - 1], Q[i].p);
    }
    pB2[0] = 1;
    for (int j = 1; j <= Block; ++j) {
      pB2[j] = pB2[j - 1] * 1ll * p2[Block] % Q[i].p;
    }
    int res = 0;
    for (auto j : S) {
      res += sum[j] % Q[i].p *
             (pow2(r - l + 1, Q[i].p) - pow2(r - l + 1 - j, Q[i].p)) % Q[i].p;
      res = (res % Q[i].p + Q[i].p) % Q[i].p;
    }
    ans[Q[i].id] = res;
  }
  for (int i = 1; i <= q; ++i) {
    write(ans[i]), EL;
  }
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

void add(int x) {
  if (cnt[a[x]]) {
    sum[cnt[a[x]]] -= a[x];
    if (!sum[cnt[a[x]]]) {
      S.erase(cnt[a[x]]);
    }
  }
  ++cnt[a[x]];
  if (!sum[cnt[a[x]]]) {
    S.insert(cnt[a[x]]);
  }
  sum[cnt[a[x]]] += a[x];
}
void del(int x) {
  sum[cnt[a[x]]] -= a[x];
  if (!sum[cnt[a[x]]]) {
    S.erase(cnt[a[x]]);
  }
  --cnt[a[x]];
  if (cnt[a[x]]) {
    if (!sum[cnt[a[x]]]) {
      S.insert(cnt[a[x]]);
    }
    sum[cnt[a[x]]] += a[x];
  }
}
int pow2(int x, int p) { return pB2[x / Block] * 1ll * p2[x % Block] % p; }
