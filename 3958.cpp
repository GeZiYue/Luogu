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
#define ll long long int
#define pow(x) ((x) * (x))
#define File(a) freopen(a".in" , "r" , stdin) , freopen(a".out" , "w" , stdout)
template<class T1>void read(T1&);
template<class T1>void write(T1);
int find(int);
void merge(int , int);
ll x[N] , y[N] , z[N];
int fa[N];
int main () {
    int t , n , h , r , i , j;
    double far;
    read(t);
    while (t--) {
        read(n);
        read(h);
        read(r);
        for (i = 1 ; i <= (n + 2) ; i++) {
            fa[i] = i;
        }
        for (i = 1 ; i <= n ; i++) {
            read(x[i]);
            read(y[i]);
            read(z[i]);
            if (z[i] <= r) {
                merge(i , n + 1);
            }
            if ((h - z[i]) <= r) {
                merge(i , n + 2);
            }
        }
        for (i = 1 ; i <= n ; i++) {
            for (j = i + 1 ; j <= n ; j++) {
                far = sqrt((pow(x[i] - x[j]) + pow(y[i] - y[j]) + pow(z[i] - z[j])) * 1.0);
                if (far < 2 * r || abs(far - 2 * r) <= 0.0000000001) {
                    merge(i , j);
                }
            }
        }
        if (find(n + 1) == find(n + 2)) {
            puts("Yes");
        }else {
            puts("No");
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
int find(int x) {
    if (fa[x] == x) {
        return x;
    }
    return fa[x] = find(fa[x]);
}
void merge(int x, int y) {
    int fx = find(x) , fy = find(y);
    fa[fy] = fx;
}
