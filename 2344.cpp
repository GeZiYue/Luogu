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
const int Mod = 1000000009;
#define lowbit(x) (x & (-x))

void update(int, int);
int query(int);

int BIT[N];
pii sum[N];
int a[N];
int Siz;

int main () {
  int n;
  read(n);
  for (int i = 1; i <= n; ++i) {
    read(sum[i].first);
    sum[i].first += sum[i - 1].first;
    sum[i].second = i;
  }
  sort(sum, sum + n + 1);
  a[sum[0].second] = 1;
  for (int i = 1; i <= n; ++i) {
    if (sum[i].first != sum[i - 1].first) {
      a[sum[i].second] = a[sum[i - 1].second] + 1;
    } else {
      a[sum[i].second] = a[sum[i - 1].second];
    }
  }
  Siz = a[sum[n].second];
  update(a[0], 1);
  for (int i = 1; i <= n; ++i) {
    int now = query(a[i]);
    update(a[i], now);
    if (i == n) {
      write(now), EL;
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

void update(int x, int num) {
  while (x <= Siz) {
    BIT[x] = (BIT[x] + num) % Mod;
    x += lowbit(x);
  }
}
int query(int x) {
  int ans = 0;
  while (x) {
    ans = (ans + BIT[x]) % Mod;
    x -= lowbit(x);
  }
  return ans;
}
