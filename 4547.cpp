#include <bits/stdc++.h>

#define isNum(a) (a >= '0' && a <= '9')
#define SP putchar(' ')
#define EL putchar('\n')
#define File(a) freopen(a ".in", "r", stdin), freopen(a ".out", "w", stdout)

template <class T>
void read(T &);
template <class T>
void write(const T &);

typedef unsigned uint;
typedef long long ll;
typedef unsigned long long ull;
typedef std::pair<int, int> pii;
const int iinf = 2147483647;
const ll llinf = 9223372036854775807ll;

constexpr int N = 500;
constexpr int Mod = 1000000007, iv2 = (Mod + 1) / 2, iv4 = (Mod + 1) / 4;

class Edge {
 public:
  uint v;
  int p;
  Edge(uint v = 0, int p = 0) : v(v), p(p) {}
} E[N];

int dp(uint sta);

std::unordered_map<uint, int> mp;
int eid;
int n, m;

int main() {
  read(n), read(m);
  for (int i = 1; i <= m; ++i) {
    int op, a, b;
    read(op), read(a), read(b);
    --a, --b;
    int id1 = (1u << a) | (1u << (b + n));
    E[++eid] = Edge(id1, iv2);
    if (op == 0) {
      continue;
    }
    read(a), read(b);
    --a, --b;
    int id2 = (1u << a) | (1u << (b + n));
    E[++eid] = Edge(id2, iv2);
    if (id1 & id2) {
      continue;
    }
    E[++eid] = Edge(id1 | id2, op == 1 ? iv4 : (Mod - iv4));
  }
  write(dp((1u << (n << 1)) - 1) * 1ll * (1 << n) % Mod), EL;
  return 0;
}

int dp(uint sta) {
  if (!sta) {
    return 1;
  }
  auto it = mp.find(sta);
  if (it != mp.end()) {
    return it->second;
  }
  int res = 0;
  for (int i = 1; i <= eid; ++i) {
    uint id = E[i].v;
    if ((id & sta) == id && (id << 1) > sta) {
      res = (res + E[i].p * 1ll * dp(sta ^ id)) % Mod;
    }
  }
  return mp[sta] = res;
}

template <class T>
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
template <class T>
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
