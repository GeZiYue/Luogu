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
const int N = 50005;

double calck(int, int);

class Field {
public:
  int x, y;
  inline bool operator < (const Field &i) const {
    return x == i.x ? y < i.y : x < i.x;
  }
};

Field a[N];
int que[N], hed, til;
ll dp[N];

int main () {
  int n;
  read(n);
  for (int i = 1; i <= n; ++i) {
    read(a[i].x), read(a[i].y);
  }
  sort(a + 1, a + n + 1);
  for (int i = n, now = 0; i >= 1; --i) {
    if (a[i].y <= now) {
      a[i].x = iinf;
    } else {
      now = a[i].y;
    }
  }
  sort(a + 1, a + n + 1);
  while (a[n].x == iinf) {
    --n;
  }
  que[hed = til = 1] = 0;
  for (int i = 1; i <= n; ++i) {
    while (hed < til && calck(que[hed], que[hed + 1]) <= a[i].x) {
      ++hed;
    }
    dp[i] = dp[que[hed]] + a[i].x * 1ll * a[que[hed] + 1].y;
    while (hed < til && calck(que[til - 1], que[til]) >= calck(que[til], i)) {
      --til;
    }
    que[++til] = i;
  }
  write(dp[n]), EL;
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

double calck(int i, int j) {
  return (dp[i] - dp[j]) * 1.0 / (a[j + 1].y - a[i + 1].y);
}
