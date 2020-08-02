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

const int N = 200005;
const int M = 2000005;

namespace ACAM {
  class Node {
  public:
    int to[26];
    int fail;
    int sum;
  };
  Node sta[N];
  int tot = 1;
  int end[N], num;
  int hed[N], nxt[N], to[N], id;
  void insert(char *);
  void add(int, int);
  void build();
  void match(char *);
  void dfs(int);
  int query(int);
}

char ch[M];

int main () {
  int n;
  read(n);
  for (int i = 1; i <= n; ++i) {
    scanf("%s", ch);
    ACAM::insert(ch);
  }
  ACAM::build();
  scanf("%s", ch);
  ACAM::match(ch);
  ACAM::dfs(1);
  for (int i = 1; i <= n; ++i) {
    write(ACAM::query(i)), EL;
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

void ACAM::insert(char *s) {
  int len = strlen(s);
  int now = 1;
  for (int i = 0; i < len; ++i) {
    int &v = sta[now].to[s[i] - 'a'];
    now = v ? v : v = ++tot;
  }
  end[++num] = now;
}
void ACAM::add(int u, int v) {
  nxt[++id] = hed[u];
  hed[u] = id;
  to[id] = v;
}
void ACAM::build() {
  std::queue<int> q;
  for (int i = 0; i < 26; ++i) {
    if (sta[1].to[i]) {
      sta[sta[1].to[i]].fail = 1;
      q.push(sta[1].to[i]);
    } else {
      sta[1].to[i] = 1;
    }
  }
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    add(sta[u].fail, u);
    for (int i = 0; i < 26; ++i) {
      int &v = sta[u].to[i];
      if (v) {
        sta[v].fail = sta[sta[u].fail].to[i];
        q.push(v);
      } else {
        v = sta[sta[u].fail].to[i];
      }
    }
  }
}
void ACAM::match(char *s) {
  int len = strlen(s);
  int now = 1;
  for (int i = 0; i < len; ++i) {
    now = sta[now].to[s[i] - 'a'];
    ++sta[now].sum;
  }
}
void ACAM::dfs(int u) {
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    dfs(v);
    sta[u].sum += sta[v].sum;
  }
}
int ACAM::query(int i) {
  return sta[end[i]].sum;
}
