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

constexpr int N = 300005;

int find(int x);

std::queue<pii> q;
std::map<int, int> mp[N];
int fa[N];
int n, m, k;

int main() {
  read(n), read(m), read(k);
  for (int i = 1; i <= n; ++i) {
    fa[i] = i;
  }
  for (int i = 1; i <= m; ++i) {
    int u, v, w;
    read(u), read(v), read(w);
    if (mp[v][w]) {
      q.emplace(u, mp[v][w]);
    } else {
      mp[v][w] = u;
    }
  }
  while (!q.empty()) {
    auto [u, v] = q.front();
    q.pop();
    fa[find(u)] = find(v);
    if (mp[u].size() < mp[v].size()) {
      mp[v].merge(mp[u]);
    } else {
      mp[u].merge(mp[v]);
    }
  }
  return 0;
}

int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

template <typename T>
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
template <typename T>
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
