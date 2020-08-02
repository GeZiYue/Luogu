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
#include <ctime>
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

const int N = 600005;
const int M = 24;

void insert(int &, int, int);
int query(int, int, int, int);

class Node {
public:
  int ch[2];
  int val;
};
Node trie[N * M];
int rot[N];
int tot;
int sum;
int n, m;

int main () {
  read(n), read(m);
  insert(rot[0], 0, 23);
  for (int i = 1; i <= n; ++i) {
    int a;
    read(a);
    sum ^= a;
    insert(rot[i] = rot[i - 1], sum, 23);
  }
  for (int i = 1; i <= m; ++i) {
    char ch = getchar();
    while (ch != 'A' && ch != 'Q') {
      ch = getchar();
    }
    if (ch == 'A') {
      ++n;
      int a;
      read(a);
      sum ^= a;
      insert(rot[n] = rot[n - 1], sum, 23);
    } else {
      int l, r, x;
      read(l), read(r), read(x);
      if (l == r && l == 1) {
        write(sum ^ x), EL;
        continue;
      }
      --l, --r;
      write(query(rot[max(l - 1, 0)], rot[r], sum ^ x, 23)), EL;
    }
  }
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

void insert(int &x, int num, int dep) {
  trie[++tot].ch[0] = trie[x].ch[0];
  trie[tot].ch[1] = trie[x].ch[1];
  trie[tot].val = trie[x].val + 1;
  x = tot;
  if (!(~dep)) {
    return;
  }
  insert(trie[x].ch[(num >> dep) & 1], num, dep - 1);
}
int query(int lx, int rx, int num, int dep) {
  if (!(~dep)) {
    return 0;
  }
  bool now = ((num >> dep) & 1);
  int sum = trie[trie[rx].ch[now ^ 1]].val - trie[trie[lx].ch[now ^ 1]].val;
  if (sum) {
    return query(trie[lx].ch[now ^ 1], trie[rx].ch[now ^ 1], num, dep - 1) + (1 << dep);
  } else {
    return query(trie[lx].ch[now], trie[rx].ch[now], num, dep - 1);
  }
}
