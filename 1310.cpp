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
const int N = 200005;
const int Mod = 10007;

void add();
void mul();

char str[N];
int id;
std::stack<int> st1;
std::stack<pii> st2;

int main () {
	int n;
	read(n);
	for (int i = 1; i <= n; ++i) {
		char ch = getchar();
		if (((ch == '+' || ch == '*') && str[id] != ')') || (ch == ')' && (str[id] == '+' || str[id] == '*'))) {
			str[++id] = '1';
		}
		str[++id] = ch;
	}
	if (str[id] != ')') {
		str[++id] = '1';
	}
	for (int i = 1; i <= id; ++i) {
		if (str[i] == '1') {
			st2.push(pii(1, 1));
		} else {
			if (str[i] == '(') {
				st1.push(-1);
			} else {
				if (str[i] == ')') {
					while (~st1.top()) {
						if (st1.top()) {
							mul();
						} else {
							add();
						}
						st1.pop();
					}
					st1.pop();
				} else {
					if (str[i] == '+') {
						while (!st1.empty() && st1.top() > 0) {
							mul();
							st1.pop();
						}
						st1.push(0);
					} else {
						st1.push(1);
					}
				}
			}
		}
	}
	while (!st1.empty()) {
		if (st1.top()) {
			mul();
		} else {
			add();
		}
		st1.pop();
	}
	write(st2.top().first), EL;
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

void add() {
	pii x = st2.top();
	st2.pop();
	pii y = st2.top();
	st2.pop();
	st2.push(pii(
	    x.first * y.first % Mod,
	    (x.first * y.second % Mod +
	    x.second * y.first % Mod +
	    x.second * y.second % Mod) % Mod
	));
}
void mul() {
	pii x = st2.top();
	st2.pop();
	pii y = st2.top();
	st2.pop();
	st2.push(pii(
	    (x.first * y.first % Mod +
	    x.first * y.second % Mod +
	    x.second * y.first % Mod) % Mod,
	    x.second * y.second % Mod
	));
}
