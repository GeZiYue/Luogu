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
const int N = 105;
const int Mod = 1000003;

void Add(int &i, const int &j) {i += j; if (i >= Mod) {i -= Mod;} }
int dfs(int, bool);

int f[N];
ll n;

int main () {
  read(n);
  int ans = n % Mod * ((n + 1) % Mod) % Mod * (Mod + 1) / 2 % Mod;
  --n;
  Add(ans, Mod - dfs(50, true));
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

int dfs(int x, bool lim) {
  if (x == -1) {
    return 1;
  }
  if (!lim && f[x]) {
    return f[x];
  }
  int k = lim ? ((n >> x) & 1) : 1;
  int res = 0;
  for (int i = 0; i <= k; ++i) {
    Add(res, dfs(x - 1, lim && (i == k)) * (i + 1) % Mod);
  }
  if (!lim) {
    f[x] = res;
  }
  return res;
}
