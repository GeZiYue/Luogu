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
#define SP putchar(' ')
#define EL putchar('\n')
#define inf 2147483647
#define N 10005
#define M 105
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T>inline void read(T&);
template<class T>inline void write(const T&);
class Class {
public:
    int begin, end, abi;
    friend bool operator<(Class, Class);
}c[M];
int dp[N][M];
int lastmin[M];
int main () {
    int n, m, t;
    read(t);
    read(n);
    read(m);
    for (int i=1; i<=n; i++) {
        int begin, last, abi;
        read(begin);
        read(last);
        read(abi);
        c[i].begin=begin;
        c[i].end=begin+last;
        c[i].abi=abi;
    }
    sort(c+1, c+n+1, [](Class i, Class j) {
        return i.end<j.end;
    });
    for (int i=1; i<=100; i++) {
        lastmin[i]=inf;
    }
    for (int i=1; i<=m; i++) {
        int need, last;
        read(need);
        read(last);
        lastmin[need]=min(lastmin[need], last);
    }
    memset(dp, -1, sizeof(dp));
    for (int i=0; i<=t; i++) {
        dp[i][1]=0;
    }
    int ans=0;
    for (int i=1, j=1; i<=t; i++) {
        if (c[j].end==i) {
            for (int k=1; k<=100; k++) {
                dp[i][c[j].abi]=max(dp[i][c[j].abi], dp[c[j].begin][k]);
            }
            for (int k=1; k<c[j].abi; k++) {
                dp[i][k]=max(dp[i][k], dp[i][c[j].abi]);
            }
            j++;
        }
        for (int k=1; k<=100; k++) {
            if (i-lastmin[k]>=0) {
                if (dp[i-lastmin[k]][k]!=-1) {
                    dp[i][k]=max(dp[i][k], dp[i-lastmin[k]][k]+1);
                    ans=max(ans, dp[i][k]);
                }
            }
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
