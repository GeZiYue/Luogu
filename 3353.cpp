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
const int N = 200005;

void update(int, int);
int query(int);

int BIT[N];
int x[N];

int main () {
    int n, l;
    read(n), read(l);
    for (int i = 1; i <= n; ++i) {
        int s;
        read(x[i]), read(s);
        update(x[i], s);
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        ans = max(ans, query(x[i] + l - 1) - query(x[i] - 1));
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

void update(int x, int num) {
    while (x <= 200000) {
        BIT[x] += num;
        x += x & -x;
    }
}
int query(int x) {
    int ans = 0;
    while (x) {
        ans += BIT[x];
        x -= x & -x;
    }
    return ans;
}
