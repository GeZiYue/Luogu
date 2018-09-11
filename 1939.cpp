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
#define Mod 1000000007
#define ll long long int
#define N 10
#define File(a) freopen(a".in" , "r" , stdin) , freopen(a".out" , "w" , stdout)
template<class T1>void read(T1&);
template<class T1>void write(T1);
class Matrix {
public:
    int n;
    ll num[N][N];
    Matrix() {
        memset(this->num , 0 , sizeof(this->num));
    }
    Matrix(int n):n(n) {
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
Matrix e;
int main () {
    Matrix ans(3) , pre(3);
    e.Clear(3);
    ans.num[1][1] = 1;
    ans.num[1][3] = 1;
    ans.num[2][1] = 1;
    ans.num[3][2] = 1;
    pre.num[1][1] = 1;
    pre.num[2][1] = 1;
    pre.num[3][1] = 1;
    int t , n;
    read(t);
    while (t--) {
        read(n);
        if (n <= 3) {
            puts("1");
            continue;
        }
        write(((ans ^ (n - 3)) * pre).num[1][1]);
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
