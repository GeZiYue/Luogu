#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<vector>
using namespace std;
#define isNum(a) (a>='0'&&a<='9')
#define SP putchar (' ')
#define EL putchar ('\n')
#define N 5
#define Mod 100000000
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T1>inline void read(T1&);
template<class T1>inline void write(T1);
int gcd(int, int);
class Matrix {
private:
    typedef unsigned int size_t;
    size_t n, m;
    int a[N][N];
public:
    Matrix(size_t n):n(n), m(n) {
        memset(a, 0, sizeof(a));
        size_t i;
        for (i=1; i<=n; i++) {
            a[i][i]=1;
        }
    }
    Matrix(size_t n, size_t m):n(n), m(m) {
        memset(a, 0, sizeof(a));
    }
    int* operator[](int k) {
        return a[k];
    }
    Matrix operator*(Matrix b) {
        if (m!=b.n) {
            throw "Error, can't multi!";
        }
        size_t i, j, k;
        Matrix ans(n, b.m);
        for (i=1; i<=n; i++) {
            for (j=1; j<=b.m; j++) {
                for (k=1; k<=m; k++) {
                    ans[i][j]=(ans[i][j]+(a[i][k]*1ll*b[k][j])%Mod)%Mod;
                }
            }
        }
        return ans;
    }
    Matrix operator*=(Matrix b) {
        return (*this)=(*this)*b;
    }
    Matrix operator^(size_t k) {
        if (n!=m) {
            throw "Error, can't multi itself!";
        }
        Matrix ans(n);
        Matrix now=(*this);
        while (k) {
            if (k&1) {
                ans*=now;
            }
            now*=now;
            k>>=1;
        }
        return ans;
    }
    Matrix operator^=(size_t b) {
        return (*this)=(*this)^b;
    }
};
int main () {
    int x, y;
    read(x);
    read(y);
    int k=gcd(x, y);
    if (k<=2) {
        write(1);
        EL;
        return 0;
    }
    Matrix ans(2, 2);
    ans[1][1]=1;
    ans[1][2]=1;
    ans[2][1]=1;
    ans^=(k-2);
    Matrix begin(1, 2);
    begin[1][1]=begin[1][2]=1;
    begin*=ans;
    write(begin[1][1]);
    EL;
    return 0;
}
template<class T1>void read(T1 &r_e_a_d) {
    T1 k=0;
    char ch=getchar();
    int flag=1;
    while (!isNum(ch)) {
        if (ch=='-') {
            flag=-1;
        }
        ch=getchar();
    }
    while (isNum(ch) ) {
        k=(k<<1)+(k<<3)+ch-'0';
        ch=getchar();
    }
    r_e_a_d = flag*k;
}
template<class T1>void write(T1 w_r_i_t_e) {
    if (w_r_i_t_e<0) {
        putchar('-');
        write(-w_r_i_t_e);
    }else {
        if (w_r_i_t_e<10) {
            putchar(w_r_i_t_e+'0');
        }else {
            write(w_r_i_t_e/10);
            putchar((w_r_i_t_e%10)+'0');
        }
    }
}
int gcd(int a, int b) {
    if (b==0) {
        return a;
    }
    return gcd(b, a%b);
}
