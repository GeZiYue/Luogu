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
const int N = 505;

void rotate(int, int, int);
void rotate_inv(int, int, int);

int a[N][N];
int tmp[N][N];

int main () {
  int n, m;
  read(n), read(m);
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      a[i][j] = (i - 1) * n + j;
    }
  }
  for (int i = 1; i <= m; ++i) {
    int x, y, r, t;
    read(x), read(y), read(r), read(t);
    if (t) {
      rotate_inv(x, y, r);
    } else {
      rotate(x, y, r);
    }
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      write(a[i][j]), SP;
    }
    EL;
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

void rotate(int x, int y, int r) {
  for (int i = -r; i <= r; ++i) {
    for (int j = -r; j <= r; ++j) {
      tmp[x + j][y - i] = a[x + i][y + j];
    }
  }
  for (int i = -r; i <= r; ++i) {
    for (int j = -r; j <= r; ++j) {
      a[x + i][y + j] = tmp[x + i][y + j];
    }
  }
}
void rotate_inv(int x, int y, int r) {
  for (int i = -r; i <= r; ++i) {
    for (int j = -r; j <= r; ++j) {
      tmp[x - j][y + i] = a[x + i][y + j];
    }
  }
  for (int i = -r; i <= r; ++i) {
    for (int j = -r; j <= r; ++j) {
      a[x + i][y + j] = tmp[x + i][y + j];
    }
  }
}
