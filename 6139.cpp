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

class WSAM {
public:
  class TrieNode {
  public:
    int to[26];
  };
  TrieNode tre[N];
  int Ttot;
  class Node {
  public:
    int len, lnk;
    int to[26];
  };
  Node sta[N << 1];
  int tot;
  void insert(char *ch);
  int insert(int, int);
  void build();
};

WSAM S;
char ch[N];

int main () {
  int n;
  read(n);
  for (int i = 1; i <= n; ++i) {
    scanf("%s", ch);
    S.insert(ch);
  }
  S.build();
  ll ans = 0;
  for (int i = 2; i <= S.tot; ++i) {
    ans += S.sta[i].len - S.sta[S.sta[i].lnk].len;
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

void WSAM::insert(char *ch) {
  int len = strlen(ch);
  int now = 0;
  for (int i = 0; i < len; ++i) {
    int &tmp = tre[now].to[ch[i] - 'a'];
    if (!tmp) {
      tmp = ++Ttot;
    }
    now = tmp;
  }
}
int WSAM::insert(int x, int las) {
  int now = ++tot;
  sta[now].len = sta[las].len + 1;
  int p = las;
  while (p && !sta[p].to[x]) {
    sta[p].to[x] = now;
    p = sta[p].lnk;
  }
  int q = sta[p].to[x];
  if (!p) {
    sta[now].lnk = 1;
    return now;
  }
  if (sta[p].len + 1 == sta[q].len) {
    sta[now].lnk = q;
  } else {
    int cur = ++tot;
    sta[cur].lnk = sta[q].lnk;
    sta[cur].len = sta[p].len + 1;
    for (int i = 0; i < 26; ++i) {
      sta[cur].to[i] = sta[q].to[i];
    }
    while (p && sta[p].to[x] == q) {
      sta[p].to[x] = cur;
      p = sta[p].lnk;
    }
    sta[now].lnk = sta[q].lnk = cur;
  }
  return now;
}
void WSAM::build() {
  std::queue<pii> q;
  tot = 1;
  q.push(pii(0, 1));
  while (!q.empty()) {
    int u = q.front().first, l = q.front().second;
    q.pop();
    for (int i = 0; i < 26; ++i) {
      int v = tre[u].to[i];
      if (v) {
        q.push(pii(v, insert(i, l)));
      }
    }
  }
}
