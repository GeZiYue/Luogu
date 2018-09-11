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
class Node {
public:
    int x , y , id;
    bool col;
    friend bool operator < (Node , Node);
}a[N];
int qx , qy;
int main () {
    int n , i , c;
    read(n);
    read(qx);
    read(qy);
    for (i = 1 ; i <= n ; i++) {
        read(a[i].x);
        read(a[i].y);
        read(c);
        a[i].col = (c == 1);
        a[i].id = i;
    }
    sort(a + 1 , a + n + 1);
    int ans = 0 , now = 0;
    for (i = 1 ; i <= n ; i++) {
        now += a[i].col;
        if ((now << 1) >= i) {
            ans++;
        }
    }
    write(ans);
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
bool operator < (Node i , Node j) {
    long long ni , nj;
    ni = (long long)(i.x - qx) * (i.x - qx) + (long long)(i.y - qy) * (i.y - qy);
    nj = (long long)(j.x - qx) * (j.x - qx) + (long long)(j.y - qy) * (j.y - qy);
    if (ni == nj) {
        return i.id < j.id;
    }else {
        return ni < nj;
    }
}
