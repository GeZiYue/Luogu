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

const int N = 405;
const int M = 10005;
const double eps = 1e-8;

class Edge {
public:
  int u, v;
  double dis;
  bool friend operator < (Edge i, Edge j) {
    return i.dis > j.dis;
  }
};

int find(int x);
bool check(double mid);

int u[M], v[M], cost[M], tim[M];
Edge e[M];
int fa[N];
int n, m, f;

int main () {
  read(n), read(m), read(f);
  for (int i = 1; i <= m; ++i) {
    read(u[i]), read(v[i]), read(cost[i]), read(tim[i]);
  }
  double l = 0, r = 1e9;
  while (r - l > eps) {
    double mid = (l + r) / 2;
    if (check(mid)) {
      l = mid;
    } else {
      r = mid;
    }
  }
  std::cout.precision(4);
  std::cout << std::fixed << r << std::endl;
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

int find(int x) {
  return (fa[x] == x) ? x : (fa[x] = find(fa[x]));
}
bool check(double mid) {
  for (int i = 1; i <= m; ++i) {
    e[i].u = u[i];
    e[i].v = v[i];
    e[i].dis = -(tim[i] * mid + cost[i]);
  }
  sort(e + 1, e + m + 1);
  for (int i = 1; i <= n; ++i) {
    fa[i] = i;
  }
  double ans = f;
  int num = 0;
  for (int i = 1; i <= m; ++i) {
    int fu = find(e[i].u), fv = find(e[i].v);
    if (fu != fv) {
      ++num;
      ans += e[i].dis;
      fa[fv] = fu;
      if (num == n - 1) {
        break;
      }
    }
  }
  return ans >= 0;
}
