#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
#define isNum(a) (a >= '0' && a <= '9')
#define SP putchar (' ')
#define EL putchar ('\n')
#define N 100005
#define M 1000005
#define ll unsigned long long int
#define File(a) freopen(a".in" , "r" , stdin) , freopen(a".out" , "w" , stdout)
template<class T1>void read(T1&);
template<class T1>void write(T1);
ll gcd(ll , ll);
bool check(ll);
ll a[N] , b[N];
int main () {
    int t , n , m , i , j , n2 , m2;
    bool flag;
    ll ans;
    read(t);
    while (t--) {
        read(n);
        read(m);
        n2 = n;
        m2 = m;
        for (i = 1 ; i <= n ; i++) {
            read(a[i]);
            if (a[i] == 1) {
                n2--;
            }
        }
        for (i = 1 ; i <= m ; i++) {
            read(b[i]);
            if (b[i] == 1) {
                m2--;
            }
        }
        if (n2 - m2 >= 2 || n2 == m2) {
            puts("NO");
            continue;
        }
        sort(a + 1 , a + n + 1);
        sort(b + 1 , b + m + 1);
        i = 1;
        j = 1;
        ans = 1;
        flag = false;
        while (1) {
            if (i > n && j > m) {
                break;
            }
            if (a[i] < b[j] || j > m) {
                if (ans != 1) {
                    flag = true;
                    break;
                }
                ans *= a[i];
                i++;
            }else {
                i++;
                j++;
            }
        }
        if (check(ans) && flag == false) {
            puts("YES");
        }else {
            puts("NO");
        }
    }
    return 0;
}
template<class T1>void read(T1 &r_e_a_d) {
    T1 k = 0;
    char ch = getchar();
    int flag = 1;
    while(!isNum(ch) ) {
        if (ch == '-') {
            flag = -1;
        }
        ch = getchar();
    }
    while(isNum(ch) ) {
        k = (k << 1) + (k << 3) + ch - '0';
        ch = getchar();
    }
    r_e_a_d = flag * k;
}
template<class T1>void write(T1 w_r_i_t_e) {
    if (w_r_i_t_e < 0) {
        putchar('-');
        write(-w_r_i_t_e);
    }else {
        if (w_r_i_t_e < 10) {
            putchar(w_r_i_t_e + '0');
        }else {
            write(w_r_i_t_e / 10);
            putchar( (w_r_i_t_e % 10) + '0');
        }
    }
}
ll gcd(ll a , ll b) {
    if (b == 0) {
        return a;
    }
    return gcd(b , a % b);
}
bool check(ll n) {
    int i;
    for (i = 2 ; i * i <= n ; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}
