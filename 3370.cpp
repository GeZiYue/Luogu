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
#define Mod1 19260817
#define Mod2 19660813
#define Base 233
#define N 10005
#define File(a) freopen(a".in" , "r" , stdin) , freopen(a".out" , "w" , stdout)
template<class T1>void read(T1&);
template<class T1>void write(T1);
int Hash(int , int , string);
pair<int , int>h[N];
int main () {
    int n , ans = 1 , i;
    string str;
    read(n);
    for (i = 1 ; i <= n ; i++) {
        cin >> str;
        h[i].first = Hash(Base , Mod1 , str);
        h[i].second = Hash(Base , Mod2 , str);
    }
    sort(h + 1, h + n + 1);
    for (i = 2 ; i <= n ; i++) {
        if (h[i].first != h[i - 1].first || h[i].second != h[i - 1].second) {
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
int Hash(int base , int mod , string str) {
    int size = str.size() , ans = 0 , i;
    for (i = 0 ; i < size ; i++) {
        ans = (ans * base % mod + int(str[i])) % mod;
    }
    return ans;
}
