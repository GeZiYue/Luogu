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

constexpr int N = 605;

int mincut(int x);
int Stoer_Wagner();

int dis[N][N];
bool vis[N], mer[N];
int w[N], ord[N];
int S, T;
int n, m;

int main() {
  read(n), read(m);
  for (int i = 1; i <= m; ++i) {
    int u, v, w;
    read(u), read(v), read(w);
    dis[u][v] += w, dis[v][u] += w;
  }
  write(Stoer_Wagner()), EL;
  return 0;
}

int mincut(int x) {
  std::fill(w, w + n + 1, 0);
  std::fill(vis, vis + n + 1, false);
  w[0] = -1;
  for (int i = 1; i <= n - x + 1; ++i) {
    int mx = 0;
    for (int j = 1; j <= n; ++j) {
      if (!mer[j] && !vis[j] && w[j] > w[mx]) {
        mx = j;
      }
    }
    ord[i] = mx;
    vis[mx] = true;
    for (int j = 1; j <= n; ++j) {
      if (!mer[j] && !vis[j]) {
        w[j] += dis[mx][j];
      }
    }
  }
  S = ord[n - x], T = ord[n - x + 1];
  return w[T];
}
int Stoer_Wagner() {
  int ans = iinf;
  for (int i = 1; i < n; ++i) {
    ans = std::min(ans, mincut(i));
    mer[T] = true;
    for (int j = 1; j <= n; ++j) {
      dis[S][j] += dis[T][j];
      dis[j][S] += dis[j][T];
    }
  }
  return ans;
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
