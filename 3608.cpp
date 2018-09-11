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
#define lowbit(x) (x & -x)
#define N 100005
#define File(a) freopen(a".in" , "r" , stdin) , freopen(a".out" , "w" , stdout)
template<class T1>void read(T1&);
template<class T1>void write(T1);
void Update(int , int);
int Query(int);
class Node {
public:
    int num , id;
    friend bool operator<(Node , Node);
}a[N];
int to[N];
int sum[N];
int l[N] , r[N];
int tot;
int main () {
    int n , i , ans = 0;
    read(n);
    for (i = 1 ; i <= n ; i++) {
        read(a[i].num);
        a[i].id = i;
    }
    sort(a + 1 , a + n + 1);
    a[0].num = -1;
    for (i = 1 ; i <= n ; i++) {
        if (a[i].num == a[i - 1].num) {
            to[a[i].id] = tot;
        }else {
            to[a[i].id] = ++tot;
        }
    }
    for (i = 1 ; i <= n ; i++) {
        l[i] = Query(tot) - Query(to[i]);
        Update(to[i] , 1);
    }
    memset(sum , 0 , sizeof(sum));
    for (i = n ; i >= 1 ; i--) {
        r[i] = Query(tot) - Query(to[i]);
        Update(to[i] , 1);
    }
    for (i = 1 ; i <= n ; i++) {
        if (max(l[i] , r[i]) > min(l[i] , r[i]) * 2) {
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
bool operator<(Node i , Node j) {
    return i.num < j.num;
}
void Update(int x , int num) {
    int i = x;
    while (i <= tot) {
        sum[i] += num;
        i += lowbit(i);
    }
}
int Query(int x) {
    int i = x , ans = 0;
    while (i) {
        ans += sum[i];
        i -= lowbit(i);
    }
    return ans;
}
