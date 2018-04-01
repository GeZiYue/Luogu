#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<iomanip>
#include<algorithm>
using namespace std;
#define isNum(a) (a>='0'&&a<='9')
#define SP putchar(' ')
#define EL putchar('\n')
#define N 105
#define File(a) freopen((string(a)+string(".in")).c_str(),"r",stdin),freopen((string(a)+string(".out")).c_str(),"w",stdout)
template<class T1>void read(T1 &r_e_a_d);
template<class T1>void write(T1 w_r_i_t_e);
double sum(double x1,double y1,double x2,double y2);
double x[N],y[N];
int main(){
    int n,i;
    double r,ans=0;
    read(n);
    cin>>r;
    ans=2*r*acos(-1);
    for(i=1;i<=n;i++){
        cin>>x[i]>>y[i];
    }
    x[0]=x[n];
    y[0]=y[n];
    for(i=1;i<=n;i++){
        ans+=sum(x[i],y[i],x[i-1],y[i-1]);
    }
    cout<<fixed<<setprecision(2)<<ans<<endl;
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
double sum(double x1,double y1,double x2,double y2){
    return (sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)));
}
