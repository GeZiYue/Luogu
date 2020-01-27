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
const int inf = 100000000;

class Suffix_tree {
public:
  int s[N];
  int to[N << 1][27], lnk[N << 1], sta[N << 1], len[N << 1], tot;
  int cnt[N << 1];
  int n, now, rem;
  Suffix_tree() : n(0), tot(1), now(1), rem(0) { len[0] = iinf; }
  int newnode(int, int);
  void extend(int);
  void query(int, int);
} st;

int n;
char ch[N];
ll ans;

int main () {
  scanf("%s", ch + 1);
  n = strlen(ch + 1);
  for (int i = 1; i <= n; ++i) {
    st.extend(ch[i] - 'a');
  }
  st.extend(26);
  st.query(1, 0);
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

int Suffix_tree::newnode(int st, int ln) {
  lnk[++tot] = 1;
  sta[tot] = st;
  len[tot] = ln;
  return tot;
}
void Suffix_tree::extend(int x) {
  s[++n] = x, ++rem;
  for (int las = 1; rem; ) {
    while (rem > len[to[now][s[n - rem + 1]]]) {
      rem -= len[now = to[now][s[n - rem + 1]]];
    }
    int &v = to[now][s[n - rem + 1]], c = s[sta[v] + rem - 1];
    if (!v || x == c) {
      lnk[las] = now;
      las = now;
      if (!v) {
        v = newnode(n - rem + 1, inf);
      } else {
        break;
      }
    } else {
      int u = newnode(sta[v], rem - 1);
      to[u][c] = v, to[u][x] = newnode(n, inf);
      sta[v] += rem - 1;
      len[v] -= rem - 1;
      lnk[las] = v = u;
      las = u;
    }
    if (now == 1) {
      --rem;
    } else {
      now = lnk[now];
    }
  }
}
void Suffix_tree::query(int x, int ln) {
  if (ln >= inf) {
    ++cnt[x];
    return;
  }
  for (int i = 0; i <= 26; ++i) {
    if (to[x][i]) {
      query(to[x][i], ln + len[to[x][i]]);
      cnt[x] += cnt[to[x][i]];
    }
  }
  if (cnt[x] > 1) {
    ans = max(ans, ln * 1ll * cnt[x]);
  }
}
