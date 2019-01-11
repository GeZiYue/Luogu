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
#define N 200005
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T>inline void read(T&);
template<class Fir, class... Res>void read(Fir&, Res&...);
template<class T>inline void write(const T&);
template<class Fir, class... Res>void write(const Fir&, const Res&...);
class Node {
public:
    int id, hg;
    int nh;
}a[N<<1];
template<class T>class BIT {
private:
    T *sum;
    int Size;
    int memsiz;
public:
    BIT(const int&);
    ~BIT();
    T query(int);
    void update(int, T);
};
void Update(int, int);
int mod[N], nm[N];
int h[N<<1];
int n, m;
int num=1;
BIT<int>*TT;
int main () {
    read(n, m);
    for (int i=1; i<=n; ++i) {
        read(a[i].hg);
        a[i].id=i;
    }
    for (int i=1; i<=m; ++i) {
        read(mod[i]);
        if (mod[i]==2) {
            read(nm[i]);
        }
        read(a[i+n].hg);
        if (mod[i]==1) {
            --a[i+n].hg;
        }
        a[i+n].id=i+n;
    }
    sort(a+1, a+n+m+1, [](const Node& i, const Node& j) {
        return i.hg<j.hg;
    });
    h[a[1].id]=1;
    for (int i=2; i<=n+m; ++i) {
        if (a[i].hg!=a[i-1].hg) {
            h[a[i].id]=++num;
        }else {
            h[a[i].id]=num;
        }
    }
    BIT<int>B(num);
    TT=&B;
    B.update(1, 1);
    for (int i=1; i<=n; ++i) {
        Update(i, 1);
    }
    for (int i=1; i<=m; ++i) {
        if (mod[i]==1) {
            write(B.query(h[i+n]));
            EL;
        }else {
            int now=nm[i];
            Update(now, -1), Update(now-1, -1), Update(now+1, -1);
            h[now]=h[i+n];
            Update(now, 1), Update(now-1, 1), Update(now+1, 1);
        }
    }
    return 0;
}
template<class T>void read(T &Re) {
    T k=0;
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
    Re=flag*k;
}
template<class Fir, class... Res>void read(Fir& Fi, Res&... Re) {
    read(Fi);
    read(Re...);
}
template<class T>void write(const T& Wr) {
    if (Wr<0) {
        putchar('-');
        write(-Wr);
    }else {
        if (Wr<10) {
            putchar(Wr+'0');
        }else {
            write(Wr/10);
            putchar((Wr%10)+'0');
        }
    }
}
template<class Fir, class... Res>void write(const Fir& Fi, const Res&... Re) {
    write(Fi);
    putchar(' ');
    write(Re...);
}
template<class T>BIT<T>::BIT(const int& Size):Size(Size) {
    sum=new int[Size+5];
    memsiz=(Size+2)*sizeof(T);
    memset(sum, 0, memsiz);
}
template<class T>BIT<T>::~BIT() {
    delete[] sum;
}
template<class T>T BIT<T>::query(int x) {
    T ans=0;
    while (x) {
        ans+=sum[x];
        x^=x&(-x);
    }
    return ans;
}
template<class T>void BIT<T>::update(int x, T num) {
    while (x<=Size) {
        sum[x]+=num;
        x+=x&(-x);
    }
}
void Update(int x, int num) {
    if (!x||x>n) {
        return;
    }
    int tmp=h[n+1];
    h[n+1]=0;
    if (h[x-1]<=h[x]&&h[x]>h[x+1]) {
        TT->update(h[x], -num);
    }else {
        if (h[x-1]>h[x]&&h[x]<=h[x+1]&&x!=n) {
            TT->update(h[x], num);
        }
    }
    h[n+1]=tmp;
}
