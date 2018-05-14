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
#define ll long long int
#define N 10005
#define Mod 19260817
#define File(a) freopen(a".in","r",stdin),freopen(a".out","w",stdout)
template<class T1>void read(T1 &r_e_a_d);
template<class T1>void write(T1 w_r_i_t_e);
ll exgcd(ll,ll,ll&,ll&);
string a,b;
int main(){
    int n,m,i;
    ll sa=0,sb=0,x,y;
    cin>>a>>b;
    n=a.size();
    m=b.size();
    for(i=0;i<n;i++){
        sa=(sa*10+(a[i]-'0'))%Mod;
    }
    for(i=0;i<m;i++){
        sb=(sb*10+(b[i]-'0'))%Mod;
    }
    if(sa==0){
        puts("0");
        return 0;
    }
    if(sb==0){
        puts("Angry!");
        return 0;
    }
    exgcd(sb,Mod,x,y);
    x=(x+Mod)%Mod;
    write(sa*x%Mod);
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
ll exgcd(ll a,ll b,ll& x,ll& y){
    if(b==0){
        x=1;
        y=0;
        return a;
    }
    ll now=exgcd(b,a%b,y,x);
    y=y-a/b*x;
    return now;
}
