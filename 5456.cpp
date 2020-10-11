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

const ll Mod = 2148473648ll;

ll ans[10];
int T, a[5];

int main() {
  read(T);
  while (T--) {
    memset(ans, 0, sizeof(ans));
    read(a[1]), read(a[2]), read(a[3]), read(a[4]);
    std::sort(a + 1, a + 5, std::greater<int>());
    int cnt = (a[1] == 1) + (a[2] == 1) + (a[3] == 1) + (a[4] == 1);
    ll A = a[1] - 2, B = a[2] - 2, C = a[3] - 2, D = a[4] - 2;
    if (cnt == 0) {
      ans[0] = A * B % Mod * C % Mod * D % Mod;
      ans[1] = 2 * (A * B * C + A * B * D + A * C * D + B * C * D) % Mod;
      ans[2] = 4 * (A * B + A * C + A * D + B * C + B * D + C * D) % Mod;
      ans[3] = 8 * (A + B + C + D) % Mod;
      ans[4] = 16;
    } else {
      if (cnt == 1) {
        ans[2] = A * B * C % Mod;
        ans[3] = 2 * (A * B + A * C + B * C) % Mod;
        ans[4] = 4 * (A + B + C) % Mod;
        ans[5] = 8;
      } else {
        if (cnt == 2) {
          ans[4] = A * B % Mod;
          ans[5] = 2 * (A + B) % Mod;
          ans[6] = 4;
        } else {
          if (cnt == 3) {
            ans[6] = A;
            ans[7] = 2;
          } else {
            ans[8] = 1;
          }
        }
      }
    }
    for (int i = 0; i <= 8; ++i) {
      write(ans[i]), SP;
    }
    EL;
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
