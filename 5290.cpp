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

const int N = 200005;

void dfs(int u);
void merge(int x, int y);

std::priority_queue<int> pq[N];
std::vector<int> to[N];
int a[N];
int n;

int main () {
  read(n);
  for (int i = 1; i <= n; ++i) {
    read(a[i]);
  }
  for (int i = 2; i <= n; ++i) {
    int fa;
    read(fa);
    to[fa].push_back(i);
  }
  dfs(1);
  ll ans = 0;
  while (!pq[1].empty()) {
    ans += pq[1].top();
    pq[1].pop();
  }
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

void dfs(int u) {
  for (auto v : to[u]) {
    dfs(v);
    merge(u, v);
  }
  pq[u].push(a[u]);
}
void merge(int x, int y) {
  if (pq[x].size() < pq[y].size()) {
    pq[x].swap(pq[y]);
  }
  std::vector<int> tmp;
  while (!pq[y].empty()) {
    tmp.push_back(max(pq[x].top(), pq[y].top()));
    pq[x].pop(), pq[y].pop();
  }
  for (auto i : tmp) {
    pq[x].push(i);
  }
}
