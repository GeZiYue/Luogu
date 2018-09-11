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
#define N 1005
#define File(a) freopen(a".in" , "r" , stdin) , freopen(a".out" , "w" , stdout)
template<class T1>void read(T1&);
template<class T1>void write(T1);
int a[N] , b[N];
string str;
int main () {
    int n , i , ans = 0 , add;
    int len;
    read(n);
    cin >> str;
    len = str.size();
    for (i = 0 ; i < len ; i++) {
        if (isNum(str[i])) {
            a[len - i] = str[i] - '0';
        }else {
            a[len - i] = str[i] - 'A' + 10;
        }
    }
    while (1) {
        copy(a + 1 , a + len + 1 , b + 1);
        reverse(a + 1 , a + len + 1);
        for (i = 1 ; i <= len ; i++) {
            if (a[i] != b[i]) {
                goto con;
            }
        }
        cout << "STEP=" << ans << endl;
        return 0;
        con:;
        if (ans >= 30) {
            break;
        }
        add = 0;
        for (i = 1 ; i <= len ; i++) {
            a[i] = a[i] + b[i] + add;
            add = a[i] / n;
            a[i] %= n;
        }
        if (add) {
            a[++len] = add;
        }
        ans++;
    }
    puts("Impossible!");
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
