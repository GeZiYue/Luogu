#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
#define Int(a) read(a)
int gcd(int a,int b);
void read(int &r_e_a_d);
bool t[4005][4005];
int a[205],b[205];
int main(){
    int n,x,y,z,i,j,ans=0;
    bool f1=0,f2=0;
    Int(n);
    for(i=1;i<=n;i++){
        Int(a[i]);
        Int(b[i]);
    }
    for(i=1;i<=n;i++){
        for(j=i+1;j<=n;j++){
            x=a[i]-a[j];
            y=b[i]-b[j];
            if(x==0){
                if(y==0){
                    continue;
                }else{
                    if(f1==0){
                        f1=1;
                        ans++;
                    }
                    continue;
                }
            }else{
                if(y==0){
                    if(f2==0){
                        f2=1;
                        ans++;
                    }
                    continue;
                }else{
                    z=gcd(x,y);
                    x/=z;
                    y/=z;
                    if(t[x+2000][y+2000]==0){
                        t[x+2000][y+2000]=1;
                        ans++;
                    }
                }
            }
        }
    }
    cout<<ans<<endl;
}
int gcd(int a,int b){
    if(b==0){
        return a;
    }else{
        return gcd(b,a%b);
    }
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
