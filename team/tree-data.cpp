#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstdlib>
#include<algorithm>
#include<fstream>
#include<ctime>
using namespace std;
ofstream out("tree20.in");
int main(){
	int n,k,i;
	srand(time(NULL));
	n=7500;
	k=15000;
	out<<n<<endl;
	for(i=1;i<=n;i++){
		out<<(rand()%k+1)<<' ';
	}
	out<<endl;
	out.close();
	return 0;
}

