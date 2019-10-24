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
const int N = 25;

bool exi[N];

int main () {
  int t;
  read(t);
  while (t--) {
    int n;
    read(n);
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
      memset(exi, false, sizeof(exi));
      int m;
      read(m);
      for (int i = 1; i <= m; ++i) {
        int a;
        read(a);
        exi[a] = true;
      }
      int id = 1;
      int now = 0;
      int xans = 0;
      int j = 20;
      while (exi[j]) {
        --j;
      }
      for (; j >= 0; --j) {
        if (!exi[j]) {
          if ((++id) & 1) {
            xans ^= now;
          }
          now = 0;
        } else {
          ++now;
        }
      }
      ans ^= xans;
    }
    puts(ans ? "YES" : "NO");
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
