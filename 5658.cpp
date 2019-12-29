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
const int M = 500005;

void add(int, int);
void dfs(int);

ll k[N];
int s[N];
int fa[N];
char ch[N];
int hed[N], nxt[M], to[M], id;
std::stack<int> st;
int n;
ll ans;

int main () {
  read(n);
  scanf("%s", ch + 1);
  for (int i = 2; i <= n; ++i) {
    read(fa[i]);
    add(fa[i], i);
  }
  dfs(1);
  for (int i = 1; i <= n; ++i) {
    ans ^= (k[i] * i);
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

void add(int u, int v) {
  nxt[++id] = hed[u];
  hed[u] = id;
  to[id] = v;
}
void dfs(int u) {
  int tmp = 0;
  k[u] = k[fa[u]];
  if (ch[u] == '(') {
    st.push(u);
    s[u] = 0;
  } else {
    if (st.empty()) {
      s[u] = 0;
    } else {
      tmp = st.top();
      st.pop();
      k[u] += (s[u] = 1 + s[fa[tmp]]);
    }
  }
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    dfs(v);
  }
  if (ch[u] == '(') {
    st.pop();
  }
  if (tmp) {
    st.push(tmp);
  }
}
