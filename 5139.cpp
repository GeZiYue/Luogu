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

class quadratic_function {
private:
    double a, h, l;
public:
    quadratic_function(double a, double b, double c): a(a), h(-b / (2.0 * a)), l(c - b * b / (4.0 * a)){}
    double operator ()(double x) {
        return a * (x - h) * (x - h) + l;
    }
    void move_up(double k) {
        l += k;
    }
    void move_right(double k) {
        h += k;
    }
    void symmetry(double x, double y) {
        a *= -1.0;
        h = 2.0 * x - h;
        l = 2.0 * y - l;
    }
    std::pair<double, double> min_and_max(double k1, double k2) {
        if (k1 <= h && k2 >= h) {
            if (a < 0) {
                return std::pair<double, double>(min((*this)(k1), (*this)(k2)), l);
            } else {
                return std::pair<double, double>(l, max((*this)(k1), (*this)(k2)));
            }
        } else {
            double mn = min((*this)(k1), (*this)(k2)), mx = max((*this)(k1), (*this)(k2));
            return std::pair<double, double>(mn, mx);
        }
    }
    bool cross(double x, double y, double z) {
        double ta = a - x, tb = -2.0 * a * h - y, tc = a * h * h + l - z;
        return tb * tb - 4.0 * ta * tc >= 0;
    }
    double fin() {
        return l;
    }
};

int main () {
    int t;
    read(t);
    while (t--) {
        double a, b, c;
        std::cin >> a >> b >> c;
        quadratic_function f(a, b, c);
        std::cout.precision(2);
        int m;
        read(m);
        for (int i = 1; i <= m; ++i) {
            int mod;
            read(mod);
            if (mod <= 2) {
                double k;
                std::cin >> k;
                if (mod == 1) {
                    f.move_up(k);
                } else {
                    f.move_right(k);
                }
            } else {
                if (mod <= 4) {
                    double k1, k2;
                    std::cin >> k1 >> k2;
                    if (mod == 3) {
                        f.symmetry(k1, k2);
                    } else {
                        std::pair<double, double> ans = f.min_and_max(k1, k2);
                        std::cout << std::fixed << ans.first << ' ' << ans.second << std::endl;
                    }
                } else {
                    double x, y, z;
                    std::cin >> x >> y >> z;
                    write(f.cross(x, y, z) ? 2 : 0), EL;
                }
            }
        }
        std::cout << f.fin() << std::endl;
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
