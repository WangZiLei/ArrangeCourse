#ifndef READFILE_TEST_CPP
#define READFILE_TEST_CPP

#include <iostream>
#include <fstream>
using namespace std;

int main(){

	std::ifstream in; //�����ļ�
	string path="C:\\Users\\WangZiLei\\Desktop\\ѡ�ι���\\resource\\AllCourseInfo\\";
	path+="1";
	path+=".txt";
	in.open(path);
	//C:\Users\WangZiLei\Desktop\ѡ�ι���\resource
	if(!in){
		std::cout<<"�����ļ�ʧ��"<<std::endl;
		return 1;
	}

	std::string str;
    while(getline(in,str)){
		std::cout<<str<<std::endl;
    }
    //std::cout<<str<<std::endl;
	//��ÿһ�����ݷֽ⵽�ṹ��

	return 0;
}

#endif // READFILE_TEST_CPP


