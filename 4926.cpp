#include <unordered_set>
#include <unordered_map>
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
const int N = 1005;
const int M = 3005;

void add(int, int, double);
bool check(double);

int hed[N], nxt[M], to[M], id;
double dis[M];
int u[N], v[N], flag[N];
int num[N], C[N];
bool type[N];
double delta[N];
bool vis[N];
int cnt[N];
int n, m, k;

int main () {
  read(n), read(m), read(k);
  for (int i = 1; i <= m; ++i) {
    int t;
    read(t);
    type[i] = t - 1;
    read(u[i]), read(v[i]), read(flag[i]);
  }
  for (int i = 1; i <= k; ++i) {
    read(num[i]), read(C[i]);
  }
  double l = 0, r = 1e20;
  double ans = -1;
  while (r - l >= 1e-8) {
    double mid = (r + l) / 2;
    if (check(mid)) {
      l = ans = mid;
    } else {
      r = mid;
    }
  }
  if (ans == -1) {
    puts("-1");
  } else {
    std::cout.precision(8);
    std::cout << std::fixed << ans << std::endl;
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

inline void add(int u, int v, double w) {
  nxt[++id] = hed[u];
  hed[u] = id;
  to[id] = v;
  dis[id] = w;
}
bool check(double t) {
  id = 0;
  memset(hed, 0, sizeof(hed));
  for (int i = 1; i <= m; ++i) {
    if (type[i]) {
      add(v[i], u[i], 1.0 / (flag[i] + t));
    } else {
      add(v[i], u[i], flag[i] - t);
    }
  }
  for (int i = 1; i <= k; ++i) {
    add(0, num[i], C[i]);
    add(num[i], 0, 1.0 / C[i]);
  }
  std::queue<int> q;
  for (int i = 0; i <= n; ++i) {
    delta[i] = 1;
    vis[i] = true;
    cnt[i] = 0;
    q.push(i);
  }
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    vis[u] = false;
    if (++cnt[u] == n + 2) {
      return true;
    }
    for (int i = hed[u]; i; i = nxt[i]) {
      int v = to[i];
      if (delta[u] * dis[i] > delta[v]) {
        delta[v] = delta[u] * dis[i];
        if (!vis[v]) {
          vis[v] = true;
          q.push(v);
        }
      }
    }
  }
  return false;
}
