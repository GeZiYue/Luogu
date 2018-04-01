#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
char pre[30],mid[30],ans[30];
int len,fin[30];
void gwork(int n,int l1,int l2);
int main(){
    int n,i;
    scanf("%s",mid+1);
    scanf("%s",pre+1);
    n=strlen(mid+1);
    for(i=1;i<=n;i++){
        fin[mid[i]-'A']=i;
    }
    gwork(n,1,1);
    for(i=1;i<=n;i++){
        putchar(ans[i]);
    }
    return 0;
}
void gwork(int n,int l1,int l2){
    if(n==1){
        ans[++len]=pre[l1];
        return;
    }
    if(n<=0){
        return;
    }
    int p=fin[pre[l1]-'A']-l2;
    gwork(p,l1+1,l2);
    gwork(n-p-1,l1+p+1,l2+p+1);
    ans[++len]=pre[l1];
    return;
}
