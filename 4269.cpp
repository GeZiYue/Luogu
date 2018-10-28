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
#define N 100005
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T1>inline void read(T1&);
template<class T1>inline void write(T1);
class Snow {
public:
    int dep, num;
    bool operator<(Snow i)const {
        return this->dep>i.dep;
    }
}a[N];
class Boot:public Snow {
public:
    int far;
}b[N];
int aft[N], bef[N];
bool ans[N];
int main () {
    int n, m;
    read(n);
    read(m);
    for (int i=1; i<=n; ++i) {
        read(a[i].dep);
        a[i].num=i;
        aft[i]=i+1;
        bef[i]=i-1;
    }
    sort(a+1, a+n+1);
    for (int i=1; i<=m; ++i) {
        read(b[i].dep);
        read(b[i].far);
        b[i].num=i;
    }
    sort(b+1, b+m+1);
    int maxi=1;
    for (int i=1, j=1; i<=m; ++i) {
        while (j<=n&&b[i].dep<a[j].dep) {
            bef[aft[a[j].num]]=bef[a[j].num];
            aft[bef[a[j].num]]=aft[a[j].num];
            maxi=max(maxi, aft[a[j].num]-bef[a[j].num]);
            ++j;
        }
        ans[b[i].num]=(b[i].far>=maxi);
    }
    for (int i=1; i<=m; ++i) {
        write(ans[i]);
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
