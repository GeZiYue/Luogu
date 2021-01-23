#include <algorithm>
#include <bitset>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

#define isNum(a) (a >= '0' && a <= '9')
#define SP putchar(' ')
#define EL putchar('\n')
#define File(a) freopen(a ".in", "r", stdin), freopen(a ".out", "w", stdout)

template <class T>
void read(T &);
template <class T>
void write(const T &);

typedef long long ll;
typedef unsigned long long ull;
typedef const long long &cll;
typedef const int &ci;
typedef std::pair<int, int> pii;
const int iinf = 2147483647;
const ll llinf = 9223372036854775807ll;
using std::abs;
using std::max;
using std::min;

constexpr int N = 100005;
constexpr int M = 15;

class Poly {
 public:
  double num[M];
  Poly() {
    for (int i = 0; i < M; ++i) {
      num[i] = 0;
    }
  }
  Poly &operator+=(const Poly &p) {
    for (int i = 0; i < M; ++i) {
      num[i] += p.num[i];
    }
    return *this;
  }
  double getnum(double x) {
    double ans = 0;
    double now = 1;
    for (int i = 0; i < M; ++i, now *= x) {
      ans += now * num[i];
    }
    return ans;
  }
};
namespace LCT {
class Node {
 public:
  int ch[2], fa;
  Poly val;
  Poly sum;
  bool rev;
} tre[N];
int sta[N];
#define lc(x) (tre[x].ch[0])
#define rc(x) (tre[x].ch[1])
#define fa(x) (tre[x].fa)
#define val(x) (tre[x].val)
#define sum(x) (tre[x].sum)
#define rev(x) (tre[x].rev)
void link(int u, int v);
void cut(int u, int v);
void change(int x, int id, double a, double b);
void query(int u, int v, double x);
}  // namespace LCT

char ch[15];
int n, m, type;

int main() {
  read(n), read(m);
  scanf("%s", ch + 1);
  using namespace LCT;
  for (int i = 1; i <= n; ++i) {
    int id;
    double a, b;
    read(id);
    scanf("%lf %lf", &a, &b);
    change(i, id, a, b);
  }
  for (int i = 1; i <= m; ++i) {
    scanf("%s", ch + 1);
    if (ch[1] == 'a') {
      int u, v;
      read(u), read(v);
      ++u, ++v;
      link(u, v);
    } else {
      if (ch[1] == 'd') {
        int u, v;
        read(u), read(v);
        ++u, ++v;
        cut(u, v);
      } else {
        if (ch[1] == 'm') {
          int x, id;
          read(x), read(id);
          ++x;
          double a, b;
          scanf("%lf %lf", &a, &b);
          change(x, id, a, b);
        } else {
          int u, v;
          read(u), read(v);
          ++u, ++v;
          double x;
          scanf("%lf", &x);
          query(u, v, x);
        }
      }
    }
  }
  return 0;
}

void sin(Poly &p, double a, double b) {
  double sinc = std::cos(b), cosc = std::sin(b);
  double now = 1;
  for (int i = 0; i < M; ++i) {
    p.num[i] = ((i & 2) ? -1 : 1) * ((i & 1) ? sinc : cosc) * now;
    now = now * a / (i + 1);
  }
}
void exp(Poly &p, double a, double b) {
  double now = std::exp(b);
  for (int i = 0; i < M; ++i) {
    p.num[i] = now;
    now = now * a / (i + 1);
  }
}
void line(Poly &p, double a, double b) {
  for (int i = 0; i < M; ++i) {
    p.num[i] = 0;
  }
  p.num[0] = b;
  p.num[1] = a;
}

namespace LCT {
bool nroot(int x) { return lc(fa(x)) == x || rc(fa(x)) == x; }
bool getid(int x) { return rc(fa(x)) == x; }
void pushup(int x) {
  sum(x) = val(x);
  sum(x) += sum(lc(x));
  sum(x) += sum(rc(x));
}
void reverse(int x) { lc(x) ^= rc(x) ^= lc(x) ^= rc(x), rev(x) ^= 1; }
void pushdown(int x) {
  if (rev(x)) {
    reverse(lc(x)), reverse(rc(x));
    rev(x) = false;
  }
}
void rotate(int x) {
  int y = fa(x), z = fa(y), yid = getid(x), zid = getid(y), w = tre[x].ch[yid ^ 1];
  if (nroot(y)) {
    tre[z].ch[zid] = x;
  }
  tre[x].ch[yid ^ 1] = y;
  tre[y].ch[yid] = w;
  fa(x) = z;
  fa(y) = x;
  if (w) {
    fa(w) = y;
  }
  pushup(y);
}
void splay(int x) {
  int y = x, z = 0;
  sta[++z] = y;
  while (nroot(y)) {
    sta[++z] = y = fa(y);
  }
  while (z) {
    pushdown(sta[z--]);
  }
  while (nroot(x)) {
    y = fa(x);
    if (nroot(y)) {
      rotate(getid(x) == getid(y) ? y : x);
    }
    rotate(x);
  }
  pushup(x);
}
void access(int x) {
  for (int y = 0; x; x = fa(y = x)) {
    splay(x), rc(x) = y, pushup(x);
  }
}
int findroot(int x) {
  access(x), splay(x);
  while (true) {
    pushdown(x);
    if (lc(x)) {
      x = lc(x);
    } else {
      break;
    }
  }
  splay(x);
  return x;
}
void makeroot(int x) { access(x), splay(x), reverse(x); }
void link(int u, int v) { makeroot(u), fa(u) = v, pushup(v); }
void cut(int u, int v) { makeroot(u), access(v), splay(v), fa(u) = lc(v) = 0, pushup(v); }
void change(int x, int id, double a, double b) {
  if (id == 1) {
    sin(val(x), a, b);
  } else {
    if (id == 2) {
      exp(val(x), a, b);
    } else {
      line(val(x), a, b);
    }
  }
  pushup(x);
  splay(x);
}
void query(int u, int v, double x) {
  makeroot(u);
  if (findroot(v) != u) {
    puts("unreachable");
  } else {
    access(v), splay(v);
    printf("%.10lf\n", sum(v).getnum(x));
  }
}
}  // namespace LCT

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
