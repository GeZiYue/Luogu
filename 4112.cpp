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

const int N = 2005;

class Suffix_Automaton {
private:
  class Node {
  public:
    int to[26], len, lnk;
  };
  Node sta[N << 1];
  int las, siz;
public:
  Suffix_Automaton() { sta[0].lnk = -1; }
  void extend(int);
  template<class T1, class T2>
  friend int bfs(T1, T2);
};
class Sequence_Automaton {
private:
  class Node {
  public:
    int to[26];
  };
  Node sta[N];
  int las[26];
  int now;
public:
  void extend(int);
  template<class T1, class T2>
  friend int bfs(T1, T2);
};

Suffix_Automaton SAM1, SAM2;
Sequence_Automaton SeqAM1, SeqAM2;
bool vis[N << 1][N << 1];
char ch1[N], ch2[N];
int n1, n2;

int main () {
  scanf("%s%s", ch1 + 1, ch2 + 1);
  n1 = strlen(ch1 + 1), n2 = strlen(ch2 + 1);
  for (int i = 1; i <= n1; ++i) {
    SAM1.extend(ch1[i] - 'a');
    SeqAM1.extend(ch1[i] - 'a');
  }
  for (int i = 1; i <= n2; ++i) {
    SAM2.extend(ch2[i] - 'a');
    SeqAM2.extend(ch2[i] - 'a');
  }
  write(bfs(SAM1, SAM2)), EL;
  write(bfs(SAM1, SeqAM2)), EL;
  write(bfs(SeqAM1, SAM2)), EL;
  write(bfs(SeqAM1, SeqAM2)), EL;
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

void Suffix_Automaton::extend(int c) {
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
      memcpy(sta[cl].to, sta[q].to, sizeof(int) * 26);
      while (~p && sta[p].to[c] == q) {
        sta[p].to[c] = cl;
        p = sta[p].lnk;
      }
      sta[q].lnk = sta[cur].lnk = cl;
    }
  } else {
    sta[cur].lnk = 0;
  }
  las = cur;
}
void Sequence_Automaton::extend(int c) {
  ++now;
  for (int i = las[c]; i < now; ++i) {
    sta[i].to[c] = now;
  }
  las[c] = now;
}
template<class T1, class T2>
int bfs(T1 am1, T2 am2) {
  class Qn {
  public:
    int p1, p2, len;
    Qn(int p1 = 0, int p2 = 0, int len = 0) : p1(p1), p2(p2), len(len) {}
  };
  memset(vis, false, sizeof(vis));
  std::queue<Qn> q;
  q.push(Qn());
  while (!q.empty()) {
    Qn now = q.front();
    q.pop();
    for (int i = 0; i < 26; ++i) {
      int t1 = am1.sta[now.p1].to[i], t2 = am2.sta[now.p2].to[i];
      if (t1) {
        if (t2) {
          if (!vis[t1][t2]) {
            q.push(Qn(t1, t2, now.len + 1));
            vis[t1][t2] = true;
          }
        } else {
          return now.len + 1;
        }
      }
    }
  }
  return -1;
}
