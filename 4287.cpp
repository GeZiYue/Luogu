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

class Palindrome_Automaton {
private:
  class Node {
  public:
    int to[26];
    int len, lnk, tran;
    Node(int ln = 0, int lk = 0, int tr = 0) : len(ln), lnk(lk), tran(tr) {
      memset(to, 0, sizeof(to));
    }
  };
  int s[N];
  Node sta[N];
  int len, siz, las;
  int find(int);
public:
  Palindrome_Automaton() : len(0), siz(1), las(0) {
    sta[0] = Node(0, 1), sta[1] = Node(-1);
    s[0] = 26;
  }
  void extend(int);
  int query();
};

Palindrome_Automaton PAM;
char ch[N];

int main () {
  int n;
  read(n);
  scanf("%s", ch);
  for (int i = 0; i < n; ++i) {
    PAM.extend(ch[i] - 'a');
  }
  write(PAM.query()), EL;
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

int Palindrome_Automaton::find(int x) {
  while (s[len - sta[x].len - 1] != s[len]) {
    x = sta[x].lnk;
  }
  return x;
}
void Palindrome_Automaton::extend(int c) {
  s[++len] = c;
  int now = find(las);
  if (!sta[now].to[c]) {
    int cur = ++siz;
    sta[cur].len = sta[now].len + 2;
    sta[cur].lnk = sta[find(sta[now].lnk)].to[c];
    if (sta[cur].len <= 2) {
      sta[cur].tran = sta[cur].lnk;
    } else {
      int x = sta[now].tran;
      while (s[len - sta[x].len - 1] != s[len] || ((sta[x].len + 2) << 1) > sta[cur].len) {
        x = sta[x].lnk;
      }
      sta[cur].tran = sta[x].to[c];
    }
    sta[now].to[c] = cur;
  }
  las = sta[now].to[c];
}
int Palindrome_Automaton::query() {
  int ans = 0;
  for (int i = 2; i <= siz; ++i) {
    if (((sta[sta[i].tran].len << 1) == sta[i].len) && (sta[i].len % 4 == 0)) {
      ans = max(ans, sta[i].len);
    }
  }
  return ans;
}
