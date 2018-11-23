#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<queue>
#include<stack>
#include<set>
#include<map>
using namespace std;
#define isNum(a) (a>='0'&&a<='9')
#define SP putchar (' ')
#define EL putchar ('\n')
#define inf 2147483647
#define N 1000005
#define M 1005
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T1>inline void read(T1&);
template<class T1>inline void write(T1);
void GetBlock(int);
void Reset(int);
void Update(int, int, int);
int Query(int, int, int);
int v[N];
int aft[N];
int bel[N], l[M], r[M], tag[M];
int main () {
    int n, m;
    read(n);
    read(m);
    for (int i=1; i<=n; ++i) {
        read(v[i]);
    }
    GetBlock(n);
    for (int i=1; i<=m; ++i) {
        char ch;
        cin>>ch;
        int l, r, x;
        read(l);
        read(r);
        read(x);
        if (ch=='M') {
            Update(l, r, x);
        }else {
            write(Query(l, r, x));
            EL;
        }
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
    while (isNum(ch)) {
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
void GetBlock(int n) {
    int blocklen=int(sqrt(n));
    int m=n/blocklen+(n%blocklen!=0);
    for (int i=1; i<=n; ++i) {
        bel[i]=(i-1)/blocklen+1;
    }
    for (int i=1; i<=m; ++i) {
        l[i]=r[i-1]+1;
        r[i]=i*blocklen;
    }
    r[m]=n;
    for (int i=1; i<=m; ++i) {
        Reset(i);
    }
}
void Reset(int x) {
    for (int i=l[x]; i<=r[x]; ++i) {
        aft[i]=v[i];
    }
    sort(aft+l[x], aft+r[x]+1);
}
void Update(int L, int R, int x) {
    for (int i=L; i<=min(r[bel[L]], R); ++i) {
        v[i]+=x;
    }
    Reset(bel[L]);
    if (bel[L]^bel[R]) {
        for (int i=l[bel[R]]; i<=R; ++i) {
            v[i]+=x;
        }
        Reset(bel[R]);
    }
    for (int i=bel[L]+1; i<bel[R]; ++i) {
        tag[i]+=x;
    }
}
int Query(int L, int R, int x) {
    int ans=0;
    for (int i=L; i<=min(r[bel[L]], R); ++i) {
        if (v[i]+tag[bel[i]]>=x) {
            ++ans;
        }
    }
    if (bel[L]^bel[R]) {
        for (int i=l[bel[R]]; i<=R; ++i) {
            if (v[i]+tag[bel[i]]>=x) {
                ++ans;
            }
        }
    }
    for (int i=bel[L]+1; i<bel[R]; ++i) {
        ans+=r[i]-(lower_bound(aft+l[i], aft+r[i]+1, x-tag[i])-aft)+1;
    }
    return ans;
}
