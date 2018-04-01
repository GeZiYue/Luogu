#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<map>
using namespace std;
map<char,int>fin;
char first[10],mid[10],last[10];
int m;
void gwork(int n,int l1,int l2);
int main(){
    int n,i;
    cin>>mid+1;
    cin>>last+1;
    n=strlen(mid+1);
    for(i=1;i<=n;i++){
        fin[mid[i]]=i;
    }
    gwork(n,1,1);
    cout<<first+1<<endl;
    return 0;
}
void gwork(int n,int l1,int l2){
    if(n<=0){
        return;
    }
    int p;
    p=fin[last[l2+n-1]]-l1;
    first[++m]=last[l2+n-1];
    gwork(p,l1,l2);
    gwork(n-p-1,l1+p+1,l2+p);
    return;
}
