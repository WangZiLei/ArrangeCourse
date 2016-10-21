#include <iostream>
using namespace std;

int main(){
	int **p,n[2]={1,2};
	p=new int*[2];
	p[0]=new int[1];
	p[1]=new int[2];

	p[0][0]=1;
	p[1][0]=2;
	p[1][1]=3;

	cout<<&p[0][0]<<" "<<&p[0][1]<<endl;
	cout<<" "<<p[0][0]<<" "<<p[1][0]<<endl;
	return 0;
}
