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
#define inf 2147483647
#define File(a) freopen(a ".in", "r", stdin), freopen(a ".out", "w", stdout)

template<class T>
inline void read(T&);
template<class T>
inline void write(const T&);

typedef long long ll;
typedef const long long & cll;
typedef const int & ci;

int main () {
    ll l, r;
    read(l), read(r);
    int t;
    read(t);
    while (t--) {
        std::string str;
        std::cin >> str;
        int flag = 1;
        if (str[0] == '-') {
            flag = -1;
            str.erase(0, 1);
        }
        ll num = 0;
        bool beg = true;
        if (str.size() == 0) {
            write(1), EL;
            goto back;
        }
        if (str.size() == 1) {
            num = str[0] - '0';
            if (num == 0 && flag == -1) {
                write(1), EL;
                goto back;
            }
            num *= flag;
            write(num >= l && num <= r ? 0 : 2), EL;
            goto back;
        }
        for (unsigned i = 0; i < str.size(); ++i) {
            if (beg && str[i] == '0') {
                write(1), EL;
                goto back;
            }
            if (str[i] != '0') {
                beg = false;
            }
            if (num * 10 + str[i] - '0' < num) {
                num = -1;
            } else {
                num = num * 10 + str[i] - '0';
            }
        }
        if (num == -1) {
            write(2), EL;
            goto back;
        }
        num *= flag;
        write(num >= l && num <= r ? 0 : 2), EL;
        back:;
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
