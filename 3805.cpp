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
#define N 11000005
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T1>inline void read(T1&);
template<class T1>inline void write(T1);
char str[N<<1];
char ch[N];
int hw[N<<1];
int main () {
    cin>>(ch+1);
    str[0]=str[1]='#';
    int n=strlen(ch+1);
    for (int i=1; i<=n; ++i) {
        str[i<<1]=ch[i];
        str[i<<1|1]='#';
    }
    n=n<<1|1;
    int mid=1, maxr=1, ans=1;
    hw[1]=1;
    for (int i=2; i<n; ++i) {
        if (i<maxr) {
            hw[i]=min(hw[(mid<<1)-i], hw[mid]+mid-i);
        }else {
            hw[i]=1;
        }
        while (str[i+hw[i]]==str[i-hw[i]]) {
            ++hw[i];
        }
        if (i+hw[i]>maxr) {
            maxr=i+hw[i];
            mid=i;
        }
        if (hw[i]>ans) {
            ans=hw[i];
        }
    }
    write(ans-1);
    EL;
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
