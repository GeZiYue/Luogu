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
#define N 50005
#define M 20005
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T>inline void read(T&);
template<class T>inline void write(const T&);
typedef long long int ll;
void Prime(int);
ll work(int, int, int);
bool isP[N];
int P[M], id;
int mu[N], sum[N];
int main () {
    Prime(50000);
    int t;
    read(t);
    while (t--) {
        int n, m, k;
        read(n), read(m), read(k);
        write(work(n, m, k));
        EL;
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
void Prime(int n) {
    mu[1]=sum[1]=1;
    for (int i=2; i<=n; ++i) {
        if (!isP[i]) {
            P[++id]=i;
            mu[i]=-1;
        }
        sum[i]=sum[i-1]+mu[i];
        for (int j=1; j<=id&&i*P[j]<=n; ++j) {
            isP[i*P[j]]=true;
            if (i%P[j]==0) {
                break;
            }
            mu[i*P[j]]=-mu[i];
        }
    }
}
ll work(int n, int m, int k) {
    n/=k, m/=k;
    int L=min(n, m);
    ll ans=0;
    for (int l=1, r; l<=L; l=r+1) {
        r=min(n/(n/l), m/(m/l));
        ans+=(n/l)*1ll*(m/l)*(sum[r]-sum[l-1]);
    }
    return ans;
}
