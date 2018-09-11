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
#define N 500005
#define M 55
#define File(a) freopen(a".in" , "r" , stdin) , freopen(a".out" , "w" , stdout)
template<class T1>void read(T1&);
template<class T1>void write(T1);
class Trie {
public:
    int nxt[N][30];
    bool end[N] , have[N];
    int id;
    void Add(string);
    void Query(string);
};
char s[M];
Trie T;
int main () {
    int n , m , i;
    read(n);
    for (i = 1 ; i <= n ; i++) {
        cin >> s;
        T.Add(string(s));
    }
    read(m);
    for (i = 1 ; i <= m ; i++) {
        cin >> s;
        T.Query(string(s));
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
void Trie::Add(string str) {
    int n = str.size() , i , now = 0;
    for (i = 0 ; i < n ; i++) {
        if (!this->nxt[now][str[i] - 'a']) {
            this->nxt[now][str[i] - 'a'] = ++this->id;
        }
        now = this->nxt[now][str[i] - 'a'];
    }
    this->end[now] = true;
}
void Trie::Query(string str) {
    int n = str.size() , i , now = 0;
    for (i = 0 ; i < n ; i++) {
        if (!this->nxt[now][str[i] - 'a']) {
            puts("WRONG");
            return;
        }
        now = this->nxt[now][str[i] - 'a'];
    }
    if (this->end[now] == false) {
        puts("WRONG");
    }else {
        if (this->have[now] == true) {
            puts("REPEAT");
        }else {
            this->have[now] = true;
            puts("OK");
        }
    }
}
