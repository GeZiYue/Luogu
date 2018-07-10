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
#define ls(x) (x << 1)
#define rs(x) (ls(x)|1)
#define File(a) freopen(a".in" , "r" , stdin) , freopen(a".out" , "w" , stdout)
template<class T1>void read(T1&);
template<class T1>void write(T1);
void Tree_Push_Down(int , int , int);
void Tree_Push_Up(int);
int Tree_Query(int , int , int , int , int);
void Tree_Update(int , int , int , int , int);
int sum[4 * N];
bool tag[4 * N];
int main () {
    int n , m , x , y , z , i;
    read(n);
    read(m);
    for (i = 1 ; i <= m ; i++) {
        read(x);
        read(y);
        read(z);
        if (x == 0) {
            Tree_Update(1 , 1 , n , y , z);
        }else {
            write(Tree_Query(1 , 1 , n , y , z));
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
void Tree_Push_Down(int x , int xL , int xR) {
    int xM = (xL + xR) >> 1;
    if (tag[x]) {
        tag[x] = false;
        sum[ls(x)] = (xM - xL + 1) - sum[ls(x)];
        tag[ls(x)] ^= 1;
        sum[rs(x)] = (xR - xM) - sum[rs(x)];
        tag[rs(x)] ^= 1;
    }
}
void Tree_Push_Up(int x) {
    sum[x] = sum[ls(x)] + sum[rs(x)];
}
int Tree_Query(int x , int xL , int xR , int qL , int qR) {
    if (xL >= qL && xR <= qR) {
        return sum[x];
    }
    if (xR < qL || xL > qR) {
        return 0;
    }
    Tree_Push_Down(x , xL , xR);
    int xM = (xL + xR) >> 1;
    return Tree_Query(ls(x) , xL , xM , qL , qR) + Tree_Query(rs(x) , xM + 1 , xR , qL , qR);
}
void Tree_Update(int x , int xL , int xR , int uL , int uR) {
    if (xL >= uL && xR <= uR) {
        sum[x] = (xR - xL + 1) - sum[x];
        tag[x] ^= 1;
        return ;
    }
    if (xR < uL || xL > uR) {
        return ;
    }
    Tree_Push_Down(x , xL , xR);
    int xM = (xL + xR) >> 1;
    Tree_Update(ls(x) , xL , xM , uL , uR);
    Tree_Update(rs(x) , xM + 1 , xR , uL , uR);
    Tree_Push_Up(x);
}
