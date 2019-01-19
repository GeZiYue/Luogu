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
#define N 5005
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T>inline void read(T&);
template<class Fir, class... Res>void read(Fir&, Res&...);
template<class T>inline void write(const T&);
template<class Fir, class... Res>void write(const Fir&, const Res&...);
class Node {
public:
    int num;
    int k;
    bool operator<(Node i) {
        if (num==i.num) {
            return k>i.k;
        }
        return num<i.num;
    }
}a[N<<1];
int main () {
    int n;
    read(n);
    for (int i=1; i<=n; ++i) {
        read(a[i].num);
        a[i].k=1;
        read(a[i+n].num);
        a[i+n].k=-1;
    }
    sort(a+1, a+(n<<1)+1);
    int beg=a[1].num;
    int ans1=0, ans2=0;
    int now=1;
    for (int i=2; i<=(n<<1); ++i) {
        if (now==0) {
            ans2=max(ans2, a[i].num-a[i-1].num);
            now+=a[i].k;
            beg=a[i].num;
        }else {
            now+=a[i].k;
            if (now==0) {
                ans1=max(ans1, a[i].num-beg);
            }
        }
    }
    write(ans1, ans2);EL;
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
