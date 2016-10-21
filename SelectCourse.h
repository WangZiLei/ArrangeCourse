#ifndef SELECTCOURSE_H_INCLUDED
#define SELECTCOURSE_H_INCLUDED

#include <iostream>
#include <vector>

class CourseInfo{
	friend bool OutputToFile(const std::vector<std::vector<CourseInfo>> &result,std::string outputFilePath);
	friend std::vector<std::vector<CourseInfo>> DeleteCourseYouNotHave(const std::vector<std::vector<CourseInfo>> &courseHasBeenSorted,
															const std::vector<std::string> &courseYouWant);
	friend bool CourseHasConflict(const std::vector<CourseInfo> &courseSelected,
					const std::vector<int> &courseIndex,
					const std::vector<CourseInfo> &allCourse);
	friend std::vector<std::vector<CourseInfo>> CirculateCourse(const std::vector<CourseInfo> &courseSelected,
													const std::vector<std::string> &courseYouWant,
													const std::vector<std::vector<int>> &courseIndexArg,
													const std::vector<CourseInfo> &allCourse);
	friend bool DoubleCourseHasConflict(const CourseInfo &courseA,const CourseInfo &courseB);
	friend void SummarizeCourse(std::vector<std::vector<CourseInfo>> &courseSorted,const std::vector<CourseInfo> &allCourse);
private:
	std::string courseName; //课程名称
	std::string teacherName; //老师名字
	std::string credit; //学分
	std::vector<std::string> vCourseTime; //上课时间 如：10304，即周一的第三四节课
	std::vector<std::string> vCourseWeek; //上课周次 如：0117，即从第一周到第十七周
public:
	CourseInfo();
	CourseInfo(const CourseInfo &p);

	std::string getCourseName()const;
	std::string getTeacherName()const;
	std::string getCredit()const;
	std::vector<std::string> getCourseTime()const;
	std::vector<std::string> getCourseWeek()const;

	//courseTimeArg 例如： 7-18,7-18 30304,50304
	bool Set(std::string courseName,std::string teacherName,
					std::string credit,std::string courseTime,std::string courseWeek);
	void Show()const;
	bool isConflictWith(const CourseInfo &theCourse)const;
};

//读取文件,读入到指定变量，此函数一般测试的时候使用
int ReadFromFile(std::vector<CourseInfo> &vCourseInfo,std::string filePath);

//返回指定字符在字符串中出现的次数
int GetCharShowTime(std::string str,char c);

//将周数信息进行分割
void WeekInfoCut(std::vector<std::string> &WeekInfo,std::string str);

//把所有的课程按照学科进行整理,courseSorted存放的是课程索引
void SummarizeCourse(std::vector<std::vector<CourseInfo>> &courseHasBeenSorted,const std::vector<CourseInfo> &allCourse);

//将已选课程和要选的课程进行比较，检查课程是否冲突
//有冲突返回真，没有冲突返回假
//courseIndex是包含了你要选的课的集合（每门科目只有一节课）
bool CourseHasConflict(const std::vector<CourseInfo> &courseSelected,
					const std::vector<int> &courseIndex,
					const std::vector<std::vector<CourseInfo>> &courseHasBeenSorted);

//提供已选择的课程和你要选的课程名称
//返回所有可行的课程安排
std::vector<std::vector<CourseInfo>> CirculateCourse(const std::vector<CourseInfo> &courseHasBeenSelected,
													const std::vector<std::vector<CourseInfo>> &courseHasBeenSorted);

//CirculateCourse()函数需要的一个小功能模块
//循环完了返回真，没有循环完返回假
bool isCirculateOver(const std::vector<std::vector<CourseInfo>> &courseHasBeenSorted,const std::vector<int> &courseIndexYouSelect);

//将courseIndexCirculated自动加一
void NextArrangement(std::vector<int> &courseIndexCirculated,const std::vector<std::vector<CourseInfo>> &courseHasBeenSorted);

//去掉那些你不用上的课程
std::vector<std::vector<CourseInfo>> DeleteCourseYouNotHave(const std::vector<std::vector<CourseInfo>> &courseHasBeenSorted,
															const std::vector<std::string> &courseYouWant);

//吧结果输出到文件
bool OutputToFile(const std::vector<std::vector<CourseInfo>> &result,std::string outputFilePath);

#endif // SELECTCOURSE_H_INCLUDED
