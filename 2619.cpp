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

constexpr int N = 50005;
constexpr int M = 100005;

class Edge {
 public:
  int u, v, w, c;
  bool operator<(Edge i) const { return (w == i.w) ? (c > i.c) : (w < i.w); }
} E[M];

int find(int x);
bool check(int mid);

int fa[N];
int num, ans;
int n, m, k;

int main() {
  read(n), read(m), read(k);
  for (int i = 1; i <= m; ++i) {
    int u, v, w, c;
    read(u), read(v), read(w), read(c);
    E[i] = {u + 1, v + 1, w, c};
  }
  int l = -400, r = 400;
  int res = 0;
  while (l <= r) {
    int mid = (l + r) >> 1;
    if (check(mid)) {
      l = mid + 1;
    } else {
      res = ans - k * mid;
      r = mid - 1;
    }
  }
  write(res), EL;
  return 0;
}

int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
bool check(int mid) {
  for (int i = 1; i <= m; ++i) {
    if (!E[i].c) {
      E[i].w += mid;
    }
  }
  std::sort(E + 1, E + m + 1);
  for (int i = 1; i <= n; ++i) {
    fa[i] = i;
  }
  num = 0, ans = 0;
  int now = 0;
  for (int i = 1; i <= m; ++i) {
    int u = E[i].u, v = E[i].v, fu = find(u), fv = find(v);
    if (fu ^ fv) {
      fa[fu] = fv;
      if (!E[i].c) {
        ++num;
      }
      ++now;
      ans += E[i].w;
      if (now >= n - 1) {
        break;
      }
    }
  }
  for (int i = 1; i <= m; ++i) {
    if (!E[i].c) {
      E[i].w -= mid;
    }
  }
  return num > k;
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
