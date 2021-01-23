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

constexpr int N = 18;
constexpr int M = 1 << 17;

void dfs(int u, int fa);

ll f[N][N][M];
ll sum[M];
bool G1[N][N], G2[N][N];
int popc[M];
int n, m, S;

int main() {
  read(n), read(m);
  S = 1 << n;
  for (int i = 1; i < S; ++i) {
    popc[i] = popc[i >> 1] + (i & 1);
  }
  for (int i = 1; i <= m; ++i) {
    int u, v;
    read(u), read(v);
    --u, --v;
    G2[u][v] = G2[v][u] = true;
  }
  for (int i = 1; i < n; ++i) {
    int u, v;
    read(u), read(v);
    --u, --v;
    G1[u][v] = G1[v][u] = true;
  }
  dfs(0, -1);
  ll ans = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < S; ++j) {
      if (popc[(S - 1) ^ j] & 1) {
        ans -= f[0][i][j];
      } else {
        ans += f[0][i][j];
      }
    }
  }
  write(ans), EL;
  return 0;
}

void dfs(int u, int fa) {
  for (int i = 0; i < n; ++i) {
    int k = 1 << i;
    for (int j = k; j < S; j = (j + 1) | k) {
      f[u][i][j] = 1;
    }
  }
  for (int v = 0; v < n; ++v) {
    if (!G1[u][v] || v == fa) {
      continue;
    }
    dfs(v, u);
    for (int i = 0; i < n; ++i) {
      memset(sum, 0, sizeof(sum));
      for (int j = 0; j < n; ++j) {
        if (!G2[i][j]) {
          continue;
        }
        int k = (1 << i) | (1 << j);
        for (int s = k; s < S; s = (s + 1) | k) {
          sum[s] += f[v][j][s];
        }
      }
      int k = 1 << i;
      for (int s = k; s < S; s = (s + 1) | k) {
        f[u][i][s] *= sum[s];
      }
    }
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
