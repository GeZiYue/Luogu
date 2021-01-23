#include <bits/stdc++.h>

#define isNum(a) (a >= '0' && a <= '9')
#define SP putchar(' ')
#define EL putchar('\n')
#define File(a) freopen(a ".in", "r", stdin), freopen(a ".out", "w", stdout)

template <class T>
void read(T &);
template <class T>
void write(const T &);

typedef unsigned uint;
typedef long long ll;
typedef unsigned long long ull;
typedef std::pair<int, int> pii;
const int iinf = 2147483647;
const ll llinf = 9223372036854775807ll;

constexpr int N = 2000005;
constexpr int M = 4000005;

void add(int u, int v);
void tarjan(int u);

int hed[N], nxt[M], to[M], id;
int dfn[N], low[N], sta[N], top, ins[N], tot;
int col[N], ctot;
int n, m;

int main() {
  read(n), read(m);
  for (int i = 1; i <= m; ++i) {
    int a, va, b, vb;
    read(a), read(va), read(b), read(vb);
    add(a + (va & 1) * n, b + (vb ^ 1) * n);
    add(b + (vb & 1) * n, a + (va ^ 1) * n);
  }
  for (int i = 1; i <= 2 * n; ++i) {
    if (!dfn[i]) {
      tarjan(i);
    }
  }
  for (int i = 1; i <= n; ++i) {
    if (col[i] == col[i + n]) {
      puts("IMPOSSIBLE");
      return 0;
    }
  }
  puts("POSSIBLE");
  for (int i = 1; i <= n; ++i) {
    putchar((col[i] < col[i + n]) + '0'), SP;
  }
  EL;
  return 0;
}

void add(int u, int v) {
  nxt[++id] = hed[u];
  hed[u] = id;
  to[id] = v;
}
void tarjan(int u) {
  dfn[u] = low[u] = ++tot;
  sta[++top] = u;
  ins[u] = true;
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    if (!dfn[v]) {
      tarjan(v);
      low[u] = std::min(low[u], low[v]);
    } else {
      if (ins[v]) {
        low[u] = std::min(low[u], dfn[v]);
      }
    }
  }
  if (dfn[u] == low[u]) {
    ++ctot;
    do {
      u = sta[top--];
      col[u] = ctot;
      ins[u] = false;
    } while (dfn[u] != low[u]);
  }
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
