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
#include <vector>

#define isNum(a) (a >= '0' && a <= '9')
#define SP putchar(' ')
#define EL putchar('\n')
#define File(a) freopen(a ".in", "r", stdin), freopen(a ".out", "w", stdout)

template <class T>
void read(T &);
template <class T>
void write(const T &);

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

const int N = 1005;
const int M = 5005;
const int Mod = 1000000007;

int rk[M], nk[M];
int ans[M];
char ch[M];
bool b[M][N];
int n, m, q;

int main() {
  read(n), read(m), read(q);
  for (int i = 1; i <= m; ++i) {
    rk[i] = i;
  }
  for (int i = 1; i <= n; ++i) {
    scanf("%s", ch + 1);
    for (int j = 1; j <= m; ++j) {
      b[j][i] = ch[j] - '0';
    }
    int now = 0;
    for (int j = 1; j <= m; ++j) {
      if (b[rk[j]][i] == 0) {
        nk[++now] = rk[j];
      }
    }
    for (int j = 1; j <= m; ++j) {
      if (b[rk[j]][i] == 1) {
        nk[++now] = rk[j];
      }
    }
    for (int j = 1; j <= m; ++j) {
      rk[j] = nk[j];
    }
  }
  for (int i = 1; i <= m; ++i) {
    for (int j = n; j >= 1; --j) {
      ans[i] = ((ans[i] << 1) + b[i][j]) % Mod;
    }
  }
  rk[m + 1] = m + 1;
  ans[m + 1] = 1;
  for (int j = 1; j <= n; ++j) {
    ans[m + 1] = (ans[m + 1] << 1) % Mod;
  }
  for (int i = 1; i <= q; ++i) {
    scanf("%s", ch + 1);
    int l = 0, r = m + 1;
    for (int j = 1; j <= m; ++j) {
      if (ch[rk[j]] == '1') {
        r = j;
        break;
      }
    }
    for (int j = m; j >= 1; --j) {
      if (ch[rk[j]] == '0') {
        l = j;
        break;
      }
    }
    if (r < l) {
      write(0), EL;
    } else {
      write((ans[rk[r]] - ans[rk[l]] + Mod) % Mod), EL;
    }
  }
  return 0;
}

template <class T>
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
template <class T>
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
