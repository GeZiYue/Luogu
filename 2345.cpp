#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
#define isNum(a) (a>='0'&&a<='9')
#define SP putchar(' ')
#define EL putchar('\n')
#define N 20000
#define File(a) freopen(a".in","r",stdin),freopen(a".out","w",stdout)
template<class T1>void read(T1 &r_e_a_d);
template<class T1>void write(T1 w_r_i_t_e);
template<int S_i_z_e,class T=int>
    class BIT{
    private:
        T sum[S_i_z_e+1];
        #define lowbit(a) (a&(-a))
    public:
        void Update(int x,T num){
            int i=x;
            while(i<=S_i_z_e){
                sum[i]+=num;
                i+=lowbit(i);
            }
        }
        T Query(int x){
            int i=x-lowbit(x);
            T ans=sum[x];
            while(i){
                ans+=sum[i];
                i-=lowbit(i);
            }
            return ans;
        }
    };
class Node{
public:
    int x,v;
    friend bool operator<(Node,Node);
}a[N];
BIT<N,long long int>num,sum;
int main(){
    int n,i;
    long long int ans=0;
    read(n);
    for(i=1;i<=n;i++){
        read(a[i].v);
        read(a[i].x);
    }
    sort(a+1,a+n+1);
    for(i=1;i<=n;i++){
        ans+=(num.Query(a[i].x)*a[i].x-sum.Query(a[i].x)+sum.Query(N)-sum.Query(a[i].x)-(i-1-num.Query(a[i].x))*a[i].x)*a[i].v;
        num.Update(a[i].x,1);
        sum.Update(a[i].x,a[i].x);
    }
    write(ans);
    EL;
    return 0;
}
template<class T1>void read(T1 &r_e_a_d){
    T1 k=0;
    char ch=getchar();
    int flag=1;
    while(!isNum(ch)){
        if(ch=='-'){
            flag=-1;
        }
        ch=getchar();
    }
    while(isNum(ch)){
        k=(k<<1)+(k<<3)+ch-'0';
        ch=getchar();
    }
    r_e_a_d=flag*k;
}
template<class T1>void write(T1 w_r_i_t_e){
    if(w_r_i_t_e<0){
        putchar('-');
        write(-w_r_i_t_e);
    }else{
        if(w_r_i_t_e<10){
            putchar(w_r_i_t_e+'0');
        }else{
            write(w_r_i_t_e/10);
            putchar((w_r_i_t_e%10)+'0');
        }
    }
}
bool operator<(Node i,Node j){
    return i.v<j.v;
}
