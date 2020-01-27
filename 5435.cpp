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
const int N = 5000;
const int M = 1000000;
const int T = 1000;
const int Mod = 998244353;

void work();
int gcd(int, int);

int pre[T + 2][T + 2];
int a[N + 2], b[N + 2];
int fac[M + 2][3];
bool isp[M + 2];
int pri[M / 10], tot;
int n;

int main () {
  work();
  read(n);
  for (int i = 1; i <= n; ++i) {
    read(a[i]);
  }
  for (int i = 1; i <= n; ++i) {
    read(b[i]);
  }
  for (int i = 1; i <= n; ++i) {
    int ans = 0;
    for (int j = 1, now = i; j <= n; ++j, now = now * 1ll * i % Mod) {
      ans = (ans + int(now * 1ll * gcd(a[i], b[j]) % Mod)) % Mod;
    }
    write(ans), EL;
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

void work() {
  fac[1][0] = fac[1][1] = fac[1][2] = 1;
  for (int i = 2; i <= M; ++i) {
    if (!isp[i]) {
      fac[i][0] = fac[i][1] = 1;
      fac[i][2] = i;
      pri[++tot] = i;
    }
    for (int j = 1; pri[j] * i <= M; ++j) {
      int tmp = pri[j] * i;
      isp[tmp] = true;
      fac[tmp][0] = fac[i][0] * pri[j];
      fac[tmp][1] = fac[i][1];
      fac[tmp][2] = fac[i][2];
      if (fac[tmp][0] > fac[tmp][1]) {
        fac[tmp][0] ^= fac[tmp][1] ^= fac[tmp][0] ^= fac[tmp][1];
      }
      if (fac[tmp][1] > fac[tmp][2]) {
        fac[tmp][1] ^= fac[tmp][2] ^= fac[tmp][1] ^= fac[tmp][2];
      }
      if (i % pri[j] == 0) {
        break;
      }
    }
  }
  for (int i = 0; i <= T; ++i) {
    pre[0][i] = pre[i][0] = i;
  }
  for (int i = 1; i <= T; ++i) {
    for (int j = 1; j <= i; ++j) {
      pre[i][j] = pre[j][i] = pre[j][i % j];
    }
  }
}
int gcd(int a, int b) {
  int ans = 1;
  for (int i = 0; i < 3; ++i) {
    int tmp = (fac[a][i] > T) ?
                (b % fac[a][i] ?
                   1
                 : fac[a][i]
                )
              : pre[fac[a][i]][b % fac[a][i]];
    b /= tmp;
    ans *= tmp;
  }
  return ans;
}
