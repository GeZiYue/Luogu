#include <iostream>
#include <cstdio>
#include <cmath>
#include <string>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>

#define isNum(a) (a >= '0' && a <= '9')
#define SP putchar(' ')
#define EL putchar('\n')
#define File(a) freopen(a ".in", "r", stdin), freopen(a ".out", "w", stdout)

template<class T>
inline void read(T&);
template<class T>
inline void write(const T&);

typedef long long ll;
typedef unsigned long long ull;
typedef const int& ci;
typedef std::pair<int, int> pii;
const int iinf = 2147483647;
const ll llinf = 9223372036854775807ll;
using std::min;
using std::max;
using std::abs;
using std::sort;
const int N = 100005;
const int M = 35;
const unsigned Base = 233333;

int a[N];
int sum[N][M];
int k[N][M];
std::map <ull, int> mp;

int main () {
    int n, m;
    read(n), read(m);
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        read(a[i]);
        ull now = 0;
        for (int j = 1; j <= m; ++j) {
            sum[i][j] = sum[i - 1][j] + ((a[i] >> (j - 1)) & 1);
            k[i][j] = sum[i][j] - sum[i][1];
            now = now * Base + (k[i][j] + Base) % Base;
        }
        if (mp[now] || now == 0) {
            ans = max(ans, i - mp[now]);
        } else {
            mp[now] = i;
        }
    }
    write(ans), EL;
    return 0;
}

template<class T>
void read(T &Re) {
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
void write(const T &Wr) {
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
