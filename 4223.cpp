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
using std::sort;

const int N = 500005;
const int M = 8;
const int Mod = 1000000007, iv2 = 500000004;

int add(int a, int b) { a += b; if (a >= Mod) { a -= Mod; } return a; }
int sub(int a, int b) { a -= b; if (a < 0) { a += Mod; } return a; }
int mabs(int a) { if (a < 0) { a += Mod; } return a; }

class Matrix {
public:
  int a[M][M];
  Matrix() {
    for (int i = 1; i <= 7; ++i) {
      for (int j = 1; j <= 7; ++j) {
        a[i][j] = 0;
      }
    }
  }
  int* operator [](int i) {
    return a[i];
  }
  Matrix & operator *=(Matrix m) {
    Matrix ans;
    for (int i = 1; i <= 7; ++i) {
      for (int k = 1; k <= 7; ++k) {
        int r = a[i][k];
        for (int j = 1; j <= 7; ++j) {
          ans[i][j] = add(ans[i][j], r * 1ll * m[k][j] % Mod) % Mod;
        }
      }
    }
    for (int i = 1; i <= 7; ++i) {
      for (int j = 1; j <= 7; ++j) {
        a[i][j] = ans[i][j];
      }
    }
    return *this;
  }
};

int pow(int a, int b, int m);
void update(int *BIT, int x, int num);
int query(int *BIT, int x);

void init();

int m[M];
int v[N];
int T[N], fT[N], gT[N];
int n, k;

int main () {
  read(n), read(k);
  for (int i = 1; i <= n; ++i) {
    read(v[i]);
  }
  if (n == 1) {
    write(0), EL;
    return 0;
  }
  if (n == 2) {
    if ((v[1] > v[2]) ^ (k & 1)) {
      write(1), EL;
    } else {
      write(0), EL;
    }
    return 0;
  }
  init();
  int sf = 0, sg = 0;
  int iv = pow(n - 2, Mod - 2, Mod);
  int ans = 0;
  for (int i = 1; i <= n; ++i) {
    int a = query(T, v[i]), fa = query(fT, v[i]), ga = query(gT, v[i]);
    int b = i - 1 - a, fb = sf - fa, gb = sg - ga;
    ans = add(ans, b * 1ll * m[1] % Mod);
    ans = add(ans, add(gb, fa) * 1ll * m[2] % Mod * iv % Mod);
    ans = add(ans, a * 1ll * m[3] % Mod);
    ans = add(ans, add(fb, ga) * 1ll * m[4] % Mod * iv % Mod);
    ans = add(ans, add(a * 1ll * (i - 2) % Mod, b * 1ll * (n - i) % Mod) * 1ll * m[5] % Mod * iv % Mod);
    ans = add(ans, add(a * 1ll * (n - i) % Mod, b * 1ll * (i - 2) % Mod) * 1ll * m[6] % Mod * iv % Mod);
    update(T, v[i], 1), update(fT, v[i], i - 1), update(gT, v[i], n - i - 1);
    sf = add(sf, i - 1), sg = add(sg, n - i - 1);
  }
  ans = add(ans, n * 1ll * (n - 1) / 2 % Mod * m[7] % Mod * iv2 % Mod);
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

void init() {
  Matrix ans;
  for (int i = 1; i <= 7; ++i) {
    ans[i][i] = 1;
  }
  Matrix tran;
  int binom = (n - 2) * 1ll * (n - 3) / 2 % Mod;
  tran[1][1] = tran[3][3] = binom;
  tran[2][2] = tran[4][4] = tran[5][5] = tran[6][6] = (binom + n - 3) % Mod;
  tran[7][7] = (binom + 2 * sub(n, 4) % Mod + 1) % Mod;
  tran[1][2] = tran[1][6] = tran[3][4] = tran[3][5] = n - 2;
  tran[2][7] = tran[4][7] = tran[5][7] = tran[6][7] = n - 3;
  tran[1][3] = tran[2][1] = tran[2][4] = tran[2][5] =
  tran[3][1] = tran[4][2] = tran[4][3] = tran[4][6] =
  tran[5][2] = tran[5][3] = tran[5][6] = tran[6][1] =
  tran[6][4] = tran[6][5] = tran[7][2] = tran[7][4] =
  tran[7][5] = tran[7][6] = 1;
  int tmp = k;
  while (tmp) {
    if (tmp & 1) {
      ans *= tran;
    }
    tran *= tran;
    tmp >>= 1;
  }
  for (int i = 1; i <= 7; ++i) {
    m[i] = ans[1][i];
  }
}
int pow(int a, int b, int m) {
  int ans = 1, now = a;
  while (b) {
    if (b & 1) {
      ans = ans * 1ll * now % m;
    }
    now = now * 1ll * now % m;
    b >>= 1;
  }
  return ans;
}
void update(int *BIT, int x, int num) {
  num = mabs(num);
  while (x <= n) {
    BIT[x] = add(BIT[x], num);
    x += x & -x;
  }
}
int query(int *BIT, int x) {
  int ans = 0;
  while (x) {
    ans = add(ans, BIT[x]);
    x -= x & -x;
  }
  return ans;
}
