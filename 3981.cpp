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

constexpr int N = 4;
constexpr int Mod = 20171111;

class Matrix {
 public:
  int a[N][N];
  Matrix() {
    for (int i = 1; i <= 3; ++i) {
      for (int j = 1; j <= 3; ++j) {
        a[i][j] = 0;
      }
    }
  }
  friend Matrix operator*(Matrix a, Matrix b);
  friend Matrix operator^(Matrix a, ll k);
};

Matrix tran, st;
ll a, b, c;

int main() {
  tran.a[1][1] = tran.a[1][2] = tran.a[1][3] = tran.a[2][1] = tran.a[3][3] = 1;
  st.a[1][1] = st.a[3][1] = 1;
  read(a), read(b), read(c);
  int ans = (a == c);
  if (c == 3) {
    ans += (b > 3);
  } else {
    if (c == 5) {
      if (b > 5) {
        ans += ((tran ^ ((b - 4) >> 1)) * st).a[2][1];
      }
    } else {
      if (c == 7) {
        if (b > 7) {
          ans += ((tran ^ ((b - 6) >> 1)) * st).a[2][1];
        }
      }
    }
  }
  write(ans), EL;
  return 0;
}

Matrix operator*(Matrix a, Matrix b) {
  Matrix ans;
  for (int i = 1; i <= 3; ++i) {
    for (int k = 1; k <= 3; ++k) {
      for (int j = 1; j <= 3; ++j) {
        ans.a[i][j] = (ans.a[i][j] + 1ll * a.a[i][k] * b.a[k][j]) % Mod;
      }
    }
  }
  return ans;
}
Matrix operator^(Matrix a, ll k) {
  Matrix ans, now = a;
  for (int i = 1; i <= 3; ++i) {
    ans.a[i][i] = 1;
  }
  while (k) {
    if (k & 1) {
      ans = ans * now;
    }
    now = now * now;
    k >>= 1;
  }
  return ans;
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
