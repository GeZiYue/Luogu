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

const int N = 200005;

namespace BIT {
ll BIT1[N], BIT2[N];
void update(ll l, ll r, ll x);
ll query(int x);
}  // namespace BIT

int getid(ll x);
pii queryA(int l, int r);
pii queryB(int l, int r);

std::vector<std::tuple<int, int, int>> Q[N];
int all[N], tot;
int lg2[N];
pii stA[20][N], stB[20][N];
ll ans[N];
ll X[N];
int sta[N], top;
int A[N], B[N];
int n, m;

int main() {
  read(n), read(m);
  for (int i = 1; i <= n; ++i) {
    read(A[i]);
    X[i + 1] = X[i] + A[i];
  }
  for (int i = 1; i <= n; ++i) read(B[i]);
  lg2[1] = 0;
  for (int i = 2; i <= n; ++i) lg2[i] = lg2[i >> 1] + 1;
  for (int i = 1; i <= n; ++i) {
    stA[0][i] = pii(A[i], i);
    stB[0][i] = pii(B[i], i);
  }
  for (int k = 1; k <= lg2[n]; ++k) {
    for (int i = 1; i <= n - (1 << k) + 1; ++i) {
      stA[k][i] = std::max(stA[k - 1][i], stA[k - 1][i + (1 << (k - 1))]);
      stB[k][i] = std::min(stB[k - 1][i], stB[k - 1][i + (1 << (k - 1))]);
    }
  }
  for (int i = 1; i <= m; ++i) {
    int s, t, u;
    read(s), read(t), read(u);
    if (queryA(s, t - 1).first > u) {
      ans[i] = -1;
      continue;
    }
    all[++tot] = u;
    int mid =
        queryB(std::max(s, static_cast<int>(std::lower_bound(X + 1, X + n + 2, X[t] - u) - X)),
               t - 1)
            .second;
    ans[i] = (X[t] - X[mid]) * B[mid];
    Q[s].emplace_back(i, 1, u);
    Q[mid].emplace_back(i, -1, u);
  }
  std::sort(all + 1, all + tot + 1);
  tot = std::unique(all + 1, all + tot + 1) - all - 1;
  sta[top = 1] = n + 1;
  for (int i = n; i >= 1; --i) {
    while (B[i] < B[sta[top]]) {
      BIT::update(X[sta[top]] - X[i] + 1, X[sta[top - 1]] - X[i], -B[sta[top]]);
      --top;
    }
    BIT::update(1, X[sta[top]] - X[i], B[i]);
    sta[++top] = i;
    for (const auto &[id, k, u] : Q[i]) ans[id] += k * BIT::query(u);
  }
  for (int i = 1; i <= m; ++i) {
    write(ans[i]), EL;
  }
  return 0;
}

pii queryA(int l, int r) {
  int k = lg2[r - l + 1];
  return std::max(stA[k][l], stA[k][r - (1 << k) + 1]);
}
pii queryB(int l, int r) {
  int k = lg2[r - l + 1];
  return std::min(stB[k][l], stB[k][r - (1 << k) + 1]);
}
int getid(ll x) { return std::lower_bound(all + 1, all + tot + 1, x) - all; }

namespace BIT {
void update(ll *A, int x, ll num) {
  while (x <= n) {
    A[x] += num;
    x += x & -x;
  }
}
ll query(ll *A, int x) {
  ll ans = 0;
  while (x) {
    ans += A[x];
    x -= x & -x;
  }
  return ans;
}
void update(ll l, ll r, ll x) {
  int idl = getid(l), idr = getid(r);
  update(BIT1, idl, x);
  update(BIT1, idr, -x);
  update(BIT2, idl, -(l - 1) * x);
  update(BIT2, idr, r * x);
}
ll query(int x) {
  int id = getid(x);
  return query(BIT1, id) * x + query(BIT2, id);
}
}  // namespace BIT

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
