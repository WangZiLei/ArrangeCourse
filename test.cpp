#include <iostream>
#include <fstream>
#include <vector>
#include "SelectCourse.h"
using namespace std;

template <typename T>
void PrintOneDenmensionVector(const vector<T> &Vector);
template <typename T>
void PrintTwoDenmensionVector(const vector<vector<T>> &Vector);
void PrintTwoDenmensionVector(const vector<vector<CourseInfo>> &Vector);
void PrintOneDenmensionVector(const vector<CourseInfo> &Vector);
void ReadFromFileTest();
void SummarizeCourseTest(const vector<CourseInfo> &allCourse);
void isCirculateOverTest(const vector<vector<CourseInfo>> &courseHasBeenSorted);
void NextArrangementTest(const vector<vector<CourseInfo>> &courseHasBeenSorted);
void DeleteCourseYouNotHaveTest(vector<vector<CourseInfo>> &courseHasBeenSorted);

int test(){
	vector<CourseInfo> aallCourse;
	string path;
	for(int i=1;i<6;i++){
		path="C:\\Users\\WangZiLei\\Desktop\\ѡ�ι���\\resource\\AllCourseInfo\\";
		char path_tmp=i+'0'-0;

		path+=path_tmp;
		path+=".txt";
		cout<<path<<endl;
		ReadFromFile(aallCourse,path);
	}
	//ReadFromFile(aallCourse,path);
	PrintOneDenmensionVector(aallCourse);

	return 0;

	vector<CourseInfo> CourseInfoTmp,allCourse;
	ReadFromFile(CourseInfoTmp,"C:\\Users\\WangZiLei\\Desktop\\ѡ�ι���\\resource\\courseWeHave.txt");
	ReadFromFile(allCourse,"C:\\Users\\WangZiLei\\Desktop\\ѡ�ι���\\resource\\courseWeChooseFrom.txt");

	PrintOneDenmensionVector(CourseInfoTmp);

	vector<vector<CourseInfo>> courseHasBeenSorted,result,courseHasBeenDelete;
	SummarizeCourse(courseHasBeenSorted,allCourse);

	vector<string> courseYouWant={"���ݽṹ","Ӣ��"};
	courseHasBeenDelete=DeleteCourseYouNotHave(courseHasBeenSorted,courseYouWant);
	//PrintTwoDenmensionVector(courseHasBeenDelete);

	result=CirculateCourse(CourseInfoTmp,courseHasBeenDelete);

	OutputToFile(result,"C:\\Users\\WangZiLei\\Desktop\\ѡ�ι���\\resource\\result.txt");
	//PrintTwoDenmensionVector(result);


	//ReadFromFileTest();
	return 0;
}

void SummarizeCourseTest(const vector<CourseInfo> &allCourse){
	vector<vector<CourseInfo>> courseSorted;
	SummarizeCourse(courseSorted,allCourse);

	//DeleteCourseYouNotHaveTest(courseSorted);
	//PrintTwoDenmensionVector(courseSorted);
	//NextArrangementTest(courseSorted);
	//isCirculateOverTest(courseSorted);
}

void CourseHasConflictTest(const vector<vector<CourseInfo>> &courseHasBeenSorted){

	vector<CourseInfo> allCourse;
	ReadFromFile(allCourse,"C:\\Users\\WangZiLei\\Desktop\\ѡ�ι���\\resource\\test_3.txt");

	//PrintOneDenmensionVector(allCourse);
	vector<vector<CourseInfo>> courseSorted;
	SummarizeCourse(courseSorted,allCourse);

	vector<string> courseYouWant={"����ҽѧʷ","���Դ���","���亯������ֱ任"};
	vector<vector<CourseInfo>> result;
	result=DeleteCourseYouNotHave(courseHasBeenSorted,courseYouWant);

}


void ReadFromFileTest(){
	vector<CourseInfo> allCourse;
	ReadFromFile(allCourse,"C:\\Users\\WangZiLei\\Desktop\\ѡ�ι���\\resource\\test2.txt");

	//PrintOneDenmensionVector(allCourse);
	SummarizeCourseTest(allCourse);
	cout<<allCourse.size()<<endl;
}

void DeleteCourseYouNotHaveTest(vector<vector<CourseInfo>> &courseHasBeenSorted){
	vector<string> courseYouWant={"����ҽѧʷ","���Դ���"};
	vector<vector<CourseInfo>> result;
	result=DeleteCourseYouNotHave(courseHasBeenSorted,courseYouWant);
	PrintTwoDenmensionVector(result);
}

void NextArrangementTest(const vector<vector<CourseInfo>> &courseHasBeenSorted){
	vector<int> courseIndexCirculated={2,2,1,0};
	NextArrangement(courseIndexCirculated,courseHasBeenSorted);
	PrintOneDenmensionVector(courseIndexCirculated);
}


void isCirculateOverTest(const vector<vector<CourseInfo>> &courseHasBeenSorted){
	vector<int> courseIndexYouSelect={2,2,1,1};
	bool result;
	result=isCirculateOver(courseHasBeenSorted,courseIndexYouSelect);
	if(result)
		cout<<"ѭ�����"<<endl;
	else
		cout<<"ѭ��û�����"<<endl;

	for(int i=0;i<courseHasBeenSorted.size();i++)
		cout<<courseHasBeenSorted[i].size()<<" ";

}


template <typename T>
void PrintOneDenmensionVector(const vector<T> &Vector){
	for(int i=0;i<Vector.size();i++)
		cout<<Vector[i]<<" ";
	cout<<endl;
}

template <typename T>
void PrintTwoDenmensionVector(const vector<vector<T>> &Vector){
	for(int i=0;i<Vector.size();i++){
		for(int j=0;j<Vector[i].size();j++)
			cout<<Vector[i][j]<<" ";
		cout<<endl;
	}
}

void PrintTwoDenmensionVector(const vector<vector<CourseInfo>> &Vector){
	for(int i=0;i<Vector.size();i++){
		for(int j=0;j<Vector[i].size();j++)
			Vector[i][j].Show();
		cout<<endl<<endl;
	}
}

void PrintOneDenmensionVector(const vector<CourseInfo> &Vector){
	for(int i=0;i<Vector.size();i++)
		Vector[i].Show();
	cout<<endl<<endl;
}
