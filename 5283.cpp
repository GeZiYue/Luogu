#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <complex>
#include <cstdio>
#include <string>
#include <vector>
#include <bitset>
#include <cmath>
#include <queue>
#include <stack>
#include <set>
#include <map>

#define isNum(a) (a >= '0' && a <= '9')
#define SP putchar(' ')
#define EL putchar('\n')
#define File(a) freopen(a ".in", "r", stdin), freopen(a ".out", "w", stdout)

template<class T>
void read(T&);
template<class T>
void write(const T&);

typedef long long ll;
typedef unsigned long long ull;
typedef const long long & cll;
typedef const int & ci;
typedef std::pair<int, int> pii;
const int iinf = 2147483647;
const ll llinf = 9223372036854775807ll;
using std::min;
using std::max;
using std::abs;
using std::sort;

const int N = 500005;
const int M = 35;
typedef unsigned int ui;

class Node {
public:
  int to[2];
  int id;
  int sum;
};
Node tre[N * M];
int siz;
int rot[N];
void insert(int&, int, int, ui);
int query(int, int, int, ui);

class Ans {
public:
  int bas, l, r, mid;
  ui val;
  bool operator < (const Ans &i) const {
    return val < i.val;
  }
};
std::priority_queue<Ans> pq;
Ans calc(int, int, int);

ui a[N];
int n, k;
int cnt;
ll ans;

int main () {
  read(n), read(k);
  for (int i = 1; i <= n; ++i) {
    read(a[i]);
    a[i] ^= a[i - 1];
    insert(rot[i] = rot[i - 1], 31, i, a[i]);
  }
  for (int i = 1; i <= n; ++i) {
    pq.push(calc(i - 1, i, n));
  }
  while (cnt < k) {
    ++cnt;
    Ans now = pq.top();
    pq.pop();
    ans += now.val;
    if (now.mid ^ now.l) {
      pq.push(calc(now.bas, now.l, now.mid - 1));
    }
    if (now.mid ^ now.r) {
      pq.push(calc(now.bas, now.mid + 1, now.r));
    }
  }
  write(ans), EL;
  return 0;
}

template<class T>
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
template<class T>
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

void insert(int &x, int dep, int id, ui a) {
  tre[++siz] = tre[x];
  x = siz;
  ++tre[x].sum;
  if (dep < 0) {
    tre[x].id = id;
    return;
  }
  insert(tre[x].to[(a >> dep) & 1], dep - 1, id, a);
}
int query(int lx, int rx, int dep, ui a) {
  if (dep < 0) {
    return tre[rx].id;
  }
  bool d = (a >> dep) & 1;
  if (tre[tre[rx].to[d ^ 1]].sum - tre[tre[lx].to[d ^ 1]].sum) {
    return query(tre[lx].to[d ^ 1], tre[rx].to[d ^ 1], dep - 1, a);
  } else {
    return query(tre[lx].to[d], tre[rx].to[d], dep - 1, a);
  }
}
Ans calc(int bas, int l, int r) {
  Ans ans;
  ans.bas = bas, ans.l = l, ans.r = r;
  ans.mid = query(rot[l - 1], rot[r], 31, a[bas]);
  ans.val = a[ans.mid] ^ a[bas];
  return ans;
}
