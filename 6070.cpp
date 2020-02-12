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

const int N = 5005;

void init(int, int, int);
void change(int, int, int);

ll s[N][N];
int n, m, k;

int main () {
  read(n), read(m), read(k);
  for (int i = 1; i <= m; ++i) {
    int x, y, num;
    read(x), read(y), read(num);
    init(x, y, num);
  }
  ll ans = 0;
  for (int i = 1; i <= n - k + 1; ++i) {
    for (int j = 1; j <= n - k + 1; ++j) {
      ans += abs(s[i][j]);
      change(i, j, -s[i][j]);
    }
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      if (s[i][j]) {
        puts("-1");
        return 0;
      }
    }
  }
  write(ans), EL;
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

void init(int x, int y, int num) {
  s[x][y] += num;
  s[x + 1][y] -= num;
  s[x][y + 1] -= num;
  s[x + 1][y + 1] += num;
}
void change(int x, int y, int num) {
  s[x][y] += num;
  s[x + k][y] -= num;
  s[x][y + k] -= num;
  s[x + k][y + k] += num;
}
