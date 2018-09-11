#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<set>
using namespace std;
#define isNum(a) (a >= '0' && a <= '9')
#define SP putchar (' ')
#define EL putchar ('\n')
#define N 2005
#define File(a) freopen(a".in" , "r" , stdin) , freopen(a".out" , "w" , stdout)
template<class T1>void read(T1&);
template<class T1>void write(T1);
bool check(int);
int a[N];
multiset<int>s;
int n , m;
int main () {
    int i , ans , L , M , R;
    read(n);
    read(m);
    for (i = 1 ; i <= n ; i++) {
        read(a[i]);
    }
    L = 1;
    R = n * 2000;
    while (L < R) {
        M = (L + R) >> 1;
        if (check(M)) {
            R = M;
        }else {
            L = M + 1;
        }
    }
    ans = L;
    for (i = L ; i >= L - 2000 ; i--) {
        if (check(i)) {
            ans = i;
        }
    }
    write(ans);
    EL;
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
bool check(int M) {
    int ans = 0 , now , i;
    for (i = 1 ; i <= n ; i++) {
        s.insert(a[i]);
    }
    while (ans <= m) {
        ans++;
        now = M;
        while (!s.empty()) {
            multiset<int>::iterator q = s.upper_bound(now);
            if (q == s.begin()) {
                break;
            }
            q--;
            now -= (*q);
            s.erase(q);
        }
        if (s.empty()) {
            break;
        }
    }
    s.clear();
    return ans <= m;
}
