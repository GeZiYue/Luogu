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
const int N = 1000005;
const int M = 8;

class BigInteger {
private:
    int Int[M];
    int len;
    void AddLen(int k) {
        len += k;
    }
public:
    int& operator[](int);
    BigInteger operator +(BigInteger);
    BigInteger operator *(int);
    BigInteger& operator +=(BigInteger);
    BigInteger& operator *=(int);
    void Write();
    BigInteger() {
        len = 0;
        memset(Int, 0, sizeof(Int));
    }
    BigInteger(int k) {
        len = 0;
        memset(Int, 0, sizeof(Int));
        while (k) {
            Int[++len] = k % 100000000;
            k /= 100000000;
        }
    }
};
template<class T>
class BIT {
private:
    T *tre;
    int n;
public:
    BIT(int k) {
        n = k;
        tre = new T[k + 5];
    }
    void update(int x, T num) {
        while (x <= n) {
            tre[x] += num;
            x += x & (-x);
        }
    }
    T query(int x) {
        T ans(0);
        while (x) {
            ans += tre[x];
            x -= x & (-x);
        }
        return ans;
    }
};

pii a[N];
int s[N];
int main () {
    int n;
    read(n);
    for (int i = 1; i <= n; ++i) {
        read(a[i].first);
        a[i].second = i;
    }
    if (n == 1) {
        write(0), EL;
        return 0;
    }
    sort(a + 1, a + n + 1);
    int now = 1;
    s[a[1].second] = 1;
    for (int i = 2; i <= n; ++i) {
        if (a[i].first == a[i - 1].first) {
            s[a[i].second] = s[a[i - 1].second];
        } else {
            s[a[i].second] = ++now;
        }
    }
    BIT<BigInteger> T(now);
    BigInteger ans(0);
    for (int i = n; i >= 1; --i) {
        ans += T.query(s[i] - 1) * i;
        T.update(s[i], n - i + 1);
    }
    ans.Write(), EL;
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

int& BigInteger::operator[](int k) {
    return Int[k];
}
BigInteger BigInteger::operator +(BigInteger k) {
    BigInteger ans;
    ans.AddLen(max(len, k.len));
    int num = 0;
    for (int i = 1; i <= max(len, k.len); i++) {
        ans[i] = Int[i] + k.Int[i] + num;
        num = ans[i] / 100000000;
        ans[i] %= 100000000;
    }
    if (num) {
        ans[++ans.len] = 1;
    }
    return ans;
}
BigInteger BigInteger::operator *(int k) {
    BigInteger ans(*this);
    ll num = 0;
    ll tmp;
    for (int i = 1; i <= ans.len; i++) {
        tmp = ans[i] * 1ll * k + num;
        num = tmp / 100000000;
        ans[i] = tmp % 100000000;
    }
    while (num) {
        ans[++ans.len] = num % 100000000;
        num /= 100000000;
    }
    return ans;
}
BigInteger& BigInteger::operator +=(BigInteger k) {
    return (*this) = (*this) + k;
}
BigInteger& BigInteger::operator *=(int k) {
    return (*this) = (*this) * k;
}
void BigInteger::Write() {
    write(Int[len]);
    for (int i = len - 1; i >= 1; i--) {
        if (Int[i] < 10000000) {
            write(0);
        }
        if (Int[i] < 1000000) {
            write(0);
        }
        if (Int[i] < 100000) {
            write(0);
        }
        if (Int[i] < 10000) {
            write(0);
        }
        if (Int[i] < 1000) {
            write(0);
        }
        if (Int[i] < 100) {
            write(0);
        }
        if (Int[i] < 10) {
            write(0);
        }
        write(Int[i]);
    }
}
