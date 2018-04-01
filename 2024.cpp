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
#define File(a) freopen((string(a)+string(".in")).c_str(),"r",stdin),freopen((string(a)+string(".out")).c_str(),"w",stdout)
#define N 50005
template<class T1>void read(T1 &r_e_a_d);
template<class T1>void write(T1 w_r_i_t_e);
int find(int x);
bool check(int mod,int x,int y);
int fa[N],hod[N];
int main(){
    int n,m,ans=0,i,a,b,c;
    read(n);
    read(m);
    for(i=1;i<=n;i++){
        fa[i]=i;
    }
    for(i=1;i<=m;i++){
        read(a);
        read(b);
        read(c);
        if((max(b,c)>n)||((c==2)&&(b==c))){
            ans++;
        }else{
            ans+=check(a,b,c);
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
        ch=getchar();
        if(ch=='-'){
            flag=-1;
        }
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
int find(int x){
    if(fa[x]==x){
        return x;
    }else{
        int tmp=find(fa[x]);
        hod[x]=(hod[x]+hod[fa[x]])%3;
        return fa[x]=tmp;
    }
}
bool check(int mod,int x,int y){
    int fx=find(x),fy=find(y);
    if(fx!=fy){
        fa[fy]=fx;
        hod[fy]=(hod[x]-hod[y]+3+((mod^1)&1))%3;
        return 0;
    }else{
        if(((hod[y]-hod[x]+3)%3)!=((mod^1)&1)){
            return 1;
        }else{
            return 0;
        }
    }
}
