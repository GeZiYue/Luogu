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

constexpr int N = 1005;
constexpr int M = 1000005;

void add(int u, int v);

int hed[N], nxt[M], to[M], id;
std::queue<int> q;
int a[N], now[N];
std::vector<int> ans;
int n;

int main() {
  read(n);
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      int tmp;
      scanf("%1d", &tmp);
      if (tmp) {
        add(i, j);
      }
    }
  }
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
    if (!a[i]) {
      q.push(i);
    }
  }
  while (!q.empty()) {
    int u = q.front();
    ans.push_back(u);
    q.pop();
    for (int i = hed[u]; i; i = nxt[i]) {
      int v = to[i];
      ++now[v];
      if (now[v] == a[v]) {
        q.push(v);
      }
    }
  }
  write(ans.size()), EL;
  for (int i : ans) {
    write(i), SP;
  }
  EL;
  return 0;
}

void add(int u, int v) {
  nxt[++id] = hed[u];
  hed[u] = id;
  to[id] = v;
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
