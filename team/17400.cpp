#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstdlib>
#include<algorithm>
#include<queue>
using namespace std;
class Node{
public:
    bool flag[505][505];
    int x,y;
    int sum;
    int k;
    Node(int n,int m,int i,int j,int s){
        int k1,k2;
        for(k1=1;k1<=n;k1++){
            for(k2=1;k2<=m;k2++){
                flag[k1][k2]=0;
            }
        }
        flag[i][j]=1;
        sum=s;
        k=1;
        x=i;
        y=j;
    }
};
int xx[10]={0,0,0,1,-1};
int yy[10]={0,1,-1,0,0};
int a[505][505];
queue<Node>q;
int main(){
    int n,m,t,i,j,mini=2147483647,x,y,ans=0;
    cin>>n>>m>>t;
    for(i=1;i<=n;i++){
        for(j=1;j<=m;j++){
            cin>>a[i][j];
            ans+=a[i][j];
            Node l(n,m,i,j,a[i][j]);
            q.push(l);
        }
    }
    while(!q.empty()){
        if(q.front().k>t){
            break;
        }
        Node l(q.front());
        q.pop();
        if(l.k==t){
            mini=min(mini,l.sum);
        }
        for(i=1;i<=4;i++){
            x=l.x+xx[i];
            y=l.y+yy[i];
            if(x<1||y<1||x>n||y>n||l.flag[x][y]){
                continue;
            }else{
                Node gn(l);
                gn.x=x;
                gn.y=y;
                gn.flag[x][y]=1;
                gn.sum+=a[x][y];
                gn.k++;
                q.push(gn);
            }
        }
    }
    cout<<ans-mini<<endl;
}
