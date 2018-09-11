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
#define N 10
#define ll long long int
#define File(a) freopen(a".in" , "r" , stdin) , freopen(a".out" , "w" , stdout)
template<class T1>void read(T1&);
template<class T1>void write(T1);
class Matrix {
public:
    int n;
    ll num[N][N];
    Matrix(){
        memset(this->num , 0 , sizeof(this->num));
    }
    Matrix(int n):n(n){
        memset(this->num , 0 , sizeof(this->num));
    }
    void Clear(int n){
        this->n = n;
        int i;
        for (i = 1 ; i <= n ; i++) {
            this->num[i][i] = 1;
        }
    }
    friend Matrix operator*(Matrix , Matrix);
    friend Matrix operator^(Matrix , ll);
};
Matrix e(2);
ll Mod;
int main () {
    Matrix chg(2) , fib(2);
    ll n;
    ll p , q , a1 , a2;
    read(p);
    read(q);
    read(a1);
    read(a2);
    read(n);
    read(Mod);
    if (n == 1) {
        write(a1);
        EL;
        return 0;
    }
    if (n == 2) {
        write(a2);
        EL;
        return 0;
    }
    e.num[1][1] = e.num[2][2] = 1;
    chg.num[1][1] = p;
    chg.num[1][2] = q;
    chg.num[2][1] = 1;
    fib.num[1][1] = a2;
    fib.num[2][1] = a1;
    write(((chg ^ (n - 2)) * fib).num[1][1]);
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
Matrix operator*(Matrix M1 , Matrix M2) {
    int i , j , k;
    Matrix ans(M1.n);
    for (i = 1 ; i <= M1.n ; i++) {
        for (j = 1 ; j <= M1.n ; j++) {
            for (k = 1 ; k <= M1.n ; k++) {
                ans.num[i][j] = (ans.num[i][j] + M1.num[i][k] * M2.num[k][j] % Mod) % Mod;
            }
        }
    }
    return ans;
}
Matrix operator^(Matrix M , ll k) {
    Matrix ans(e) , now(M);
    while (k) {
        if (k & 1) {
            ans = ans * now;
        }
        now = now * now;
        k >>= 1;
    }
    return ans;
}
