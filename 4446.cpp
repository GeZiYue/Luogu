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
#define N 31630
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
typedef long long int ll;
template<class T1>inline void read(T1&);
template<class T1>inline void write(T1);
void Prime(int);
bool isP[N+5];
int Pr[N+5], id;
ll m[1000005];
int main () {
    Prime(N);
    int t;
    read(t);
    for (int i=1; i<=1000000; ++i) {
        m[i]=i*1ll*i*i;
    }
    while (t--) {
        ll n;
        read(n);
        int ans=1;
        int k=sqrt(sqrt(n));
        for (int i=1; i<=id&&n!=1&&Pr[i]<=k; ++i) {
            int now=0;
            while (n%Pr[i]==0) {
                n/=Pr[i];
                ++now;
                if (now==3) {
                    now=0;
                    ans*=Pr[i];
                }
            }
        }
        int now=lower_bound(m+1, m+1000001, n)-m;
        if (m[now]==n) {
            ans*=now;
        }
        write(ans);
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
void Prime(int n) {
    for (int i=2; i<=n; ++i) {
        if (!isP[i]) {
            Pr[++id]=i;
        }
        for (int j=1; j<=id&&i*Pr[j]<=n; ++j) {
            isP[i*Pr[j]]=true;
            if (i%Pr[j]==0) {
                break;
            }
        }
    }
}
