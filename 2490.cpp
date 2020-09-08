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
#include <ctime>
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

const int N = 10005;
const int M = 20;
const int Mod = 1000000007;

void inc(int &a, int b) { a += b; if (a >= Mod) { a -= Mod; } }

int dp[M][N];
int C[N][105];
int n, m, k;

int main () {
  read(n), read(k), read(m);
  C[0][0] = 1;
  for (int i = 1; i <= n; ++i) {
    C[i][0] = 1;
    for (int j = 1; j <= 100; ++j) {
      C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % Mod;
    }
  }
  dp[0][0] = 1;
  for (int i = 0; i <= 16; ++i) {
    int x = (1 << i);
    for (int j = 0; j <= n - k; ++j) {
      for (int l = 0; x * l * (m + 1) <= n - k - j && l * (m + 1) <= k / 2; ++l) {
        inc(dp[i + 1][j + x * l * (m + 1)], C[k / 2][l * (m + 1)] * 1ll * dp[i][j] % Mod);
      }
    }
  }
  int ans = 0;
  for (int i = 0; i <= n - k; ++i) {
    ans = (ans + C[n - i - k / 2][k / 2] * 1ll * dp[17][i] % Mod) % Mod;
  }
  write((C[n][k] - ans + Mod) % Mod), EL;
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
