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
#define inf 2147483647
#define File(a) freopen(a".in" , "r" , stdin) , freopen(a".out" , "w" , stdout)
template<class T1>void read(T1&);
template<class T1>void write(T1);
int rand();
class Node {
public:
    int ls;
    int rs;
    int key;
    int pri;
    int cnt;
    int siz;
};

class Treap {
public:
    Node s[N];
    int root , tot;
    void Update(int&);
    void Zig(int&);
    void Zag(int&);
    void Insert(int& , int);
    void Delete(int& , int);
    int Query_Rank(int , int);
    int Query_Kth(int , int);
    int Before(int , int);
    int After(int , int);
}T;

int main () {
    int n , i , x , y;
    read(n);
    for (i = 1 ; i <= n ; i++) {
        read(x);
        read(y);
        if (x == 1) {
            T.Insert(T.root , y);
        }
        if (x == 2) {
            T.Delete(T.root , y);
        }
        if (x == 3) {
            write(T.Query_Rank(T.root , y));
            EL;
        }
        if (x == 4) {
            write(T.Query_Kth(T.root , y));
            EL;
        }
        if (x == 5) {
            write(T.Before(T.root , y));
            EL;
        }
        if (x == 6) {
            write(T.After(T.root , y));
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

int rand() {
    static int seed = 708;
    seed = seed * 482711ll % 2147483647;
    return seed;
}

void Treap::Update(int &x) {
    s[x].siz = s[s[x].ls].siz + s[s[x].rs].siz + s[x].cnt;
}
void Treap::Zig(int &x) {
    int r = s[x].rs;
    s[x].rs = s[r].ls;
    s[r].ls = x;
    s[r].siz = s[x].siz;
    Update(x);
    x = r;
}
void Treap::Zag(int &x) {
    int l = s[x].ls;
    s[x].ls = s[l].rs;
    s[l].rs = x;
    s[l].siz = s[x].siz;
    Update(x);
    x = l;
}
void Treap::Insert(int &x , int k) {
    if (x == 0) {
        tot++;
        x = tot;
        s[x].siz = 1;
        s[x].cnt = 1;
        s[x].key = k;
        s[x].pri = rand();
        return;
    }
    s[x].siz++;
    if (s[x].key == k) {
        s[x].cnt++;
    }else {
        if (k < s[x].key) {
            Insert(s[x].ls , k);
            if (s[x].pri > s[s[x].ls].pri) {
                Zag(x);
            }
        }else {
            Insert(s[x].rs , k);
            if (s[x].pri > s[s[x].rs].pri) {
                Zig(x);
            }
        }
    }
}
void Treap::Delete(int &x , int k) {
    if (s[x].key == k) {
        if (s[x].cnt > 1) {
            s[x].siz--;
            s[x].cnt--;
            return;
        }
        if (s[x].ls * s[x].rs == 0) {
            x = s[x].ls + s[x].rs;
            return;
        }
        if (s[s[x].ls].pri < s[s[x].rs].pri) {
            Zag(x);
            Delete(x , k);
        }else {
            Zig(x);
            Delete(x , k);
        }
    }else {
        s[x].siz--;
        if (k < s[x].key) {
            Delete(s[x].ls , k);
        }else {
            Delete(s[x].rs , k);
        }
    }
}
int Treap::Query_Rank(int x , int k) {
    int ans = 0;
    while (x) {
        if (k == s[x].key) {
            return ans + s[s[x].ls].siz + 1;
        }
        if (k < s[x].key) {
            x = s[x].ls;
        }else {
            ans += s[s[x].ls].siz + s[x].cnt;
            x = s[x].rs;
        }
    }
}
int Treap::Query_Kth(int x , int k) {
    while (x) {
        if (k > s[s[x].ls].siz && k <= s[s[x].ls].siz + s[x].cnt) {
            return s[x].key;
        }
        if (k <= s[s[x].ls].siz) {
            x = s[x].ls;
        }else {
            k -= s[s[x].ls].siz + s[x].cnt;
            x = s[x].rs;
        }
    }
    return 0;
}
int Treap::Before(int x , int k) {
    int ans = -inf;
    while (x) {
        if (s[x].key < k) {
            ans = s[x].key;
            x = s[x].rs;
        }else {
            x = s[x].ls;
        }
    }
    return ans;
}
int Treap::After(int x , int k) {
    int ans = inf;
    while (x) {
        if (s[x].key > k) {
            ans = s[x].key;
            x = s[x].ls;
        }else {
            x = s[x].rs;
        }
    }
    return ans;
}
