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
#define lowbit(x) (x&(-x))
#define N 2050
#define File(a) freopen(a".in","r",stdin),freopen(a".out","w",stdout)
template<class T1>void read(T1 &r_e_a_d);
template<class T1>void write(T1 w_r_i_t_e);
class BIT{
private:
    int sum[N][N];
public:
    int Query(int,int);
    void Update(int,int,int);
}S,Si,Sj,Sij;
int Query(int,int,int,int);
void Update(int,int,int,int,int);
int n,m;
int main(){
    int x1,y1,x2,y2,num;
    char ch;
    cin>>ch;
    read(n);
    read(m);
    while(cin>>ch){
        if(ch=='L'){
            read(x1);
            read(y1);
            read(x2);
            read(y2);
            read(num);
            Update(x1,y1,x2,y2,num);
        }else{
            read(x1);
            read(y1);
            read(x2);
            read(y2);
            write(Query(x1,y1,x2,y2));
            EL;
        }
    }
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
int BIT::Query(int x,int y){
    int ans=0,i,j;
    for(i=x;i;i-=lowbit(i)){
        for(j=y;j;j-=lowbit(j)){
            ans+=sum[i][j];
        }
    }
    return ans;
}
void BIT::Update(int x,int y,int num){
    int i,j;
    for(i=x;i<=n;i+=lowbit(i)){
        for(j=y;j<=m;j+=lowbit(j)){
            sum[i][j]+=num;
        }
    }
}
int Query_One_Point(int x,int y){
    return S.Query(x,y)*(x*y+x+y+1)-Si.Query(x,y)*(y+1)-Sj.Query(x,y)*(x+1)+Sij.Query(x,y);
}
void Update_One_Point(int x,int y,int num){
    S.Update(x,y,num);
    Si.Update(x,y,num*x);
    Sj.Update(x,y,num*y);
    Sij.Update(x,y,num*x*y);
}
int Query(int x1,int y1,int x2,int y2){
    return Query_One_Point(x2,y2)-Query_One_Point(x1-1,y2)-Query_One_Point(x2,y1-1)+Query_One_Point(x1-1,y1-1);
}
void Update(int x1,int y1,int x2,int y2,int num){
    Update_One_Point(x1,y1,num);
    Update_One_Point(x1,y2+1,-num);
    Update_One_Point(x2+1,y1,-num);
    Update_One_Point(x2+1,y2+1,num);
}
