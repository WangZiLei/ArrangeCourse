#include <iostream>
#include <fstream>
using namespace std;

int main(){

	std::ofstream out; //�����ļ�
	out.open("C:\\Users\\WangZiLei\\Desktop\\ѡ�ι���\\testwrite.txt");
	if(!out)
		cout<<"Failed to write file"<<endl;
	out<<"123";
	out.close();

	return 0;
}



