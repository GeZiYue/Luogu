#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<vector>
using namespace std;
#define isNum(a) (a>='0'&&a<='9')
#define SP putchar (' ')
#define EL putchar ('\n')
#define inf 2147483647
#define N 20005
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T1>inline void read(T1&);
template<class T1>inline void write(T1);
void Push_Up(int, int, int);
void Build(int, int, int);
void Update(int, int, int, int);
int Query();
bool num[N];
int Left[N<<2], Right[N<<2], Middle[N<<2];
int main () {
    int n, m;
    read(n);
    read(m);
    Build(1, 1, n);
    for (int i=1; i<=m; ++i) {
        int x;
        read(x);
        Update(1, 1, n, x);
        write(Query());
        EL;
    }
    return 0;
}
template<class T1>void read(T1 &r_e_a_d) {
    T1 k=0;
    char ch=getchar();
    int flag=1;
    while (!isNum(ch)) {
        if (ch=='-') {
            flag=-1;
        }
        ch=getchar();
    }
    while (isNum(ch) ) {
        k=(k<<1)+(k<<3)+ch-'0';
        ch=getchar();
    }
    r_e_a_d = flag*k;
}
template<class T1>void write(T1 w_r_i_t_e) {
    if (w_r_i_t_e<0) {
        putchar('-');
        write(-w_r_i_t_e);
    }else {
        if (w_r_i_t_e<10) {
            putchar(w_r_i_t_e+'0');
        }else {
            write(w_r_i_t_e/10);
            putchar((w_r_i_t_e%10)+'0');
        }
    }
}
void Build(int x, int xL, int xR) {
    if (xL==xR) {
        num[xL]=true;
        Left[x]=Right[x]=Middle[x]=1;
        return;
    }
    int xM=(xL+xR)>>1;
    Build(ls(x), xL, xM);
    Build(rs(x), xM+1, xR);
    Push_Up(x, xL, xR);
}
void Push_Up(int x, int xL, int xR) {
    int xM=(xL+xR)>>1;
    Left[x]=(Left[ls(x)]==(xM-xL+1)&&(num[xM]^num[xM+1]))?
    Left[ls(x)]+Left[rs(x)]:
    Left[ls(x)];
    Right[x]=(Right[rs(x)]==(xR-xM)&&(num[xM]^num[xM+1]))?
    Right[rs(x)]+Right[ls(x)]:
    Right[rs(x)];
    Middle[x]=max(Middle[ls(x)], Middle[rs(x)]);
    if (num[xM]^num[xM+1]) {
        Middle[x]=max(Middle[x], Right[ls(x)]+Left[rs(x)]);
    }
}
void Update(int x, int xL, int xR, int q) {
    if (xL>q||xR<q) {
        return;
    }
    if (xL==xR) {
        num[xL]=!num[xL];
        return;
    }
    int xM=(xL+xR)>>1;
    Update(ls(x), xL, xM, q);
    Update(rs(x), xM+1, xR, q);
    Push_Up(x, xL, xR);
}
int Query() {
    return max(max(Left[1], Right[1]), Middle[1]);
}
