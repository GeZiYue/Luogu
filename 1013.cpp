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
const int N = 15;

std::string s[N][N];
std::map<char, int> mp;

char mt[N];

int main () {
    int n;
    read(n);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            std::cin >> s[i][j];
            if (s[i][j].size() > 2 || ((i == 1 || j == 1) && s[i][j].size() > 1)) {
                puts("ERROR!");
                return 0;
            }
        }
    }
    for (int i = 2; i <= n; ++i) {
        int num = 0;
        for (int j = 2; j <= n; ++j) {
            num += s[i][j].size() - 1;
        }
        mp[s[i][1][0]] = num;
    }
    for (int i = 2; i <= n; ++i) {
        int num = 0;
        for (int j = 2; j <= n; ++j) {
            num += s[j][i].size() - 1;
        }
        if (mp[s[1][i][0]] ^ num) {
            puts("ERROR!");
            return 0;
        }
    }
    for (int i = 2; i <= n; ++i) {
        if (mt[mp[s[1][i][0]]]) {
            puts("ERROR!");
            return 0;
        }
        mt[mp[s[1][i][0]]] = s[1][i][0];
    }
    for (int i = 2; i <= n; ++i) {
        for (int j = 2; j <= n; ++j) {
            int a = mp[s[i][1][0]], b = mp[s[1][j][0]], c = mp[s[i][j][0]];
            if (s[i][j].size() > 1) {
                c = mp[s[i][j][1]];
                if (s[i][j][0] != mt[1]) {
                    puts("ERROR!");
                    return 0;
                }
            }
            if ((a + b) % (n - 1) != c) {
                puts("ERROR!");
                return 0;
            }
        }
    }
    for (int i = 2; i <= n; ++i) {
        putchar(s[1][i][0]),
        putchar('='),
        write(mp[s[1][i][0]]),
        SP;
    }
    EL;
    write(n - 1),
    EL;
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
