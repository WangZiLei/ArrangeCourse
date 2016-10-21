#include <iostream>
using namespace std;

void fun(int **p,int m,int n){
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			cout<<" "<<p[i][j];
		}
	}
}

int** fun2(){
	int **p;
	p=new int*[2];
	p[0]=new int[2];
	p[1]=new int[3];
	p[0][0]=1;
	p[0][1]=2;
	p[1][0]=3;
	p[1][1]=4;
	p[1][2]=5;
	return p;
}

int main(){
	int **p=fun2();

	fun(p,2,3);
	return 0;
}

