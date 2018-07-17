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
#define N 55
#define File(a) freopen(a".in" , "r" , stdin) , freopen(a".out" , "w" , stdout)
template<class T1>void read(T1&);
template<class T1>void write(T1);
int a[N];
int main () {
    int n , ans1 = 0 , ans2 = 0 , sum = 0 , i , L , R;
    read(n);
    for (i = 1 ; i <= n ; i++) {
        read(a[i]);
        sum += a[i];
    }
    read(L);
    read(R);
    if (sum < n * L || sum > n * R) {
        write(-1);
        EL;
    }else {
        for (i = 1 ; i <= n ; i++) {
            if (a[i] > R) {
                ans1 += a[i] - R;
            }
            if (a[i] < L){
                ans2 += L - a[i];
            }
        }
        write(max(ans1 , ans2));
        EL;
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
