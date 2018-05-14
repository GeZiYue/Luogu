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
#define lowbit(x) (x&(-x))
#define Mod 1000000009
#define N 100005
#define ll long long int
#define File(a) freopen(a".in","r",stdin),freopen(a".out","w",stdout)
template<class T1>void read(T1 &r_e_a_d);
template<class T1>void write(T1 w_r_i_t_e);
void Update(int,int);
int Query(int);
class Node{
public:
    int num;
    int id;
    friend bool operator<(Node,Node);
}a[N];
int sum[N],num[N];
int tot;
ll dp[N];
int main(){
    int n,i,j,now;
    read(n);
    for(i=1;i<=n;i++){
        read(j);
        a[i].num=a[i-1].num+j;
        a[i].id=i;
    }
    sort(a,a+n+1);
    num[a[0].id]=1;
    j=1;
    for(i=1;i<=n;i++){
        if(a[i].num!=a[i-1].num){
            num[a[i].id]=++j;
        }else{
            num[a[i].id]=j;
        }
    }
    tot=j;
    Update(num[0],1);
    for(i=1;i<=n;i++){
        now=Query(num[i]);
        Update(num[i],now);
    }
    write(now);
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
    return i.num<j.num;
}
void Update(int x,int num){
    int i=x;
    while(i<=tot){
        sum[i]=(sum[i]+num)%Mod;
        i+=lowbit(i);
    }
}
int Query(int x){
    int i=x,ans=0;
    while(i>0){
        ans=(ans+sum[i])%Mod;
        i-=lowbit(i);
    }
    return ans;
}
