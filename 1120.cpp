#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<vector>
using namespace std;
#define isNum(a) (a >= '0' && a <= '9')
#define SP putchar (' ')
#define EL putchar ('\n')
#define N 105
#define File(a) freopen(a".in" , "r" , stdin) , freopen(a".out" , "w" , stdout)
template<class T1>void read(T1&);
template<class T1>void write(T1);
void DFS(int , int , int);
int a[N];
int n , m , p;
bool used[N];
int sum , maxi;
int main () {
    int k;
    read(k);
    n = k;
    for (int i = 1 ; i <= n ; i++) {
        read(a[i]);
        if (a[i] > 50) {
            i--;
            n--;
        }else {
            sum += a[i];
            maxi = max(maxi , a[i]);
        }
    }
    sort(a + 1 , a + n + 1 , greater<int>());
    for (int i = maxi ; i <= sum ; i++) {
        if (sum % i == 0) {
            memset(used , false , sizeof(used));
            m = sum / i;
            p = i;
            DFS(1 , 0 , i);
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
void DFS(int k , int last , int rest) {
    if (k == m) {
        write(p);
        EL;
        exit(0);
    }
    if (rest == 0) {
        DFS(k + 1 , 0 , p);
        return;
    }
    for (int i = last + 1 ; i <= n ; i++) {
        if (a[i] <= rest && used[i] == false) {
            used[i] = true;
            DFS(k , i , rest - a[i]);
            used[i] = false;
            if (rest == p || a[i] == rest) {
                return;
            }
            while (a[i] == a[i + 1]) {
                i++;
            }
        }
    }
}
