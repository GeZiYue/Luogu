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

const int N = 100005;

void addedge(int u, int v, int c, int w);

std::unordered_map<int, ll> sum[N], dis[N];
std::unordered_map<int, int> len[N], col[N];
std::unordered_map<int, std::vector<pii>> mp[N];

int n, m;

int main() {
  read(n), read(m);
  for (int i = 1; i <= m; ++i) {
    int u, v, c, w;
    read(u), read(v), read(c), read(w);
    addedge(u, v, c, w), addedge(v, u, c, w);
  }
  std::priority_queue<std::tuple<ll, int, int>> pq;
  auto upd = [&](int v, int c, ll udis) {
    if (!dis[v].count(c) || dis[v][c] > udis) {
      dis[v][c] = udis;
      pq.emplace(-udis, v, c);
    }
  };
  upd(1, 0, 0);
  while (!pq.empty()) {
    auto [d, u, c] = pq.top();
    d = -d;
    pq.pop();
    if (d != dis[u][c]) continue;
    for (auto [v, vc] : mp[u][c]) {
      ll w;
      if (c == vc)
        w = std::min(1ll * len[u][v], sum[u][col[u][v]] - len[u][v]);
      else if (c)
        w = sum[u][c] - len[u][v];
      else
        w = 0;
      upd(v, vc, d + w);
    }
  }
  if (dis[n].count(0))
    write(dis[n][0]), EL;
  else
    puts("-1");
  return 0;
}

void addedge(int u, int v, int c, int w) {
  col[u][v] = c, len[u][v] = w;
  sum[u][c] += w;
  mp[u][0].emplace_back(v, 0);
  mp[u][0].emplace_back(v, c);
  mp[u][c].emplace_back(v, 0);
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
