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
template<int S_i_z_e,class T = int>
    class BIT {
    private:
        T sum[S_i_z_e + 1];
        #define lowbit(a) (a & (-a))
    public:
        void Update(int x , T num) {
            int i = x;
            while(i <= S_i_z_e) {
                sum[i] += num;
                i += lowbit(i);
            }
        }
        T Query(int x) {
            int i = x - lowbit(x);
            T ans = sum[x];
            while(i) {
                ans += sum[i];
                i -= lowbit(i);
            }
            return ans;
        }
    };
BIT<N> x , y;
int main () {
    int n , m , i , q , a , b;
    read(n);
    read(m);
    for (i = 1 ; i <= m ; i++) {
        read(q);
        read(a);
        read(b);
        if (q == 1) {
            x.Update(a , 1);
            y.Update(b , 1);
        }else {
            write(x.Query(b) - y.Query(a - 1));
            EL;
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
