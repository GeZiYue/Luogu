#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<iomanip>
using namespace std;
#define isNum(a) (a >= '0' && a <= '9')
#define SP putchar (' ')
#define EL putchar ('\n')
#define N 100005
#define File(a) freopen(a".in" , "r" , stdin) , freopen(a".out" , "w" , stdout)
template<class T1>void read(T1&);
template<class T1>void write(T1);
bool judge(double);
int a[N];
double sum[N];
int n , s , t;
int que[N] , tail , head;
int main () {
    double L , M , R , ans;
    read(n);
    read(s);
    read(t);
    for (int i = 1 ; i <= n ; i++) {
        read(a[i]);
    }
    L = -10000;
    R = 10000;
    while (R - L > 0.00001) {
        M = (L + R) / 2;
        if (judge(M)) {
            L = M;
            ans = M;
        }else {
            R = M;
        }
    }
    cout << fixed << setprecision(3) << ans << endl;
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
bool judge(double M) {
    for (int i = 1 ; i <= n ; i++) {
        sum[i] = sum[i - 1] + a[i] - M;
    }
    tail = 0;
    head = 1;
    for (int i = s ; i <= n ; i++) {
        int now = i - s;
        while (head <= tail && sum[now] < sum[que[tail]]) {
            tail--;
        }
        que[++tail] = now;
        while (que[head] < i - t) {
            head++;
        }
        if (sum[i] - sum[que[head]] >= 0) {
            return true;
        }
    }
    return false;
}
