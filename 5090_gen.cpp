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

constexpr int N = 100005;
constexpr int M = 200005;

void add(int u, int v);
int gcd(int a, int b);
void dfs(int u, int fa);

int hed[N], nxt[M], to[M], id;
int ansp[N], nowp[N];
int ans[N], now[N];
int tot, minn;
std::list<int> L;
std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
int n;

int main() {
  File("10");
  int T;
  read(T);
  while (T--) {
    memset(hed, 0, sizeof(hed));
    id = 0;
    read(n);
    for (int i = 1; i < n; ++i) {
      int u, v;
      read(u), read(v);
      add(u, v), add(v, u);
    }
    minn = n;
    for (int i = 1; i <= n; ++i) {
      ansp[i] = i;
    }
    while (true) {
      for (int i = 1; i <= n; ++i) {
        nowp[i] = ansp[i];
        now[i] = 0;
      }
      for (int i = 1; i <= 20000; ++i) {
        std::swap(nowp[rnd() % n + 1], nowp[rnd() % n + 1]);
      }
      L.clear();
      for (int i = 1; i <= n; ++i) {
        L.push_back(nowp[i]);
      }
      tot = 0;
      dfs(1, 0);
      std::cerr << tot << std::endl;
      if (tot <= minn) {
        minn = tot;
        for (int i = 1; i <= n; ++i) {
          ansp[i] = nowp[i];
          ans[i] = now[i];
        }
        if (minn == 0) {
          break;
        }
      }
    }
    for (int i = 1; i <= n; ++i) {
      write(ans[i]), SP;
    }
    EL;
  }
  return 0;
}

void add(int u, int v) {
  nxt[++id] = hed[u];
  hed[u] = id;
  to[id] = v;
}
int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }
void dfs(int u, int fa) {
  for (auto it = L.begin(); it != L.end(); ++it) {
    if (!fa || gcd(now[fa], *it) == 1) {
      now[u] = *it;
      L.erase(it);
      break;
    }
  }
  if (!now[u]) {
    now[u] = *L.begin();
    L.erase(L.begin());
    ++tot;
  }
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    if (v == fa) {
      continue;
    }
    dfs(v, u);
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
