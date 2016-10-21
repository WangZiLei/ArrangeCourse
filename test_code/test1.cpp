#include <iostream>
using namespace std;

class A{
public:
	int *p;
	int n;
};

int main(){
	A tmp[2];
	tmp[1].p=new int[6];
	tmp[1].n=6;
	tmp[0].p=new int[6];
	tmp[0].n=6;


	for(int i=0;i<6;i++)
		tmp[1].p[i]=i;
	for(int i=0;i<6;i++)
		tmp[0].p[i]=i+6;

	for(int i=0;i<6;i++)
		cout<<" "<<tmp[1].p[i];
	cout<<endl;
	for(int i=0;i<6;i++)
		cout<<" "<<tmp[0].p[i];

	return 0;
}
