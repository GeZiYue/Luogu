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
#define N 1005
#define GetSum(x1,y1,x2,y2) (sum[x2][y2]-sum[x1-1][y2]-sum[x2][y1-1]+sum[x1-1][y1-1])
#define File(a) freopen(a".in","r",stdin),freopen(a".out","w",stdout)
template<class T1>void read(T1 &r_e_a_d);
template<class T1>void write(T1 w_r_i_t_e);
class Node{
public:
    int num,id;
    friend bool operator<(Node ,Node );
}xs[N],ys[N];
int x[N],y[N];
int sum[N][N];
int main(){
    int n,i,j,k,a,b,c,d,ans;
    read(n);
    for(i=1;i<=n;i++){
        read(xs[i].num);
        read(ys[i].num);
        xs[i].id=ys[i].id=i;
    }
    sort(xs+1,xs+n+1);
    sort(ys+1,ys+n+1);
    for(i=1;i<=n;i++){
        x[xs[i].id]=i;
        y[ys[i].id]=i;
    }
    for(i=1;i<=n;i++){
        sum[x[i]][y[i]]=1;
    }
    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++){
            sum[i][j]+=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];
        }
    }
    ans=n;
    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++){
            ans=min(ans,max(max(GetSum(1,1,i,j),GetSum(1,j+1,i,n)),max(GetSum(i+1,1,n,j),GetSum(i+1,j+1,n,n))));
        }
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
    return i.num<j.num;
}
