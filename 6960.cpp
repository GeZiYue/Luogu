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

constexpr int N = 10005;

bool query(int x, int y);
void print();

int res[N];
std::vector<std::tuple<int, int, std::vector<int> > > V;
int num[N];
int n;

int main() {
  read(n);
  if (!(n & 1)) {
    V.emplace_back(1, n + 1, []() -> std::vector<int> {
      std::vector<int> now;
      for (int i = n / 2 + 1; i <= n + 1; ++i) {
        now.push_back(i);
      }
      return now;
    }());
  } else {
    V.emplace_back(1, n, []() -> std::vector<int> {
      std::vector<int> now;
      for (int i = n / 2 + 1; i <= n; ++i) {
        now.push_back(i);
      }
      return now;
    }());
  }
  for (int i = 1; i <= n / 2; ++i) {
    num[i] = i;
  }
  std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
  std::shuffle(num + 1, num + n / 2 + 1, rnd);
  for (int i = 1; i <= n / 2; ++i) {
    int now = num[i];
    int l, r;
    l = 0, r = V.size() - 1;
    int ans = 0;
    while (l <= r) {
      int mid = (l + r) >> 1;
      if (!query(now, *std::get<2>(V[mid]).begin())) {
        ans = mid;
        l = mid + 1;
      } else {
        r = mid - 1;
      }
    }
    if (ans != int(V.size()) - 1) {
      bool flag = false;
      for (int i : std::get<2>(V[ans + 1])) {
        if (!query(now, i)) {
          flag = true;
          break;
        }
      }
      if (flag) {
        ++ans;
      }
    }
    int num = 0;
    std::vector<int> L1, L2;
    for (int i : std::get<2>(V[ans])) {
      if (query(now, i)) {
        L2.push_back(i);
      } else {
        ++num;
        L1.push_back(i);
      }
    }
    num = std::get<0>(V[ans]) + num * 2 - 1;
    int L = std::get<0>(V[ans]), R = std::get<1>(V[ans]);
    V.erase(V.begin() + ans);
    V.emplace(V.begin() + ans, num + 1, R, L2);
    V.emplace(V.begin() + ans, L, num - 1, L1);
    res[now] = num;
  }
  for (auto i : V) {
    res[*std::get<2>(i).begin()] = std::get<0>(i);
  }
  print();
  return 0;
}

bool query(int x, int y) {
  if (y == n + 1) {
    return true;
  }
  putchar('?'), SP, write(x), SP, write(y - n / 2), EL, fflush(stdout);
  char ch = getchar();
  while (ch != '<' && ch != '>') {
    ch = getchar();
  }
  return ch == '<';
}
void print() {
  putchar('!'), SP;
  for (int i = 1; i <= n; ++i) {
    write(res[i]), SP;
  }
  EL, fflush(stdout);
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
