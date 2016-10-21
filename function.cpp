#include <iostream>
#include <fstream>
#include <vector>
#include "SelectCourse.h"

int ReadFromFile(std::vector<CourseInfo> &vCourseInfo,std::string filePath){
	std::ifstream in; //读入文件
	in.open(filePath);
	if(!in){
		std::cout<<"读入文件失败"<<std::endl;
		return 1;
	}

	CourseInfo tmp_CourseInfo;

	std::string courseName; //课程名称
	std::string teacherName; //老师名字
	std::string SurplusStuNum;//课堂剩余人数
	std::string credit; //学分
	std::string CourseTime; //上课时间 如：10304，即周一的第三四节课
	std::string CourseWeek; //上课周次

    while(!in.fail()){

		in>>courseName; //课程名称
		in>>credit; //学分
		in>>SurplusStuNum;//课堂剩余人数
		in>>teacherName; //老师名字
		in>>CourseWeek; //上课周次
		in>>CourseTime; //上课时间 如：10304，即周一的第三四节课

		//如果课程剩余人数小于-10，则不读取该课程信息
		if(SurplusStuNum<="-10")
			continue;
		if(tmp_CourseInfo.Set(courseName,teacherName,credit,CourseTime,CourseWeek)){
			vCourseInfo.push_back(tmp_CourseInfo);
			//成功添加完CourseInfo数据之后必须清空这些变量的数据
			//否则在读到文件结尾的时候会重复添加数据
			courseName="";
			credit="";
			SurplusStuNum="";
			teacherName="";
			CourseWeek="";
			CourseTime="";
		}
    }
	return 0;
}

void SummarizeCourse(std::vector<std::vector<CourseInfo>> &courseHasBeenSorted,const std::vector<CourseInfo> &allCourse){
	courseHasBeenSorted.clear();
	//当前学科是否存在
	bool subjectExist=false;
	std::vector<CourseInfo> vTmp;

	for(int i=0;i<allCourse.size();i++){
		subjectExist=false;

		decltype(courseHasBeenSorted.size()) j;
		for(j=0;j<courseHasBeenSorted.size();j++){
			//如果allCourse中的课程与courseSorted中的某个课程名字相同,则该课程存在
			//直接吧该课程的索引添加进courseSorted即可
			//否则，在courseSorted中添加一个新的学科，再加入该课程
			if(allCourse[i].courseName==courseHasBeenSorted[j][0].courseName){
				subjectExist=true;
				break;
			}
		}
		//如果把以下代码放到第二重for里面，则该代码块该开始的时候不会被执行
		//一开始不被执行，会导致该代码块永远不会被执行
		if(subjectExist){
			courseHasBeenSorted[j].push_back(allCourse[i]);
		}else{
			vTmp.clear();
			vTmp.push_back(allCourse[i]);
			courseHasBeenSorted.push_back(vTmp);
		}
	}
}

std::vector<std::vector<CourseInfo>> DeleteCourseYouNotHave(const std::vector<std::vector<CourseInfo>> &courseHasBeenSorted,
															const std::vector<std::string> &courseYouWant){
	std::vector<std::vector<CourseInfo>> courseHasBeenDelete;

	for(int i=0;i<courseHasBeenSorted.size();i++){
		for(int j=0;j<courseYouWant.size();j++)
			if(courseHasBeenSorted[i][0].courseName==courseYouWant[j]){
				courseHasBeenDelete.push_back(courseHasBeenSorted[i]);
				break;
			}
	}
	return courseHasBeenDelete;
}


std::vector<std::vector<CourseInfo>> CirculateCourse(const std::vector<CourseInfo> &courseHasBeenSelected,
													const std::vector<std::vector<CourseInfo>> &courseHasBeenSorted){

	//将已选课程和未选课程进行对比
	//检查课程是否有冲突
	std::vector<std::vector<CourseInfo>> result;
	std::vector<CourseInfo> resultTmp;
	std::vector<int> courseArrange;

	for(int i=0;i<courseHasBeenSorted.size();i++)
		courseArrange.push_back(0);

	while(!isCirculateOver(courseHasBeenSorted,courseArrange)){
		if(!CourseHasConflict(courseHasBeenSelected,courseArrange,courseHasBeenSorted)){
			resultTmp.clear();
			resultTmp=courseHasBeenSelected;
			for(int i=0;i<courseArrange.size();i++){
				resultTmp.push_back(courseHasBeenSorted[i][courseArrange[i]]);
			}

			result.push_back(resultTmp);
		}
		NextArrangement(courseArrange,courseHasBeenSorted);
	}

	return result;
}


void NextArrangement(std::vector<int> &courseIndexCirculated,
					const std::vector<std::vector<CourseInfo>> &courseHasBeenSorted){
	for(int i=0;i<courseIndexCirculated.size();i++){
		//如果不用进位，则将当前位加一，然后break
		//如果需要进位，则本次循环什么都不做
		//直接跳到下一次循环，将下一位加一，并清空前面所有数
		if((courseHasBeenSorted[i].size()-1)!=courseIndexCirculated[i]){
			courseIndexCirculated[i]++;
			for(int j=i-1;j>=0;j--){
				//将i前面所有位数清零
				courseIndexCirculated[j]=0;
			}
			break;
		}
	}
}

bool isCirculateOver(const std::vector<std::vector<CourseInfo>> &courseHasBeenSorted,
					const std::vector<int> &courseIndexYouSelect){
	//逐位比较，如果发现courseIndexArg[i]和courseIndexYouSelect[i]不等
	//则直接可以判断没有循环完
	for(int i=0;i<courseHasBeenSorted.size();i++)
		if((courseHasBeenSorted[i].size()-1)!=courseIndexYouSelect[i]){
			return false;
		}
	return true;
}

bool CourseHasConflict(const std::vector<CourseInfo> &courseSelected,
					const std::vector<int> &courseIndex,
					const std::vector<std::vector<CourseInfo>> &courseHasBeenSorted){
	//假设已选课程之间没有冲突
	//先将已选课程和要选课程进行检查
	//看课程是否冲突
	for(int i=0;i<courseSelected.size();i++)
		for(int j=0;j<courseIndex.size();j++)
			//如果课程有冲突，直接返回真
			if(courseSelected[i].isConflictWith(courseHasBeenSorted[j][courseIndex[j]]))
				return true;

	//接下来比较要选课程自己之间有没有冲突
	for(int i=0;i<courseIndex.size()-1;i++)
		for(int j=i+1;j<courseIndex.size();j++)
			if(courseHasBeenSorted[i][courseIndex[i]].isConflictWith(courseHasBeenSorted[j][courseIndex[j]]))
				return true;
	return false;
}

bool OutputToFile(const std::vector<std::vector<CourseInfo>> &result,std::string outputFilePath){
	std::ofstream outputFileStream;
	outputFileStream.open(outputFilePath);
	if(!outputFileStream)
		return false;
	outputFileStream<<"一共有"<<result.size()<<"种方案："<<std::endl<<std::endl;

	for(auto &iTemp:result){
		for(auto &jTemp:iTemp){
			outputFileStream<<jTemp.getCourseName()<<" "
            <<jTemp.getTeacherName()<<" "<<jTemp.getCredit()<<"  ";
            for(decltype(jTemp.vCourseTime.size()) k=0;k!=jTemp.vCourseTime.size();k++){
				outputFileStream<<jTemp.vCourseWeek[k]<<" "<<jTemp.vCourseTime[k]<<" ";
            }
            outputFileStream<<std::endl;
		}
		outputFileStream<<std::endl;
	}
	outputFileStream.close();
	return true;
}




