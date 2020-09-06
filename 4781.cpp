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

const int N = 2005;
const int Mod = 998244353;

int mabs(int a) { return a < 0 ? a + Mod : a; }
int pow(int a, int b, int m);

int x[N], y[N];
int n, k;

int main () {
  read(n), read(k);
  for (int i = 1; i <= n; ++i) {
    read(x[i]), read(y[i]);
  }
  int ans = 0;
  for (int i = 1; i <= n; ++i) {
    int now = y[i];
    for (int j = 1; j <= n; ++j) {
      if (j != i) {
        now = now * 1ll * mabs(k - x[j]) % Mod * pow(mabs(x[i] - x[j]), Mod - 2, Mod) % Mod;
      }
    }
    ans = (ans + now) % Mod;
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

int pow(int a, int b, int m) {
  int now = a, ans = 1;
  while (b) {
    if (b & 1) {
      ans = ans * 1ll * now % Mod;
    }
    now = now * 1ll * now % Mod;
    b >>= 1;
  }
  return ans;
}
