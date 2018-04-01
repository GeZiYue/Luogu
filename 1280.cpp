#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<fstream>
using namespace std;
//ifstream fin(".in");
//ofstream fout(".out");
class work{
public:
	void in_i_x(){
		cin>>i_x;
	}
	void in_i_y(){
		cin>>i_y;
	}
	int get_i_x(){
		return i_x;
	}
	int get_i_y(){
		return i_y;
	}
private:
	int i_x;
	int i_y;
}a[10005];
bool cmp1(work a,work b){
	return a.get_i_x()<b.get_i_x();
}
int main(){
	int i,n,k,j,dp[10005]={0};
	cin>>n>>k;
	for(i=1;i<=k;i++){
		a[i].in_i_x();
		a[i].in_i_y();
	}
	sort(a+1,a+k+1,cmp1);
	dp[n+1]=0;
	j=k;
	for(i=n;i>=1;i--){
		if(i==a[j].get_i_x()){
			for(;i==a[j].get_i_x();j--){
				dp[i]=max(dp[i],dp[i+a[j].get_i_y()]);
			}
		} else{
			if(i!=a[j].get_i_x()){
				dp[i]=dp[i+1]+1;
			}
		}
	}
	cout<<dp[1]<<endl;
	//fin.close;
	//fout.close;
	return 0;
}