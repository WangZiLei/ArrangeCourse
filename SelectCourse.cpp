#include <iostream>
#include <fstream>
#include <vector>
#include "SelectCourse.h"

#define DEBUG_MODE

std::string CourseInfo::getCourseName()const{
	return courseName;
}
std::string CourseInfo::getTeacherName()const{
	return teacherName;
}
std::string CourseInfo::getCredit()const{
	return credit;
}
std::vector<std::string> CourseInfo::getCourseTime()const{
	return vCourseTime;
}
std::vector<std::string> CourseInfo::getCourseWeek()const{
	return vCourseWeek;
}

void CourseInfo::Show()const{
	std::cout<<"课程名称:"<<courseName<<"  老师:"<<teacherName<<"  学分:"<<credit<<std::endl;
	for(int i=0;i<vCourseTime.size();i++){
		std::cout<<"上课时间 "<<(i+1)<<" 周次 "<<vCourseWeek[i]<<" 上课时间 "<<vCourseTime[i]<<std::endl;
	}
}

CourseInfo::CourseInfo(){
	courseName="";
	teacherName="";
	credit="0";
	vCourseTime.clear();
	vCourseWeek.clear();
}

CourseInfo::CourseInfo(const CourseInfo &p){
	courseName=p.courseName;
	teacherName=p.teacherName;
	credit=p.credit;
	vCourseTime=p.vCourseTime;
	vCourseWeek=p.vCourseWeek;
}

bool CourseInfo::Set(std::string courseName,std::string teacherName,
					std::string credit,std::string courseTime,std::string courseWeek){
	if(courseName==""||teacherName==""||credit==""||courseTime==""||courseWeek=="")
		return false;
	//清空vector中的元素
	vCourseTime.clear();
	vCourseWeek.clear();

	this->courseName=courseName;
	this->teacherName=teacherName;
	this->credit=credit;

	//将课程时间进行其分段
	//少数课程上课时间是这样的：501020304
	//目前暂时不支持这一种课程
	for(int i=0;i<courseTime.length();i+=6){
		vCourseTime.push_back(courseTime.substr(i,5));
	}

	//将周数进行分段
	WeekInfoCut(vCourseWeek,courseWeek);
	return true;
}

void WeekInfoCut(std::vector<std::string> &WeekInfo,std::string str){
	int beginIndex=0,endIndex;
	std::string tmp;
	do{
		endIndex=str.find(',',beginIndex+1);
		//若课表中只有一个时间，则find函数返回一个非常大的值
		if(endIndex>str.length())
			endIndex=str.length();
		tmp=str.substr(beginIndex,endIndex-beginIndex);
		//把周次信息更换成0716这种形式
		if(tmp.length()==3){
			//如果str是1-7这种形式的
			tmp.erase(1,1);
			tmp.insert(0,"0");
			tmp.insert(2,"0");
		}else if(tmp.length()==4){
			//如果是9-16这种形式
			tmp.erase(1,1);
			tmp.insert(0,"0");
		}else{
			//如果str是11-17这种形式
			tmp.erase(2,1);
		}
		WeekInfo.push_back(tmp);
		beginIndex=endIndex+1;
	}while(endIndex<str.length()-1);

}

bool CourseInfo::isConflictWith(const CourseInfo &theCourse)const{
	//课程A，B分别有几个上课时间
	int timeNumA=vCourseTime.size(),timeNumB=theCourse.vCourseTime.size();
	//课程A，B的开始和结束周数
	std::string courseABeginWeek,courseAEndWeek,courseBBeginWeek,courseBEndWeek;
	//课程A，B在周几上课，从第几节课开始，到第几节课
	std::string courseAWeekDay,courseABeginTime,courseAEndTime;
	std::string courseBWeekDay,courseBBeginTime,courseBEndTime;

	for(int i=0;i<timeNumA;i++){
		for(int j=0;j<timeNumB;j++){
			courseABeginWeek=vCourseWeek[i].substr(0,2);
			courseAEndWeek=vCourseWeek[i].substr(2,2);
			courseBBeginWeek=theCourse.vCourseWeek[i].substr(0,2);
			courseBEndWeek=theCourse.vCourseWeek[i].substr(2,2);

			courseAWeekDay=vCourseTime[i].substr(0,1);
			courseABeginTime=vCourseTime[i].substr(1,2);
			courseAEndTime=vCourseTime[i].substr(3,2);
			courseBWeekDay=theCourse.vCourseTime[i].substr(0,1);
			courseBBeginTime=theCourse.vCourseTime[i].substr(1,2);
			courseBEndTime=theCourse.vCourseTime[i].substr(3,2);


			if(courseABeginWeek>courseBEndWeek||courseAEndWeek<courseBBeginWeek)
				//如果两个课程的上课周数完全没有交集，那么这两个课一定没有冲突
				continue;
			else{
				//如果两个课程的上课周数有交集，则比较每周的上课时间
				if(courseAWeekDay!=courseBWeekDay)
					//如果两个课程在周几不一样，则一定没有冲突
					continue;
				else{
					if(courseABeginTime>courseBEndTime||courseAEndTime<courseBBeginTime)
						//如果在同一天的课程上课时间没有交集，则没有冲突
						continue;
					else
						return true;;
				}
			}
		}
	}
	return false;
}



