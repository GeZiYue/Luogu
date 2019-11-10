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

class Aho_Corasick_automaton {
public:
  void insert(char *);
  void build();
  int query(char *);
private:
  class Node {
  public:
    int fail;
    int end;
    int tr[26];
  };
  Node trie[N];
  int id;
};

Aho_Corasick_automaton aca;
char ch[N];

int main () {
  int n;
  read(n);
  for (int i = 1; i <= n; ++i) {
    scanf("%s", ch);
    aca.insert(ch);
  }
  aca.build();
  scanf("%s", ch);
  write(aca.query(ch)), EL;
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

void Aho_Corasick_automaton::insert(char *ch) {
  int n = strlen(ch);
  int now = 0;
  for (int i = 0; i < n; ++i) {
    now = (trie[now].tr[ch[i] - 'a'] ? trie[now].tr[ch[i] - 'a'] : (trie[now].tr[ch[i] - 'a'] = ++id));
  }
  ++trie[now].end;
}
void Aho_Corasick_automaton::build() {
  std::queue<int> q;
  for (int i = 0; i < 26; ++i) {
    if (trie[0].tr[i]) {
      trie[trie[0].tr[i]].fail = 0;
      q.push(trie[0].tr[i]);
    }
  }
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int i = 0; i < 26; ++i) {
      if (trie[u].tr[i]) {
        trie[trie[u].tr[i]].fail = trie[trie[u].fail].tr[i];
        q.push(trie[u].tr[i]);
      } else {
        trie[u].tr[i] = trie[trie[u].fail].tr[i];
      }
    }
  }
}
int Aho_Corasick_automaton::query(char *ch) {
  int n = strlen(ch);
  int now = 0;
  int ans = 0;
  for (int i = 0; i < n; ++i) {
    now = trie[now].tr[ch[i] - 'a'];
    for (int j = now; j && (~trie[j].end); j = trie[j].fail) {
      ans += trie[j].end;
      trie[j].end = -1;
    }
  }
  return ans;
}
