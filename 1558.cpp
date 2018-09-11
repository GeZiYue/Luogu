#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<bitset>
using namespace std;
#define isNum(a) (a >= '0' && a <= '9')
#define SP putchar (' ')
#define EL putchar ('\n')
#define ls(x) (x << 1)
#define rs(x) (x << 1 | 1)
#define N 400005
#define File(a) freopen(a".in" , "r" , stdin) , freopen(a".out" , "w" , stdout)
template<class T1>void read(T1&);
template<class T1>void write(T1);
typedef bitset<31> bit;
void Push_Down(int);
void Push_Up(int);
void Build(int , int , int);
void Update(int , int , int , int , int , int);
bit Query(int , int , int , int , int);
bit col[N];
bool tag[N];
int main () {
    int n , m , k , i , a , b , c;
    char ch;
    read(n);
    read(k);
    read(m);
    Build(1 , 1 , n);
    for (i = 1 ; i <= m ; i++) {
        cin >> ch;
        read(a);
        read(b);
        if (a > b) {
            swap(a , b);
        }
        if (ch == 'C') {
            read(c);
            Update(1 , 1 , n , a , b , c);
        }else {
            write(Query(1 , 1 , n , a , b).count());
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
void Push_Down(int x) {
    if (tag[x]) {
        col[ls(x)] = col[x];
        col[rs(x)] = col[x];
        tag[ls(x)] = true;
        tag[rs(x)] = true;
        tag[x] = false;
    }
}
void Push_Up(int x) {
    col[x] = col[ls(x)] | col[rs(x)];
}
void Build(int x , int xL , int xR) {
    col[x][1] = true;
    if (xL == xR) {
        return;
    }
    int xM = (xL + xR) >> 1;
    Build(ls(x) , xL , xM);
    Build(rs(x) , xM + 1 , xR);
}
void Update(int x , int xL , int xR , int uL , int uR , int color) {
    if (xL >= uL && xR <= uR) {
        col[x].reset();
        col[x][color] = true;
        tag[x] = true;
        return;
    }
    if (xL > uR || xR < uL) {
        return;
    }
    Push_Down(x);
    int xM = (xL + xR) >> 1;
    Update(ls(x) , xL , xM , uL , uR , color);
    Update(rs(x) , xM + 1 , xR , uL , uR , color);
    Push_Up(x);
}
bit Query(int x , int xL , int xR , int qL , int qR) {
    if (xL >= qL && xR <= qR) {
        return col[x];
    }
    if (xL > qR || xR < qL) {
        return bit();
    }
    Push_Down(x);
    int xM = (xL + xR) >> 1;
    return Query(ls(x) , xL , xM , qL , qR) | Query(rs(x) , xM + 1 , xR , qL , qR);
}
