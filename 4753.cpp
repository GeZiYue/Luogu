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
#define File(a) freopen(a".in" , "r" , stdin) , freopen(a".out" , "w" , stdout)
template<class T1>void read(T1&);
template<class T1>void write(T1);
int a[N] , ans[N] , id;
bool f[N];
int main () {
    int m , n , s , i , now , f1 = false;
    read(m);
    read(n);
    read(s);
    for (i = 1 ; i <= n ; i++) {
        read(a[i]);
    }
    a[0] = 0;
    a[n + 1] = m;
    now = 0;
    for (i = 1 ; i <= n + 1 ; i++) {
        if (a[i] - now >= s) {
            now = a[i];
            f[i] = true;
            ans[++id] = i;
        }
    }
    if (now != m) {
        puts("NO");
        return 0;
    }
    for (i = n ; i >= 0 ; i--) {
        if (now - a[i] >= s && f[i] == false) {
            now = a[i];
            f[i] = true;
            ans[++id] = i;
        }else {
            if (f[i] == false) {
                puts("NO");
                return 0;
            }
        }
    }
    if (now != 0) {
        puts("NO");
        return 0;
    }
    puts("YES");
    for (i = 1 ; i <= id ; i++) {
        write(ans[i]);
        SP;
    }
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
