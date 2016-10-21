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
	vector<CourseInfo> CourseInfoTmp,allCourse;
	ReadFromFile(CourseInfoTmp,"C:\\Users\\WangZiLei\\Desktop\\选课工具\\resource\\courseWeHave");
	ReadFromFile(allCourse,"C:\\Users\\WangZiLei\\Desktop\\选课工具\\resource\\courseWeChooseFrom");

	vector<vector<CourseInfo>> courseHasBeenSorted,result,courseHasBeenDelete;
	SummarizeCourse(courseHasBeenSorted,allCourse);

	vector<string> courseYouWant={"数据结构","英语"};
	courseHasBeenDelete=DeleteCourseYouNotHave(courseHasBeenSorted,courseYouWant);
	//PrintTwoDenmensionVector(courseHasBeenDelete);

	result=CirculateCourse(CourseInfoTmp,courseHasBeenDelete);

	OutputToFile(result,"C:\\Users\\WangZiLei\\Desktop\\选课工具\\resource\\result.txt");
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
	ReadFromFile(allCourse,"C:\\Users\\WangZiLei\\Desktop\\选课工具\\resource\\test_3.txt");

	//PrintOneDenmensionVector(allCourse);
	vector<vector<CourseInfo>> courseSorted;
	SummarizeCourse(courseSorted,allCourse);

	vector<string> courseYouWant={"简明医学史","线性代数","复变函数与积分变换"};
	vector<vector<CourseInfo>> result;
	result=DeleteCourseYouNotHave(courseHasBeenSorted,courseYouWant);

}


void ReadFromFileTest(){
	vector<CourseInfo> allCourse;
	ReadFromFile(allCourse,"C:\\Users\\WangZiLei\\Desktop\\选课工具\\resource\\test2.txt");

	//PrintOneDenmensionVector(allCourse);
	SummarizeCourseTest(allCourse);
	cout<<allCourse.size()<<endl;
}

void DeleteCourseYouNotHaveTest(vector<vector<CourseInfo>> &courseHasBeenSorted){
	vector<string> courseYouWant={"简明医学史","线性代数"};
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
		cout<<"循环完毕"<<endl;
	else
		cout<<"循环没有完毕"<<endl;

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
