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
#define N 105
#define File(a) freopen((string(a)+string(".in")).c_str(),"r",stdin),freopen((string(a)+string(".out")).c_str(),"w",stdout)
template<class T1>void read(T1 &r_e_a_d);
template<class T1>void write(T1 w_r_i_t_e);
int DFS(int x,int y);
int a[N][N];
int f[N][N];
int n,m;
int xx[10]={0,1,-1,0,0},yy[10]={0,0,0,1,-1};
int main(){
    int i,j,ans=0;
    read(n);
    read(m);
    for(i=1;i<=n;i++){
        for(j=1;j<=m;j++){
            read(a[i][j]);
        }
    }
    for(i=1;i<=n;i++){
        for(j=1;j<=m;j++){
            ans=max(ans,DFS(i,j)+1);
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
int DFS(int x,int y){
    if(f[x][y]){
        return f[x][y];
    }
    int i,ans=0,nx,ny;
    for(i=1;i<=4;i++){
        nx=x+xx[i];
        ny=y+yy[i];
        if(nx>=1&&ny>=1&&nx<=n&&ny<=m&&a[x][y]>a[nx][ny]){
            ans=max(ans,DFS(nx,ny)+1);
        }
    }
    f[x][y]=ans;
    return ans;
}
