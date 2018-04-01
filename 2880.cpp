#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
#define lc(a) (a<<1)
#define rc(a) ((a<<1)|1)
#define inf 2147483647
#define Int(a) read(a)
int maxn[200005],minn[200005];
int a[50005];
void read(int &r_e_a_d);
void write(int w_r_i_t_e);
void build(int n,int L,int R);
int querymax(int n,int nL,int nR,int qL,int qR);
int querymin(int n,int nL,int nR,int qL,int qR);
int main(){
	int n,m,i,x,y;
	Int(n);
	Int(m);
	for(i=1;i<=n;i++){
		Int(a[i]);
	}
	build(1,1,n);
	for(i=1;i<=m;i++){
		Int(x);
		Int(y);
		write(querymax(1,1,n,x,y)-querymin(1,1,n,x,y));
		putchar('\n');
	}
	return 0;
}
void read(int &r_e_a_d){
    int k=0;
    bool flag=0;
    char c;
    while(1){
        c=getchar();
        if(c=='-'){
            flag=1;
            break;
        }
        if(c>='0'&&c<='9'){
            k=c-'0';
            break;
        }
    }
    while(1){
        c=getchar();
        if(c<'0'||c>'9'){
            break;
        }else{
            k=(k<<1)+(k<<3)+c-'0';
        }
    }
    if(flag==1){
        k=-k;
    }
    r_e_a_d=k;
}
void write(int w_r_i_t_e){
    if(w_r_i_t_e<10){
        putchar(w_r_i_t_e+'0');
    }else{
        write(w_r_i_t_e/10);
        putchar(w_r_i_t_e%10+'0');
    }
}
void build(int n,int L,int R){
	if(L==R){
		maxn[n]=minn[n]=a[L];
	}else{
		int M=(L+R)>>1;
		build(lc(n),L,M);
		build(rc(n),M+1,R);
		maxn[n]=max(maxn[lc(n)],maxn[rc(n)]);
		minn[n]=min(minn[lc(n)],minn[rc(n)]);
	}
}
int querymax(int n,int nL,int nR,int qL,int qR){
	if(nL>=qL&&nR<=qR){
		return maxn[n];
	}
	if(nR<qL||nL>qR){
		return -inf;
	}
	int M=(nL+nR)>>1;
	return max(querymax(lc(n),nL,M,qL,qR),querymax(rc(n),M+1,nR,qL,qR));
}
int querymin(int n,int nL,int nR,int qL,int qR){
	if(nL>=qL&&nR<=qR){
		return minn[n];
	}
	if(nR<qL||nL>qR){
		return inf;
	}
	int M=(nL+nR)>>1;
	return min(querymin(lc(n),nL,M,qL,qR),querymin(rc(n),M+1,nR,qL,qR));
}
