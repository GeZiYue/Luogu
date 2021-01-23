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
using std::sort;

constexpr int N = 100005;

namespace Leftist_Tree {
class Node {
 public:
  int val, fa, dis, ch[2];
} tre[N];
#define lc(x) (tre[x].ch[0])
#define rc(x) (tre[x].ch[1])
#define val(x) (tre[x].val)
#define fa(x) (tre[x].fa)
#define dis(x) (tre[x].dis)
bool cmp(int x, int y);
int getfa(int x);
int merge(int x, int y);
void pop(int x);
}  // namespace Leftist_Tree

int n, q;

int main() {
  read(n), read(q);
  using namespace Leftist_Tree;
  for (int i = 1; i <= n; ++i) {
    read(val(i));
    fa(i) = i;
  }
  val(0) = -1;
  for (int i = 1; i <= q; ++i) {
    int op;
    read(op);
    if (op == 1) {
      int x, y;
      read(x), read(y);
      if (val(x) == -1 || val(y) == -1) {
        continue;
      }
      int fx = getfa(x), fy = getfa(y);
      if (fx ^ fy) {
        fa(fx) = fa(fy) = merge(fx, fy);
      }
    } else {
      int x;
      read(x);
      if (val(x) == -1) {
        write(-1), EL;
        continue;
      }
      int fx = getfa(x);
      write(val(fx)), EL;
      pop(fx);
    }
  }
  return 0;
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

bool Leftist_Tree::cmp(int x, int y) { return (val(x) < val(y)) || (val(x) == val(y) && x < y); }
int Leftist_Tree::getfa(int x) { return (fa(x) == x) ? x : (fa(x) = getfa(fa(x))); }
int Leftist_Tree::merge(int x, int y) {
  if (x == 0 || y == 0) {
    return x + y;
  }
  if (!cmp(x, y)) {
    std::swap(x, y);
  }
  rc(x) = merge(rc(x), y);
  if (dis(lc(x)) < dis(rc(x))) {
    std::swap(lc(x), rc(x));
  }
  fa(lc(x)) = fa(rc(x)) = fa(x) = x;
  dis(x) = dis(rc(x)) + 1;
  return x;
}
void Leftist_Tree::pop(int x) {
  val(x) = -1;
  fa(lc(x)) = lc(x);
  fa(rc(x)) = rc(x);
  fa(x) = merge(lc(x), rc(x));
}
