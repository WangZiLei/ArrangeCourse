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
	std::cout<<"�γ�����:"<<courseName<<"  ��ʦ:"<<teacherName<<"  ѧ��:"<<credit<<std::endl;
	for(int i=0;i<vCourseTime.size();i++){
		std::cout<<"�Ͽ�ʱ�� "<<(i+1)<<" �ܴ� "<<vCourseWeek[i]<<" �Ͽ�ʱ�� "<<vCourseTime[i]<<std::endl;
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
	//���vector�е�Ԫ��
	vCourseTime.clear();
	vCourseWeek.clear();

	this->courseName=courseName;
	this->teacherName=teacherName;
	this->credit=credit;

	//���γ�ʱ�������ֶ�
	//�����γ��Ͽ�ʱ���������ģ�501020304
	//Ŀǰ��ʱ��֧����һ�ֿγ�
	for(int i=0;i<courseTime.length();i+=6){
		vCourseTime.push_back(courseTime.substr(i,5));
	}

	//���������зֶ�
	WeekInfoCut(vCourseWeek,courseWeek);
	return true;
}

void WeekInfoCut(std::vector<std::string> &WeekInfo,std::string str){
	int beginIndex=0,endIndex;
	std::string tmp;
	do{
		endIndex=str.find(',',beginIndex+1);
		//���α���ֻ��һ��ʱ�䣬��find��������һ���ǳ����ֵ
		if(endIndex>str.length())
			endIndex=str.length();
		tmp=str.substr(beginIndex,endIndex-beginIndex);
		//���ܴ���Ϣ������0716������ʽ
		if(tmp.length()==3){
			//���str��1-7������ʽ��
			tmp.erase(1,1);
			tmp.insert(0,"0");
			tmp.insert(2,"0");
		}else if(tmp.length()==4){
			//�����9-16������ʽ
			tmp.erase(1,1);
			tmp.insert(0,"0");
		}else{
			//���str��11-17������ʽ
			tmp.erase(2,1);
		}
		WeekInfo.push_back(tmp);
		beginIndex=endIndex+1;
	}while(endIndex<str.length()-1);

}

bool CourseInfo::isConflictWith(const CourseInfo &theCourse)const{
	//�γ�A��B�ֱ��м����Ͽ�ʱ��
	int timeNumA=vCourseTime.size(),timeNumB=theCourse.vCourseTime.size();
	//�γ�A��B�Ŀ�ʼ�ͽ�������
	std::string courseABeginWeek,courseAEndWeek,courseBBeginWeek,courseBEndWeek;
	//�γ�A��B���ܼ��ϿΣ��ӵڼ��ڿο�ʼ�����ڼ��ڿ�
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
				//��������γ̵��Ͽ�������ȫû�н�������ô��������һ��û�г�ͻ
				continue;
			else{
				//��������γ̵��Ͽ������н�������Ƚ�ÿ�ܵ��Ͽ�ʱ��
				if(courseAWeekDay!=courseBWeekDay)
					//��������γ����ܼ���һ������һ��û�г�ͻ
					continue;
				else{
					if(courseABeginTime>courseBEndTime||courseAEndTime<courseBBeginTime)
						//�����ͬһ��Ŀγ��Ͽ�ʱ��û�н�������û�г�ͻ
						continue;
					else
						return true;;
				}
			}
		}
	}
	return false;
}



