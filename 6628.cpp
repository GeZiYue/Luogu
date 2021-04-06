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

constexpr int N = 2505;

int find(int x);

std::vector<int> G[N];
int fa[N];
int bel[N];
int n, m, s;

int main() {
  read(n), read(m), read(s);
  for (int i = 1; i <= n; ++i) {
    fa[i] = i;
  }
  int sum = 0;
  for (int i = 1; i <= m; ++i) {
    int u, v;
    read(u), read(v);
    G[u].push_back(v), G[v].push_back(u);
    sum += std::abs(v - u);
    fa[find(u)] = find(v);
  }
  for (int i = 1; i <= n; ++i) {
    bel[i] = find(i);
  }
  for (int i = 1; i <= n; ++i) {
    int ans = sum;
    for (int j = 1; j <= n; ++j) {
      fa[j] = j;
    }
    G[s].push_back(i), G[i].push_back(s);
    fa[find(bel[s])] = find(bel[i]);
    for (int j = 1, las = 0; j <= n; ++j) {
      if (G[j].size() & 1) {
        if (las) {
          ans += j - las;
          for (int k = las; k < j; ++k) {
            fa[find(bel[k])] = find(bel[j]);
          }
          las = 0;
        } else {
          las = j;
        }
      }
    }
    std::vector<std::tuple<int, int, int>> V;
    for (int j = 1, las = 0; j <= n; ++j) {
      if (G[j].size()) {
        if (las && find(bel[las]) != find(bel[j])) {
          V.emplace_back(j - las, bel[las], bel[j]);
        }
        las = j;
      }
    }
    std::sort(V.begin(), V.end());
    for (auto [w, u, v] : V) {
      if (find(u) != find(v)) {
        ans += 2 * w;
        fa[find(u)] = find(v);
      }
    }
    G[s].pop_back(), G[i].pop_back();
    write(ans), putchar(" \n"[i == n]);
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
