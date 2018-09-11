#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<vector>
using namespace std;
#define isNum(a) (a >= '0' && a <= '9')
#define SP putchar (' ')
#define EL putchar ('\n')
#define File(a) freopen(a".in" , "r" , stdin) , freopen(a".out" , "w" , stdout)
template<class T1>void read(T1&);
template<class T1>void write(T1);
int main () {
    string a , b , c;
    cin >> a >> b >> c;
    double p , h , h1 , alpha , beta , r;
    cin >> p >> alpha >> r >> h;
    if (c == "AP") {
        beta = 5;
    }else {
        if (c == "APCR" || c == "APFSDS") {
            beta = 2;
        }else {
            beta = 0;
        }
    }
    if (r > h * 3) {
        beta *= 3;
    }else {
        if (r > h * 2) {
            beta *= 2;
        }
    }
    if (((c == "AP" || c == "APCR" || c == "APFSDS") && (alpha - beta) >= 70) || (c == "HEAT" && (alpha - beta) >= 85)) {
        cout << "We didn't penetrate their armor!" << endl;
        return 0;
    }
    h1 = h / cos((alpha - beta) * 3.1415926 / 180);
    if (p * 0.75 >= h1) {
        cout << "Penetration!" << endl;
    }else {
        if (p * 1.25 <= h1) {
            cout << "We didn't penetrate their armor!" << endl;
        }else {
            cout << "Server is important~" << endl;
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
