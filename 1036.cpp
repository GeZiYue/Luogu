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
typedef const long long & cll;
typedef const int & ci;
typedef std::pair<int, int> pii;
const int iinf = 2147483647;
const ll llinf = 9223372036854775807ll;
using std::min;
using std::max;
using std::abs;
using std::sort;
const int N = 25;

void pri(int);
bool isp(int);
void dfs();

int p[1005], id;
bool ip[1005];
int now, sum, res;
int ans;
int n, k;
int a[N];

int main () {
    pri(1000);
    read(n), read(k);
    res = k;
    for (int i = 1; i <= n; ++i) {
        read(a[i]);
    }
    dfs();
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

void pri(int n) {
    for (int i = 2; i <= n; ++i) {
        if (!ip[i]) {
            p[++id] = i;
        }
        for (int j = 1; j <= id && p[j] * i <= n; ++j) {
            ip[p[j] * i] = true;
            if (i % p[j] == 0) {
                break;
            }
        }
    }
}
bool isp(int x) {
    for (int i = 1; i <= id && p[i] * p[i] <= x; ++i) {
        if (x % p[i] == 0) {
            return false;
        }
    }
    return true;
}
void dfs() {
    if (!res) {
        if (isp(sum)) {
            ++ans;
        }
        return;
    }
    for (int i = now + 1; i <= n - res + 1; ++i) {
        now = i;
        --res;
        sum += a[i];
        dfs();
        sum -= a[i];
        ++res;
    }
}
