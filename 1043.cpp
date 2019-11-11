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
const int N = 105;
const int M = 15;

int mind[N][N][M], maxd[N][N][M];
int a[N];
int sum[N];

int main () {
  int n, m;
  read(n), read(m);
  for (int i = 1; i <= n; ++i) {
    read(a[i]);
    a[i] = (a[i] % 10 + 10) % 10;
    a[n + i] = a[i];
  }
  n <<= 1;
  for (int i = 1; i <= n; ++i) {
    sum[i] = (sum[i - 1] + a[i]) % 10;
    mind[i][i][1] = maxd[i][i][1] = a[i];
  }
  for (int l = 1; l <= (n >> 1); ++l) {
    for (int i = 1, j = l; j <= n; ++i, ++j) {
      mind[i][j][1] = maxd[i][j][1] = (sum[j] - sum[i - 1] + 10) % 10;
      for (int k = 2; k <= min(m, l); ++k) {
        mind[i][j][k] = iinf;
        maxd[i][j][k] = -iinf;
        for (int d = i + k - 2; d < j; ++d) {
          mind[i][j][k] = min(mind[i][j][k], mind[i][d][k - 1] * ((sum[j] - sum[d] + 10) % 10));
          maxd[i][j][k] = max(maxd[i][j][k], maxd[i][d][k - 1] * ((sum[j] - sum[d] + 10) % 10));
        }
      }
    }
  }
  int ans1 = iinf, ans2 = -iinf;
  for (int i = 1; i <= (n >> 1); ++i) {
    ans1 = min(ans1, mind[i][i + (n >> 1) - 1][m]);
    ans2 = max(ans2, maxd[i][i + (n >> 1) - 1][m]);
  }
  write(ans1), EL, write(ans2), EL;
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
