#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<fstream>
using namespace std;
class Node{
public:
    Node(){
        sum=0;
    }
    void scanner();
    void tester();
    void printer();
    bool operator<(Node &i);
private:
    int first,sum,num,test;
    string name;
}a[1005];
int main(){
    int n,i;
    cin>>n;
    for(i=1;i<=n;i++){
        a[i].scanner();
        a[i].tester();
    }
    sort(a+1,a+n+1);
    for(i=1;i<=n;i++){
        a[i].printer();
    }
    return 0;
}
void Node::scanner(){
    int i;
    cin>>this->name>>this->first>>this->sum>>this->num;
    this->sum+=this->first;
    return;
}
void Node::tester(){
    test=200-this->sum*2/3;
    return;
}
void Node::printer(){
    cout<<this->name<<' '<<this->test<<endl;
    return;
}
bool Node::operator<(Node &i){
    if(this->sum==i.sum){
        if(this->first==i.first){
            return this->num<i.num;
        }else{
            return this->first>i.first;
        }
    }else{
        return this->sum>i.sum;
    }
}
