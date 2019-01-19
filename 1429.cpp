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
class Point {
public:
    double x, y;
}a[N];
double dis(const Point&, const Point&);
double work(const int&, const int&);
int main () {
    int n;
    read(n);
    for (int i=1; i<=n; ++i) {
        cin>>a[i].x>>a[i].y;
    }
    sort(a+1, a+n+1, [](const Point& i, const Point& j) {
        if (i.x==j.x) {
            return i.y<=j.y;
        }
        return i.x<=j.x;
    });
    printf("%.4f\n", work(1, n));
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
double dis(const Point& x, const Point& y) {
    return sqrt((x.x-y.x)*(x.x-y.x)+(x.y-y.y)*(x.y-y.y));
}
double work(const int& l, const int& r) {
    double d=inf;
    if (l==r) {
        return d;
    }
    if (l+1==r) {
        return dis(a[l], a[r]);
    }
    int m=(l+r)>>1;
    d=min(work(l, m), work(m+1, r));
    vector<int>ans;
    for (int i=l; i<=r; ++i) {
        if (abs(a[m].x-a[i].x)<=d) {
            ans.push_back(i);
        }
    }
    sort(ans.begin(), ans.end(), [](const int& i, const int& j) {
        return a[i].y<a[j].y;
    });
    for (unsigned i=0; i<ans.size()-1; ++i) {
        for (unsigned j=i+1; j<ans.size()&&a[ans[j]].y-a[ans[i]].y<d; ++j) {
            d=min(d, dis(a[ans[i]], a[ans[j]]));
        }
    }
    return d;
}
