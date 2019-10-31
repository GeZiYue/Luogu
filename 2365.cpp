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
const int N = 10005;

double calck(int, int);

int st[N], sf[N];
int dp[N];
int que[N], hed, til;

int main () {
  int n, s;
  read(n), read(s);
  for (int i = 1; i <= n; ++i) {
    int t, f;
    read(t), read(f);
    st[i] = st[i - 1] + t;
    sf[i] = sf[i - 1] + f;
  }
  que[hed = til = 1] = 0;
  for (int i = 1; i <= n; ++i) {
    while (hed < til && calck(que[hed], que[hed + 1]) <= st[i] + s) {
      ++hed;
    }
    dp[i] = dp[que[hed]] + st[i] * sf[i] + s * sf[n] - (st[i] + s) * sf[que[hed]];
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
  return (dp[i] - dp[j]) * 1.0 / (sf[i] - sf[j]);
}
