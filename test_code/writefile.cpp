#include <iostream>
#include <fstream>
using namespace std;

int main(){

	std::ofstream out; //读入文件
	out.open("C:\\Users\\WangZiLei\\Desktop\\选课工具\\testwrite.txt");
	if(!out)
		cout<<"Failed to write file"<<endl;
	out<<"123";
	out.close();

	return 0;
}



