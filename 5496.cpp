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
  short s[N];
  class Node {
  public:
    int to[26];
    int len, lnk, cnt;
    Node(int ln = 0, int lk = 0) : len(ln), lnk(lk) {}
  };
  Node sta[N];
  int las, siz, len;
  int find(int);
public:
  Palindrome_Automaton() : las(0), siz(1), len(0) {
    s[0] = 26;
    sta[0] = Node(0, 1), sta[1] = Node(-1);
  }
  int extend(short);
};

Palindrome_Automaton PAM;

char ch[N];

int main () {
  int n;
  scanf("%s", ch);
  n = strlen(ch);
  int las = 0;
  for (int i = 0; i < n; ++i) {
    ch[i] = (ch[i] - 'a' + las) % 26 + 'a';
    las = PAM.extend(ch[i] - 'a');
    write(las), SP;
  }
  EL;
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
int Palindrome_Automaton::extend(short c) {
  s[++len] = c;
  int now = find(las);
  if (!sta[now].to[c]) {
    int cur = ++siz;
    sta[cur].len = sta[now].len + 2;
    sta[cur].lnk = sta[find(sta[now].lnk)].to[c];
    sta[cur].cnt = sta[sta[cur].lnk].cnt + 1;
    sta[now].to[c] = cur;
  }
  las = sta[now].to[c];
  return sta[las].cnt;
}
