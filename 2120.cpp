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

double calck(int, int);

ll sp[N], sm[N];
ll dp[N];
int x[N], p[N], c[N];
int que[N], hed, til;

int main () {
  int n;
  read(n);
  for (int i = 1; i <= n; ++i) {
    read(x[i]), read(p[i]), read(c[i]);
    sp[i] = sp[i - 1] + p[i];
    sm[i] = sm[i - 1] + x[i] * 1ll * p[i];
  }
  que[hed = til = 1] = 0;
  for (int i = 1; i <= n; ++i) {
    while (hed < til && calck(que[hed], que[hed + 1]) <= x[i]) {
      ++hed;
    }
    dp[i] = dp[que[hed]] + c[i] + (sp[i] - sp[que[hed]]) * x[i] - (sm[i] - sm[que[hed]]);
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
  return (dp[i] - dp[j] + sm[i] - sm[j]) * 1.0 / (sp[i] - sp[j]);
}
