#ifndef READFILE_TEST_CPP
#define READFILE_TEST_CPP

#include <iostream>
#include <fstream>
using namespace std;

int main(){

	std::ifstream in; //读入文件
	string path="C:\\Users\\WangZiLei\\Desktop\\选课工具\\resource\\AllCourseInfo\\";
	path+="1";
	path+=".txt";
	in.open(path);
	//C:\Users\WangZiLei\Desktop\选课工具\resource
	if(!in){
		std::cout<<"读入文件失败"<<std::endl;
		return 1;
	}

	std::string str;
    while(getline(in,str)){
		std::cout<<str<<std::endl;
    }
    //std::cout<<str<<std::endl;
	//将每一行数据分解到结构体

	return 0;
}

#endif // READFILE_TEST_CPP


