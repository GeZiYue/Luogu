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

const int N = 1000005;
const int Mod = 998244353;

int add(int a, int b) { return (a += b) >= Mod ? a - Mod : a; }
int sub(int a, int b) { return (a -= b) < 0 ? a + Mod : a; }
int pow(int a, int b, int m);

int f[N], sum[N];
std::vector<int> to[N];
int n, m;

int main() {
  read(n), read(n), read(m);
  for (int i = 1; i <= m; ++i) {
    int u, v;
    read(u), read(v);
    to[u].push_back(v);
  }
  for (int i = 1; i <= n; ++i) {
    f[i] = to[i].size() + 1;
    for (auto j : to[i]) {
      f[i] = add(f[i], sub(sum[i - 1], sum[j - 1]));
    }
    sum[i] = add(sum[i - 1], f[i]);
  }
  write(sum[n]), EL;
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
