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

const int N = 2000005;

class Line {
public:
  ll l, r;
  Line(ll l = 0, ll r = 0) : l(l), r(r) {}
};

ll gcd(ll a, ll b);

Line a[N];
int cnt;
ll A, B;
int n;

int main() {
  read(n), read(A), read(B);
  ll G = A / gcd(A, B + 1);
  if (G * 1.0 * B >= 1e18) {
    G = int(1e18);
  } else {
    G *= B;
  }
  for (int i = 1; i <= n; ++i) {
    ll l, r;
    read(l), read(r);
    if (r - l + 1 >= G) {
      write(G), EL;
      return 0;
    } else {
      l %= G, r %= G;
      if (l <= r) {
        a[++cnt] = Line(l, r);
      } else {
        a[++cnt] = Line(l, G - 1);
        a[++cnt] = Line(0, r);
      }
    }
  }
  std::sort(a + 1, a + cnt + 1, [](Line i, Line j) {
    return (i.l == j.l) ? (i.r < j.r) : (i.l < j.l);
  });
  ll nl = a[1].l, nr = a[1].r;
  ll ans = 0;
  a[++cnt] = Line(G, G);
  for (int i = 2; i <= cnt; ++i) {
    if (a[i].l > nr) {
      ans += nr - nl + 1;
      nl = a[i].l;
      nr = a[i].r;
    } else {
      nr = max(nr, a[i].r);
    }
  }
  write(ans), EL;
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

ll gcd(ll a, ll b) { return (b == 0) ? a : gcd(b, a % b); }
