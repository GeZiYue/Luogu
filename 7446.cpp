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

const int N = 400005;
const int B = 650;
const int Bn = N / B + 5;

int find_bel(int x);
int find_Bl(int x);
int find_Br(int x);
int find_fa(int x);
int find_top(int x);
void build(int x);
void update(int l, int r, int x);
int query(int l, int r);

int fa[N], top[N], tag[Bn];
int num[N];
int n, q;

int main() {
  read(n), read(q);
  for (int i = 2; i <= n; ++i) read(fa[i]);
  for (int i = 1; i <= (n - 1) / B + 1; ++i) build(i);
  int lasans = 0;
  while (q--) {
    int op;
    read(op);
    if (op == 1) {
      int l, r, x;
      read(l), read(r), read(x);
      l ^= lasans, r ^= lasans, x ^= lasans;
      update(l, r, x);
    } else {
      int u, v;
      read(u), read(v);
      u ^= lasans, v ^= lasans;
      write(lasans = query(u, v)), EL;
    }
  }
  return 0;
}

void build(int x) {
  int Bl = find_Bl(x), Br = find_Br(x);
  for (int i = Bl; i <= Br; ++i) {
    fa[i] = std::max(1, fa[i] - tag[x]);
  }
  tag[x] = 0;
  for (int i = Bl; i <= Br; ++i) {
    if (fa[i] < Bl) {
      top[i] = fa[i];
    } else {
      top[i] = top[fa[i]];
    }
  }
}
void update(int l, int r, int x) {
  int Bl = find_bel(l), Br = find_bel(r);
  if (Bl == Br) {
    for (int i = l; i <= r; ++i) {
      fa[i] = std::max(1, fa[i] - x);
    }
    build(Bl);
    return;
  }
  for (int i = l; i <= find_Br(Bl); ++i) {
    fa[i] = std::max(1, fa[i] - x);
  }
  build(Bl);
  for (int i = find_Bl(Br); i <= r; ++i) {
    fa[i] = std::max(1, fa[i] - x);
  }
  build(Br);
  for (int i = Bl + 1; i < Br; ++i) {
    tag[i] += x;
    if (num[i] <= B) {
      build(i);
      ++num[i];
    }
  }
}
int query(int l, int r) {
  while (l != r) {
    if (find_bel(l) < find_bel(r)) {
      std::swap(l, r);
    }
    if (find_bel(l) > find_bel(r)) {
      l = find_top(l);
    } else {
      if (find_top(l) != find_top(r)) {
        l = find_top(l), r = find_top(r);
      } else {
        while (l != r) {
          if (l > r) {
            l = find_fa(l);
          } else {
            r = find_fa(r);
          }
        }
      }
    }
  }
  return l;
}
int find_bel(int x) { return (x - 1) / B + 1; }
int find_Bl(int x) { return (x - 1) * B + 1; }
int find_Br(int x) { return std::min(n, x * B); }
int find_fa(int x) { return std::max(1, fa[x] - tag[find_bel(x)]); }
int find_top(int x) { return std::max(1, top[x] - tag[find_bel(x)]); }

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
