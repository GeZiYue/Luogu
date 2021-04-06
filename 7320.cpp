#include <bits/stdc++.h>

#define isNum(a) (a >= '0' && a <= '9')
#define SP putchar(' ')
#define EL putchar('\n')
#define File(a) freopen(a ".in", "r", stdin), freopen(a ".out", "w", stdout)

template <typename T>
void read(T &);
template <typename T>
void write(const T &);

typedef unsigned uint;
typedef long long ll;
typedef unsigned long long ull;
typedef std::pair<int, int> pii;
const int iinf = 2147483647;
const ll llinf = 9223372036854775807ll;

const int N = 300005;

void dfs(int u, int fa, int k);

std::vector<int> G[N];
int f[N];
int n;

int main() {
  read(n);
  for (int i = 1; i < n; ++i) {
    int u, v;
    read(u), read(v);
    G[u].push_back(v), G[v].push_back(u);
  }
  int l = 1, r = n;
  int ans = n;
  while (l <= r) {
    int mid = (l + r) >> 1;
    dfs(1, 0, mid);
    if (f[1]) {
      l = mid + 1;
    } else {
      ans = mid;
      r = mid - 1;
    }
  }
  write(ans), EL;
  return 0;
}

void dfs(int u, int fa, int k) {
  f[u] = 0;
  for (int v : G[u]) {
    if (v == fa) continue;
    dfs(v, u, k);
    f[u] += f[v] + 1;
  }
  f[u] -= k;
  if (f[u] < 0) f[u] = 0;
}

template <typename T>
void read(T &Re) {
  T k = 0;
  char ch = getchar();
  int flag = 1;
  while (!isNum(ch)) {
    if (ch == '-') flag = -1;
    ch = getchar();
  }
  while (isNum(ch)) {
    k = (k << 1) + (k << 3) + ch - '0';
    ch = getchar();
  }
  Re = flag * k;
}
template <typename T>
void write(const T &Wr) {
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
