#include <algorithm>
#include <bitset>
#include <chrono>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <random>
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

const int N = 505;
const int M = 25001;

std::bitset<M> dp[2];
int a[N];
int n;

int main() {
  read(n);
  for (int i = 1; i <= n; ++i) {
    read(a[i]);
  }
  std::sort(a + 1, a + n + 1, std::greater<int>());
  int las = 1, now = 0;
  a[1] = 0;
  dp[1].set(0);
  for (int i = 2; i <= n; ++i) {
    dp[now] = dp[las];
    for (int j = i - 1; j > 1; --j) {
      if (a[j] ^ a[j - 1]) {
        dp[now] |= (dp[las] << (a[j] - a[i]));
      }
    }
    las ^= 1, now ^= 1;
  }
  for (int i = 0; i < M; ++i) {
    if (dp[las].test(i)) {
      write(i), SP;
    }
  }
  EL;
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
