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
const int N = 100005;
const int M = 200005;

void update(int, int);
int query(int);
void work(int*, int);

int a[N], b[N], c[N];
int p[N];
int v[N];
int BIT[M];
int tmp[N];
int ans[N];
int cnt[N];
int n, m;

int main () {
  read(n), read(m);
  for (int i = 1; i <= n; ++i) {
    read(a[i]), read(b[i]), read(c[i]);
    p[i] = i;
  }
  sort(p + 1, p + n + 1, [](int x, int y) {
    if (a[x] == a[y]) {
      if (b[x] == b[y]) {
        return c[x] < c[y];
      } else {
        return b[x] < b[y];
      }
    } else {
      return a[x] < a[y];
    }
  });
  int now = 1;
  v[p[1]] = 1;
  for (int i = 2; i <= n; ++i) {
    if (a[p[i]] == a[p[i - 1]] && b[p[i]] == b[p[i - 1]] && c[p[i]] == c[p[i - 1]]) {
      ++v[p[now]];
    } else {
      p[++now] = p[i];
      v[p[i]] = 1;
    }
  }
  work(p, now);
  for (int i = 1; i <= now; ++i) {
    ans[cnt[p[i]] + v[p[i]] - 1] += v[p[i]];
  }
  for (int i = 0; i < n; ++i) {
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
  while (x <= m) {
    BIT[x] += num;
    x += x & (-x);
  }
}
int query(int x) {
  int ans = 0;
  while (x) {
    ans += BIT[x];
    x -= x & (-x);
  }
  return ans;
}
void work(int *p, int n) {
  if (n == 1) {
    return;
  }
  int mid = n >> 1;
  work(p, mid);
  work(p + mid, n - mid);
  memcpy(tmp + 1, p + 1, n << 2);
  int l = 1, r = mid + 1;
  int k = 0;
  while (l <= mid && r <= n) {
    int x = tmp[l], y = tmp[r];
    if (b[x] <= b[y]) {
      p[++k] = x;
      update(c[x], v[x]);
      ++l;
    } else {
      p[++k] = y;
      cnt[y] += query(c[y]);
      ++r;
    }
  }
  while (r <= n) {
    p[++k] = tmp[r];
    cnt[tmp[r]] += query(c[tmp[r]]);
    ++r;
  }
  memcpy(p + k + 1, tmp + l, (mid + 1 - l) << 2);
  for (int i = 1; i < l; ++i) {
    update(c[tmp[i]], -v[tmp[i]]);
  }
}
