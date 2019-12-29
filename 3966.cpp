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
const int N = 1000005;
const int M = 205;

class ACA {
public:
  int to[N][26];
  int fail[N];
  int end[N];
  int sum[N];
  int cnt;
  int insert(const std::string &);
  void build();
  void query(const std::string &);
} aca;
int hed[N], nxt[N], to[N], id;
void add(int, int);
void add(int);
void getans(int);

char ch[N];
std::string str[M];
int sum[N];
int ans[N];
int n;

int main () {
  read(n);
  for (int i = 1; i <= n; ++i) {
    scanf("%s", ch);
    str[i] = std::string(ch);
    ans[i] = aca.insert(str[i]);
  }
  aca.build();
  for (int i = 1; i <= n; ++i) {
    aca.query(str[i]);
  }
  getans(0);
  for (int i = 1; i <= n; ++i) {
    write(sum[ans[i]]), EL;
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

int ACA::insert(const std::string &ch) {
  int n = ch.size();
  int now = 0;
  for (int i = 0; i < n; ++i) {
    int &v = to[now][ch[i] - 'a'];
    now = (v ? v : (v = ++cnt));
  }
  ++end[now];
  return now;
}
void ACA::build() {
  std::queue<int> q;
  for (int i = 0; i < 26; ++i) {
    if (to[0][i]) {
      q.push(to[0][i]);
    }
  }
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int i = 0; i < 26; ++i) {
      int &v = to[u][i];
      if (v) {
        fail[v] = to[fail[u]][i];
        q.push(v);
      } else {
        v = to[fail[u]][i];
      }
    }
  }
  for (int i = 1; i <= cnt; ++i) {
    add(fail[i], i);
  }
}
void ACA::query(const std::string &ch) {
  int n = ch.size();
  int now = 0;
  for (int i = 0; i < n; ++i) {
    now = to[now][ch[i] - 'a'];
    add(now);
  }
}
void add(int u, int v) {
  nxt[++id] = hed[u];
  hed[u] = id;
  to[id] = v;
}
void add(int u) {
  ++sum[u];
}
void getans(int u) {
  for (int i = hed[u]; i; i = nxt[i]) {
    getans(to[i]);
    sum[u] += sum[to[i]];
  }
}
