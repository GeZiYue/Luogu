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
#define N 100005
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T>inline void read(T&);
template<class Fir, class... Res>void read(Fir&, Res&...);
template<class T>inline void write(const T&);
template<class Fir, class... Res>void write(const Fir&, const Res&...);
priority_queue<int, vector<int>, greater<int> >q[N];
int a[N];
bool lk[N];
int num[N];
int main () {
    int n;
    read(n);
    for (int i=1; i<=n; ++i) {
        read(num[i]);
    }
    sort(num+1, num+n+1);
    int now=1;
    a[1]=1;
    for (int i=2; i<=n; ++i) {
        if (num[i]!=num[i-1]) {
            a[i]=++now;
            lk[i]=num[i]==num[i-1]+1;
        }else {
            a[i]=now;
            lk[i]=lk[i-1];
        }
    }
    for (int i=1; i<=n; ++i) {
        if (lk[i]&&a[i]!=1) {
            if (!q[a[i]-1].empty()) {
                int k=q[a[i]-1].top();
                q[a[i]-1].pop();
                q[a[i]].push(k+1);
            }else {
                q[a[i]].push(1);
            }
        }else {
            q[a[i]].push(1);
        }
    }
    int ans=inf;
    for (int i=1; i<=now; ++i) {
        if (!q[i].empty()) {
            ans=min(ans, q[i].top());
        }
    }
    write(ans);
    EL;
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
