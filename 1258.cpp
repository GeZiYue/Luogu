#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<fstream>
using namespace std;
int main(){
	double a,b,c;
  	scanf("%lf %lf %lf",&a,&b,&c);
  	printf("%.6lf",((b+c)*a/(3*b+c))/c+(a-((b+c)*a/(3*b+c)))/b);
	return 0;
}

