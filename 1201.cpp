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
const int N = 15;

int ans[N];
std::string str[N];
std::map<std::string, int> mp;

int main () {
    int n;
    read(n);
    for (int i = 1; i <= n; ++i) {
        std::cin >> str[i];
        mp[str[i]] = i;
    }
    for (int i = 1; i <= n; ++i) {
        std::string s;
        std::cin >> s;
        int m, c;
        read(m), read(c);
        if (c == 0) {
            continue;
        }
        int on = m / c;
        ans[mp[s]] -= on * c;
        for (int j = 1; j <= c; ++j) {
            std::cin >> s;
            ans[mp[s]] += on;
        }
    }
    for (int i = 1; i <= n; ++i) {
        std::cout << str[i] << ' ' << ans[i] << std::endl;
    }
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
