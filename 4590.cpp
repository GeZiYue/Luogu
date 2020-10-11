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

template <class T> void read(T &);
template <class T> void write(const T &);

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

const int N = 35000;
const int Mod = 1000000007;

void add(int &a, int b) {
  a += b;
  while (a >= Mod) {
    a -= Mod;
  }
}
int hash(int *a, int len);
void ihash(int *a, int len, int val);
void trans(bool t1, int t2, int t3, char c, const int &val);

int dp[2][N][3];
int tmp1[16], tmp2[16];
char str[16];
int ans[16];
int siz[N];
int n, k, S;

int main() {
  read(n), read(k);
  scanf("%s", str + 1);
  S = 1 << k;
  for (int i = 1; i < S; ++i) {
    siz[i] = siz[i >> 1] + (i & 1);
  }
  bool now = 1, las = 0;
  dp[0][0][0] = 1;
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j < S; ++j) {
      for (int k = 0; k < 3; ++k) {
        dp[now][j][k] = 0;
      }
    }
    for (int j = 0; j < S; ++j) {
      if (dp[las][j][0]) {
        trans(now, j, 1, 'N', dp[las][j][0]);
        trans(now, j, 0, 'O', dp[las][j][0]);
        trans(now, j, 0, 'I', dp[las][j][0]);
      }
      if (dp[las][j][1]) {
        trans(now, j, 1, 'N', dp[las][j][1]);
        trans(now, j, 2, 'O', dp[las][j][1]);
        trans(now, j, 0, 'I', dp[las][j][1]);
      }
      if (dp[las][j][2]) {
        trans(now, j, 1, 'N', dp[las][j][2]);
        trans(now, j, 0, 'O', dp[las][j][2]);
      }
    }
    now ^= 1;
    las ^= 1;
  }
  for (int j = 0; j < S; ++j) {
    for (int k = 0; k < 3; ++k) {
      if (dp[las][j][k]) {
        add(ans[siz[j]], dp[las][j][k]);
      }
    }
  }
  for (int i = 0; i <= k; ++i) {
    write(ans[i]), EL;
  }
  return 0;
}

template <class T> inline void read(T &Re) {
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
template <class T> inline void write(const T &Wr) {
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

int hash(int *a, int len) {
  int ans = 0;
  for (int i = 0; i < len; ++i) {
    ans |= ((a[i + 1] - a[i]) << i);
  }
  return ans;
}
void ihash(int *a, int len, int val) {
  for (int i = 0; i < len; ++i) {
    a[i + 1] = (val >> i) & 1;
  }
  for (int i = 1; i <= len; ++i) {
    a[i] += a[i - 1];
  }
}
void trans(bool t1, int t2, int t3, char c, const int &val) {
  ihash(tmp1, k, t2);
  for (int i = 1; i <= k; ++i) {
    tmp2[i] = max(max(tmp2[i - 1], tmp1[i]), tmp1[i - 1] + (c == str[i]));
  }
  int tt2 = hash(tmp2, k);
  add(dp[t1][tt2][t3], val);
}
