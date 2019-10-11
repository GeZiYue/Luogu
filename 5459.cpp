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

void update(int, int);
int query(int);

ll a[N];
ll sum[N];
int BIT[N];
int m;

int main () {
  int n, l, r;
  read(n), read(l), read(r);
  for (int i = 1; i <= n; ++i) {
    read(a[i]);
    a[i] += a[i - 1];
    sum[i] = a[i];
  }
  sum[n + 1] = 0;
  sort(sum + 1, sum + n + 2);
  m = std::unique(sum + 1, sum + n + 2) - sum - 1;
  {
    int k = std::lower_bound(sum + 1, sum + m + 1, 0) - sum;
    update(k, 1);
  }
  ll ans = 0;
  for (int i = 1; i <= n; ++i) {
    {
      int k = std::lower_bound(sum + 1, sum + m + 1, a[i] - r) - sum;
      ans -= query(k - 1);
    }
    {
      int k = std::upper_bound(sum + 1, sum + m + 1, a[i] - l) - sum - 1;
      ans += query(k);
    }
    {
      int k = std::lower_bound(sum + 1, sum + m + 1, a[i]) - sum;
      update(k, 1);
    }
  }
  write(ans), EL;
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
