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
#define M_N 30005
#define M_M 5005
#define lowbit(a) (a&(-a))
#define File(a) freopen(a".in","r",stdin),freopen(a".out","w",stdout)
template<class T1>void read(T1 &r_e_a_d);
template<class T1>void write(T1 w_r_i_t_e);
class BIT{
private:
    int Sum[M_N];
    int s;
public:
    BIT(){
        memset(Sum,0,sizeof(Sum));
    }
    friend void GN(int);
    void Update(int,int);
    int Query_Sum(int,int);
    int Query(int);
}Tree;
class Seg{
public:
    int x,y,s;
    friend bool operator<(Seg,Seg);
}a[M_M];
void GN(int);
bool flag[M_N];
int main(){
    int n,m,i,j,ans=0,now;
    read(n);
    read(m);
    GN(n);
    for(i=1;i<=m;i++){
        read(a[i].x);
        read(a[i].y);
        read(a[i].s);
    }
    sort(a+1,a+m+1);
    for(i=1;i<=m;i++){
        now=a[i].s-Tree.Query_Sum(a[i].x,a[i].y);
        now=max(now,0);
        ans+=now;
        for(j=a[i].y;j>=a[i].x&&now;j--){
            if(flag[j]==false){
                flag[j]=true;
                Tree.Update(j,1);
                now--;
            }
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
void BIT::Update(int n,int num){
    int i=n;
    while(i<=s){
        Sum[i]+=num;
        i+=lowbit(i);
    }
}
int BIT::Query(int n){
    int i=n,ans=0;
    while(i>0){
        ans+=Sum[i];
        i-=lowbit(i);
    }
    return ans;
}
int BIT::Query_Sum(int x,int y){
    return Query(y)-Query(x-1);
}
void GN(int n){
    Tree.s=n;
}
bool operator<(Seg i,Seg j){
    if(i.y==j.y){
        return i.x<j.x;
    }else{
        return i.y<j.y;
    }
}
