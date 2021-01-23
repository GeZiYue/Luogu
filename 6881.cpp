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

constexpr int N = 200005;

class Seg_Tree {
 public:
  ll sum[N << 3], tag[N << 3];
  void pushdown(int x, int xl, int xr);
  void update(int x, int xl, int xr, int ul, int ur, int num);
  ll query(int x, int xl, int xr, int ql, int qr);
} L1, L2, R1, R2;

void init();

int pre[N], suf[N];
int a[N];
std::vector<int> V1[N], V2[N], V3[N];
std::vector<std::tuple<int, int, int> > Q[N];
ll ans[N];
int n, q;

int main() {
  read(n), read(q);
  for (int i = 1; i <= n; ++i) {
    read(a[i]);
  }
  init();
  for (int i = 1; i <= n; ++i) {
    L1.update(1, -n, n, -n, i, a[i]);
    R2.update(1, -n, n, -n, i - 1, a[i]);
    V1[suf[i] - i].push_back(i);
    if (pre[i]) {
      V2[i - pre[i]].push_back(i);
      V3[suf[i] - pre[i]].push_back(i);
    }
  }
  for (int i = 1; i <= q; ++i) {
    int t, l, r;
    read(t), read(l), read(r);
    if (t < n) {
      ++t;
    }
    Q[t].emplace_back(l, r, i);
  }
  for (int t = 1; t <= n; ++t) {
    for (auto i : V1[t]) {
      R2.update(1, -n, n, -n, i - 1, -a[i]);
      R1.update(1, -n, n, -n, suf[i] - 1, a[i]);
    }
    for (auto i : V2[t]) {
      L1.update(1, -n, n, -n, i, -a[i]);
      L2.update(1, -n, n, -n, pre[i], a[i]);
    }
    for (auto i : V3[t]) {
      R1.update(1, -n, n, -n, suf[i] - 1, -a[i]);
      L2.update(1, -n, n, -n, pre[i], -a[i]);
    }
    for (auto j : Q[t]) {
      int l = std::get<0>(j), r = std::get<1>(j);
      ans[std::get<2>(j)] = R1.query(1, -n, n, l, r) + R2.query(1, -n, n, l - t, r - t) -
                            L1.query(1, -n, n, l + 1, r + 1) -
                            L2.query(1, -n, n, l + 1 - t, r + 1 - t);
    }
  }
  for (int i = 1; i <= q; ++i) {
    write(ans[i]), EL;
  }
  return 0;
}

void init() {
  std::stack<int> St;
  for (int i = 1; i <= n; ++i) {
    while (!St.empty() && a[i] >= a[St.top()]) {
      St.pop();
    }
    if (St.empty()) {
      pre[i] = 0;
    } else {
      pre[i] = St.top();
    }
    St.push(i);
  }
  while (!St.empty()) {
    St.pop();
  }
  for (int i = n; i >= 1; --i) {
    while (!St.empty() && a[i] > a[St.top()]) {
      St.pop();
    }
    if (St.empty()) {
      suf[i] = n + 1;
    } else {
      suf[i] = St.top();
    }
    St.push(i);
  }
}

void Seg_Tree::pushdown(int x, int xl, int xr) {
  if (tag[x]) {
    int xm = (xl + xr) >> 1;
    sum[x << 1] += (xm - xl + 1) * tag[x];
    sum[x << 1 | 1] += (xr - xm) * tag[x];
    tag[x << 1] += tag[x];
    tag[x << 1 | 1] += tag[x];
    tag[x] = 0;
  }
}
void Seg_Tree::update(int x, int xl, int xr, int ul, int ur, int num) {
  if (ul <= xl && xr <= ur) {
    tag[x] += num;
    sum[x] += 1ll * (xr - xl + 1) * num;
    return;
  }
  pushdown(x, xl, xr);
  int xm = (xl + xr) >> 1;
  if (ul <= xm) {
    update(x << 1, xl, xm, ul, ur, num);
  }
  if (ur > xm) {
    update(x << 1 | 1, xm + 1, xr, ul, ur, num);
  }
  sum[x] = sum[x << 1] + sum[x << 1 | 1];
}
ll Seg_Tree::query(int x, int xl, int xr, int ql, int qr) {
  if (ql <= xl && xr <= qr) {
    return sum[x];
  }
  pushdown(x, xl, xr);
  int xm = (xl + xr) >> 1;
  ll ans = 0;
  if (ql <= xm) {
    ans += query(x << 1, xl, xm, ql, qr);
  }
  if (qr > xm) {
    ans += query(x << 1 | 1, xm + 1, xr, ql, qr);
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
