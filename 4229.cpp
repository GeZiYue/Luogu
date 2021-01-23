#include <bits/stdc++.h>

#define isNum(a) (a >= '0' && a <= '9')
#define SP putchar(' ')
#define EL putchar('\n')
#define File(a) freopen(a ".in", "r", stdin), freopen(a ".out", "w", stdout)

template <typename T>
void read(T &);
template <typename T>
void write(const T &);

typedef unsigned uint;
typedef long long ll;
typedef unsigned long long ull;
typedef std::pair<int, int> pii;
const int iinf = 2147483647;
const ll llinf = 9223372036854775807ll;

constexpr int N = 1005;
constexpr int Mod = 998244353;

int pow(int a, int b, int m);

class Lim {
 public:
  int l, r, a;
} Q[N];

int minn[N];
int dp[N][N];
int n, q, A;

int main() {
  int T;
  read(T);
  while (T--) {
    read(n), read(q), read(A);
    std::vector<int> V, C;
    V.push_back(1), V.push_back(n + 1);
    for (int i = 1; i <= q; ++i) {
      read(Q[i].l), read(Q[i].r), read(Q[i].a);
      ++Q[i].r;
      V.push_back(Q[i].l), V.push_back(Q[i].r);
      C.push_back(Q[i].a);
    }
    std::sort(V.begin(), V.end());
    V.erase(std::unique(V.begin(), V.end()), V.end());
    std::sort(C.begin(), C.end());
    C.erase(std::unique(C.begin(), C.end()), C.end());
    int tot = V.size();
    for (int i = 1; i < tot; ++i) {
      minn[i] = A + 1;
      for (int j = 1; j <= q; ++j) {
        if (Q[j].l <= V[i - 1] && V[i - 1] < Q[j].r) {
          minn[i] = std::min(minn[i], Q[j].a);
        }
      }
    }
    auto work = [&](int a) -> int {
      int cnt = 0;
      std::vector<int> st(1), len(1), las(1);
      for (int i = 1; i < tot; ++i) {
        if (minn[i] == a) {
          ++cnt;
          st.push_back(V[i - 1]);
          len.push_back(V[i] - V[i - 1]);
          las.push_back(0);
        }
      }
      for (int i = 1; i <= q; ++i) {
        if (Q[i].a == a) {
          int l = -1, r = -2;
          for (int j = 1; j <= cnt; ++j) {
            if (st[j] >= Q[i].l) {
              if (l == -1) {
                l = j;
              }
            }
            if (st[j] < Q[i].r) {
              r = j;
            }
          }
          if (r < l) {
            return 0;
          }
          las[r] = std::max(las[r], l);
        }
      }
      for (int i = 0; i <= cnt; ++i) {
        for (int j = 0; j <= cnt; ++j) {
          dp[i][j] = 0;
        }
      }
      dp[0][0] = 1;
      for (int i = 1; i <= cnt; ++i) {
        int k1 = pow(a, len[i], Mod), k2 = pow(a - 1, len[i], Mod);
        for (int j = i - 1; j >= las[i]; --j) {
          dp[i][j] = 1ll * dp[i - 1][j] * k2 % Mod;
        }
        for (int j = i - 1; j >= 0; --j) {
          dp[i][i] = (dp[i][i] + 1ll * dp[i - 1][j] * (k1 - k2 + Mod)) % Mod;
        }
      }
      int ans = 0;
      for (int i = 0; i <= cnt; ++i) {
        ans = (ans + dp[cnt][i]) % Mod;
      }
      return ans;
    };
    int ans = 1;
    for (int a : C) {
      ans = 1ll * ans * work(a) % Mod;
    }
    for (int i = 1; i < tot; ++i) {
      if (minn[i] == A + 1) {
        ans = 1ll * ans * pow(A, V[i] - V[i - 1], Mod) % Mod;
      }
    }
    write(ans), EL;
  }
  return 0;
}

int pow(int a, int b, int m) {
  int ans = 1, now = a;
  while (b) {
    if (b & 1) {
      ans = 1ll * now * ans % m;
    }
    now = 1ll * now * now % m;
    b >>= 1;
  }
  return ans;
}

template <typename T>
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
template <typename T>
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
