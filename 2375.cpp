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

const int N = 1000005;
const int Mod = 1000000007;

int pi[N], dep[N], ans[N];
char a[N];

int main () {
  int t;
  read(t);
  while (t--) {
    scanf("%s", a + 1);
    int n = strlen(a + 1);
    dep[1] = 1;
    for (int i = 2, j = 0; i <= n; ++i) {
      while (j && (a[j + 1] != a[i])) {
        j = pi[j];
      }
      if (a[j + 1] == a[i]) {
        ++j;
      }
      pi[i] = j;
      dep[i] = dep[j] + 1;
    }
    for (int i = 2, j = 0; i <= n; ++i) {
      while (j && (a[j + 1] != a[i])) {
        j = pi[j];
      }
      if (a[j + 1] == a[i]) {
        ++j;
      }
      while ((j << 1) > i) {
        j = pi[j];
      }
      ans[i] = j;
    }
    int mul = 1;
    for (int i = 1; i <= n; ++i) {
      mul = mul * 1ll * (dep[ans[i]] + 1) % Mod;
    }
    write(mul), EL;
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
