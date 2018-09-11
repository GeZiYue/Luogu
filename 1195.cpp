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
#define M 10005
#define File(a) freopen(a".in" , "r" , stdin) , freopen(a".out" , "w" , stdout)
template<class T1>void read(T1&);
template<class T1>void write(T1);
int find(int);
bool judge(int , int);
void merge(int , int);
int fa[N];
class Edge {
public:
    int x , y , c;
    bool operator<(Edge);
}a[M];
int main () {
    int n , m , k , i;
    read(n);
    read(m);
    read(k);
    for (i = 1 ; i <= m ; i++) {
        read(a[i].x);
        read(a[i].y);
        read(a[i].c);
    }
    sort(a + 1 , a + m + 1);
    for (i = 1 ; i <= n ; i++) {
        fa[i] = i;
    }
    int now = n , ans = 0;
    for (i = 1 ; i <= m ; i++) {
        if (judge(a[i].x , a[i].y)) {
            merge(a[i].x , a[i].y);
            now--;
            ans += a[i].c;
        }
        if (now == k) {
            write(ans);
            EL;
            return 0;
        }
    }
    puts("No Answer");
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
bool Edge::operator<(Edge i) {
    return this->c < i.c;
}
int find(int x) {
    if (fa[x] == x) {
        return x;
    }
    return fa[x] = find(fa[x]);
}
bool judge(int x , int y) {
    return find(x) != find(y);
}
void merge(int x , int y) {
    int fx = find(x) , fy = find(y);
    fa[fy] = fx;
}
