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
using std::string;

const int Mod = 998244353;

class Dfun {
public:
    int f, df;
    Dfun(ci f = 0, ci df = 0) : f(f), df(df) {}
    friend Dfun operator+(const Dfun &, const Dfun &);
    friend Dfun operator*(const Dfun &, const Dfun &);
    friend Dfun operator^(const Dfun &, int);
};

int pow(int, int);
Dfun work(int);

string str;

int main () {
    int t;
    read(t);
    while (t--) {
        string str1;
        std::cin >> str1;
        const int n = str1.size();
        str.clear();
        std::stack<char> sta;
        while (!sta.empty()) {
            sta.pop();
        }
        for (int i = 0; i < n; ++i) {
            // putchar(str1[i]), EL;
            if (str1[i] == 'x' || isNum(str1[i])) {
                str.push_back(str1[i]);
            } else {
                if (str1[i] == '(') {
                    sta.push('(');
                } else {
                    if (str1[i] == ')') {
                        putchar('t'), SP, write(i), EL;
                        while (sta.top() != '(') {
                            write(111), SP, putchar(sta.top()), EL;
                            str.push_back(sta.top());
                            sta.pop();
                        }
                        sta.pop();
                    } else {
                        if (str1[i] == '+') {
                            while (!sta.empty() && sta.top() != '+') {
                                str.push_back(sta.top());
                                sta.pop();
                            }
                            sta.push('+');
                        } else {
                            if (str1[i] == '*') {
                                while (!sta.empty() && (sta.top() == '^' || sta.top() == '(')) {
                                    str.push_back(sta.top());
                                    sta.pop();
                                }
                                sta.push('*');
                            } else {
                                while (!sta.empty() && sta.top() == '(') {
                                    str.push_back(sta.top());
                                    sta.pop();
                                }
                                sta.push('^');
                            }
                        }
                    }
                }
            }
        }
        while (!sta.empty()) {
            str.push_back(sta.top());
            sta.pop();
        }
        // std::cout << str << std::endl;
        int a1, a2;
        read(a1), read(a2);
        write(work(a1).df), SP, write(work(a2).df), EL;
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

Dfun operator+(const Dfun &i, const Dfun &j) {
    return Dfun((i.f + j.f) % Mod, (i.df + j.df) % Mod);
}
Dfun operator*(const Dfun &i, const Dfun &j) {
    return Dfun(i.f * 1ll * j.f % Mod,
        (i.f * 1ll * j.df % Mod + i.df * 1ll *j.f % Mod) % Mod);
}
Dfun operator^(const Dfun &i, int j) {
    Dfun ans(1, 0), now(i);
    while (j) {
        if (j & 1) {
            ans = ans * now;
        }
        now = now * now;
        j >>= 1;
    }
    return ans;
}

Dfun work(int x) {
    int n = str.size();
    std::stack<Dfun> sta;
    int num = -1;
    for (int i = 0; i < n; ++i) {
        if (str[i] == 'x') {
            sta.push(Dfun(x, 1));
        } else {
            if (isNum(str[i])) {
                if (num == -1) {
                    num = 0;
                }
                num = num * 10 + str[i] - '0';
            } else {
                if (num != -1) {
                    sta.push(Dfun(num));
                    num = -1;
                }
                if (str[i] == '+') {
                    Dfun tmp = sta.top();
                    sta.pop();
                    tmp = tmp + sta.top();
                    sta.pop();
                    sta.push(tmp);
                } else {
                    if (str[i] == '*') {
                        Dfun tmp = sta.top();
                        sta.pop();
                        tmp = tmp * sta.top();
                        sta.pop();
                        sta.push(tmp);
                    } else {
                        int tmp = sta.top().f;
                        sta.pop();
                        Dfun ans = sta.top() ^ tmp;
                        sta.pop();
                        sta.push(ans);
                    }
                }
            }
        }
    }
    if (num != -1) {
        sta.push(Dfun(num));
    }
    return sta.top();
}
