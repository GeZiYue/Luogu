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

constexpr int Mod = 10007, iv2 = (Mod + 1) / 2, iv3 = (Mod + 1) / 3;

int sum1(const int &l, const int &r);
int sum2(const int &l, const int &r);
void work2(int x);
int work1(int x);

ll cnt2, sm12, sm22;

int main() {
  int l, r;
  read(l), read(r);
  write((work1(r) - work1(l - 1) + Mod) * 4 % Mod), EL;
  return 0;
}

int sum2(const int &x) { return x * 1ll * (x + 1) % Mod * iv2 * (2 * x + 1) % Mod * iv3 % Mod; }
int sum1(const int &l, const int &r) { return (r - l + 1) * 1ll * (r + l) / 2 % Mod; }
int sum2(const int &l, const int &r) { return (sum2(r) - sum2(l - 1) + Mod) % Mod; }
void work2(int x) {
  cnt2 = 0, sm12 = 0, sm22 = 0;
  for (int l = 1, r; l <= x; l = r + 1) {
    r = x / (x / l);
    int nn = x / l % Mod, nc = (r - l + 1) % Mod;
    cnt2 += nc * nn;
    sm12 += sum1(l, r) * nn + sum1(1, nn) * nc;
    sm22 += sum2(l, r) * nn + sum2(nn) * nc + sum1(l, r) * 2 * sum1(1, nn);
  }
  cnt2 %= Mod, sm12 %= Mod, sm22 %= Mod;
}
int work1(int x) {
  ll ans = 0;
  for (int l = 1, r; l <= x; l = r + 1) {
    r = x / (x / l);
    int now = x / l;
    work2(now);
    ans += sum2(l, r) * cnt2 + sum1(l, r) * 2 * sm12 + (r - l + 1) % Mod * sm22;
  }
  return ans % Mod;
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
