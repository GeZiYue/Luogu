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

constexpr int N = 200005;

class Node {
 public:
  ll x, y;
  ll dep() { return x + y; }
  ll lowx() {
    if (!x) {
      return 1ll << 62 | 1;
    }
    return x & -x;
  }
  ll lowy() {
    if (!y) {
      return 1ll << 62 | 1;
    }
    return y & -y;
  }
  Node jump() {
    if (lowx() < lowy()) {
      return {x - (x & -x), y};
    } else {
      return {x, y - (y & -y)};
    }
  }
};

bool check(Node a, Node b);
Node lca(Node a, Node b);
void find(Node a, int k);

ll x[N], y[N];
ll sx, sy, ex, ey;
int ans[N];
int n;

int main() {
  read(n);
  for (int i = 1; i <= n; ++i) {
    read(x[i]), read(y[i]);
  }
  read(sx), read(sy), read(ex), read(ey);
  Node a{sx, sy}, b = {ex, ey}, LCA = lca(a, b);
  find(a, 1);
  find(b, 1);
  find(LCA, -2);
  for (int i = 1; i <= n; ++i) {
    if (x[i] == LCA.x && y[i] == LCA.y) {
      ++ans[i];
    }
  }
  write(a.dep() + b.dep() - 2 * LCA.dep()), EL;
  for (int i = 1; i <= n; ++i) {
    write(ans[i]);
  }
  EL;
  return 0;
}

bool check(Node a, Node b) {
  if (a.x == b.x) {
    if (a.y < b.y) {
      std::swap(a, b);
    }
    if (a.y >= b.y && (a.y - (a.y & -a.y)) <= b.y) {
      return true;
    }
  }
  if (a.y == b.y) {
    if (a.x < b.x) {
      std::swap(a, b);
    }
    if (a.x >= b.x && (a.x - (a.x & -a.x)) <= b.x) {
      return true;
    }
  }
  return false;
}
Node lca(Node a, Node b) {
  while (!check(a, b)) {
    if (a.jump().dep() >= b.jump().dep()) {
      a = a.jump();
    } else {
      b = b.jump();
    }
  }
  return a.dep() < b.dep() ? a : b;
}
void find(Node a, int k) {
  std::vector<std::tuple<ll, ll, ll, ll> > V;
  while (true) {
    Node c = a.jump();
    V.emplace_back(a.x, a.y, c.x, c.y);
    a = c;
    if (a.x == 0 && a.y == 0) {
      break;
    }
  }
  for (int j = 1; j <= n; ++j) {
    ll x1, y1, x2, y2;
    for (auto i : V) {
      std::tie(x1, y1, x2, y2) = i;
      if (x1 == x2 && x[j] == x1 && y[j] >= y2 && y[j] <= y1) {
        ans[j] += k;
        break;
      }
      if (y1 == y2 && y[j] == y1 && x[j] >= x2 && x[j] <= x1) {
        ans[j] += k;
        break;
      }
    }
  }
}

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
