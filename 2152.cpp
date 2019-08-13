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
const int N = 2005;

class BigInteger {
private:
    int Int[N];
    int len;
    void AddLen(int k) {
        len += k;
    }
    void DelLen(int k) {
    	len -= k;
	}
public:
    int& operator[](int);
    bool isev();
    bool iszr();
    BigInteger div2();
    bool operator <(const BigInteger&) const;
    BigInteger operator -(const BigInteger&) const;
    BigInteger operator *(int);
    void Read();
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

BigInteger gcd(BigInteger, BigInteger);

BigInteger a, b;

int main () {
	a.Read(), b.Read();
	gcd(a, b).Write();
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
bool BigInteger::isev() {
	return !(Int[1] % 2);
}
bool BigInteger::iszr() {
	return len == 0;
}
BigInteger BigInteger::div2() {
	BigInteger ans(*this);
	for (int i = ans.len; i >= 1; --i) {
		ans[i - 1] += (ans[i] % 2) * 100000000;
		ans[i] >>= 1;
	}
    ans[0] = 0;
	while (ans.len && ans[ans.len] == 0) {
		ans.DelLen(1);
	}
    return ans;
}
bool BigInteger::operator <(const BigInteger &k) const {
	if (len != k.len) {
		return len < k.len;
	}
	for (int i = len; i >= 1; --i) {
		if (Int[i] != k.Int[i]) {
			return Int[i] < k.Int[i];
		}
	}
	return 0;
}
BigInteger BigInteger::operator -(const BigInteger &k) const {
	BigInteger ans(*this);
	for (int i = 1; i <= k.len; ++i) {
		ans[i] -= k.Int[i];
		if (ans[i] < 0) {
			--ans[i + 1];
			ans[i] += 100000000;
		}
	}
    for (int i = k.len + 1; i <= ans.len && ans[i] < 0; ++i) {
        --ans[i + 1];
        ans[i] += 100000000;
    }
	while (ans.len && ans[ans.len] == 0) {
		ans.DelLen(1);
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
void BigInteger::Read() {
	std::string str;
    std::cin >> str;
    len = str.size();
    std::reverse(str.begin(), str.end());
    for (int i = len; i >= 1; --i) {
        Int[(i - 1) / 8 + 1] = Int[(i - 1) / 8 + 1] * 10 + str[i - 1] - '0';
    }
    len = (len - 1) / 8 + 1;
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

BigInteger gcd(BigInteger a, BigInteger b) {
    BigInteger t(1);
    int k = 0;
    while (true) {
        if (b.iszr()) {
            t = a;
            break;
        }
        if (a.iszr()) {
            t = b;
            break;
        }
        if (a.isev() && b.isev()) {
            a = a.div2();
            b = b.div2();
            ++k;
        } else {
            if (a.isev()) {
                a = a.div2();
            } else {
                if (b.isev()) {
                    b = b.div2();
                } else {
                    if (a < b) {
                        b = b - a;
                    } else {
                        a = a - b;
                    }
                }
            }
        }
    }
    while (k--) {
        t = t * 2;
    }
    return t;
}
