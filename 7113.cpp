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

const int N = 100005;
const int M = 500005;
#define ll __int128

class Frac {
 public:
  ll a, b;
  Frac(ll aa = 0, ll bb = 1) : a(aa), b(bb) {}
  void mini();
  Frac operator+(const Frac &i) const;
  Frac operator*(const Frac &i) const;
};

ll gcd(ll a, ll b);
ll lcm(ll a, ll b);
void add(int u, int v);

int hed[N], nxt[M], to[M], id;
Frac ans[N];
int deg[N];
int out[N];
int n, m;

int main() {
  read(n), read(m);
  for (int i = 1; i <= n; ++i) {
    int d;
    read(d);
    for (int j = 1; j <= d; ++j) {
      int v;
      read(v);
      add(i, v);
      ++deg[v];
    }
    out[i] = d;
  }
  std::queue<int> q;
  for (int i = 1; i <= m; ++i) {
    ans[i] = 1;
  }
  for (int i = 1; i <= n; ++i) {
    if (deg[i] == 0) {
      q.push(i);
    }
  }
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    if (out[u] == 0) {
      continue;
    }
    Frac now = ans[u] * Frac(1, out[u]);
    for (int i = hed[u]; i; i = nxt[i]) {
      int v = to[i];
      --deg[v];
      ans[v] = ans[v] + now;
      if (deg[v] == 0) {
        q.push(v);
      }
    }
  }
  for (int i = 1; i <= n; ++i) {
    if (out[i] == 0) {
      write(ans[i].a), SP, write(ans[i].b), EL;
    }
  }
  return 0;
}

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }
ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }
void add(int u, int v) {
  nxt[++id] = hed[u];
  hed[u] = id;
  to[id] = v;
}

void Frac::mini() {
  ll k = gcd(a, b);
  a /= k, b /= k;
}
Frac Frac::operator+(const Frac &i) const {
  ll k = lcm(b, i.b);
  Frac ans(a * k / b + i.a * k / i.b, k);
  ans.mini();
  return ans;
}
Frac Frac::operator*(const Frac &i) const {
  Frac ans(a * i.a, b * i.b);
  ans.mini();
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
