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

const int N = 100005;

class Wide_Suffix_Automaton {
private:
  class Node {
  public:
    int to[26];
    int len, lnk;
  };
  Node sta[N << 1];
  int las, siz;
  int col[N << 1];
  void update(int, int);
public:
  Wide_Suffix_Automaton() { sta[0].lnk = -1; }
  void extend(int);
  void endl();
  friend void solve();
};

void solve();

Wide_Suffix_Automaton wsam;
int len[N];
std::string ch[N];
char tmp[N];
int ans[N];
int n;

int main () {
  read(n);
  for (int i = 1; i <= n; ++i) {
    scanf("%s", tmp);
    ch[i] = std::string(tmp);
    len[i] = strlen(tmp);
    for (int j = 0; j < len[i]; ++j) {
      wsam.extend(tmp[j] - 'a');
    }
    wsam.endl();
  }
  solve();
  for (int i = 1; i <= n; ++i) {
    write(ans[i]), EL;
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

void Wide_Suffix_Automaton::extend(int c) {
  int cur = ++siz;
  sta[cur].len = sta[las].len + 1;
  int p = las;
  while (~p && !sta[p].to[c]) {
    sta[p].to[c] = cur;
    p = sta[p].lnk;
  }
  if (~p) {
    int q = sta[p].to[c];
    if (sta[q].len == sta[p].len + 1) {
      sta[cur].lnk = q;
    } else {
      int cl = ++siz;
      sta[cl].len = sta[p].len + 1;
      sta[cl].lnk = sta[q].lnk;
      memcpy(sta[cl].to, sta[q].to, sizeof(sta[q].to));
      while (~p && sta[p].to[c] == q) {
        sta[p].to[c] = cl;
        p = sta[p].lnk;
      }
      sta[cur].lnk = sta[q].lnk = cl;
    }
  } else {
    sta[cur].lnk = 0;
  }
  las = cur;
}
void Wide_Suffix_Automaton::endl() {
  las = 0;
}
void Wide_Suffix_Automaton::update(int x, int i) {
  while (x && col[x] != -1 && col[x] != i) {
    if (col[x]) {
      col[x] = -1;
    } else {
      col[x] = i;
    }
    x = sta[x].lnk;
  }
}
void solve() {
  for (int i = 1; i <= n; ++i) {
    for (int j = 0, x = 0; j < len[i]; ++j) {
      wsam.update(x = wsam.sta[x].to[ch[i][j] - 'a'], i);
    }
  }
  for (int i = 1; i <= wsam.siz; ++i) {
    if (~wsam.col[i]) {
      ans[wsam.col[i]] += wsam.sta[i].len - wsam.sta[wsam.sta[i].lnk].len;
    }
  }
}
