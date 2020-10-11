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

const int N = 5005;
const int M = 100005;

void add(int u, int v, int f, int c);
bool SPFA();
int Dinic(int u, int f);
void MCMF();

int hed[N], nxt[M], to[M], flw[M], cot[M], id = 1;
int cur[N], dis[N];
bool vis[N];
int Minc, Maxf;
int S, T;
int n, m;
int ans;

int main() {
  read(n), read(m), read(S), read(T);
  for (int i = 1; i <= m; ++i) {
    int u, v, f, c;
    read(u), read(v), read(f), read(c);
    add(u, v, f, c);
    add(v, u, 0, -c);
  }
  MCMF();
  write(Maxf), SP, write(Minc), EL;
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

void add(int u, int v, int f, int c) {
  nxt[++id] = hed[u];
  hed[u] = id;
  to[id] = v;
  flw[id] = f;
  cot[id] = c;
}
bool SPFA() {
  for (int i = 1; i <= n; ++i) {
    dis[i] = iinf;
    cur[i] = hed[i];
  }
  dis[S] = 0;
  std::queue<int> q;
  q.push(S);
  vis[S] = true;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    vis[u] = false;
    for (int i = hed[u]; i; i = nxt[i]) {
      int v = to[i];
      if (flw[i] && dis[u] + cot[i] < dis[v]) {
        dis[v] = dis[u] + cot[i];
        if (!vis[v]) {
          vis[v] = true;
          q.push(v);
        }
      }
    }
  }
  return dis[T] != iinf;
}
int Dinic(int u, int f) {
  if (u == T || !f) {
    return f;
  }
  vis[u] = true;
  int ans = 0;
  for (int &i = cur[u]; i; i = nxt[i]) {
    int v = to[i];
    if (!vis[v] && flw[i] && dis[u] + cot[i] == dis[v]) {
      int now = Dinic(v, min(flw[i], f));
      if (now) {
        flw[i] -= now, flw[i ^ 1] += now;
        ans += now, f -= now;
        Minc += now * cot[i];
        if (!f) {
          break;
        }
      }
    }
  }
  vis[u] = false;
  return ans;
}
void MCMF() {
  while (SPFA()) {
    int x;
    while ((x = Dinic(S, iinf))) {
      Maxf += x;
    }
  }
}
