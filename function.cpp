#include <iostream>
#include <fstream>
#include <vector>
#include "SelectCourse.h"

int ReadFromFile(std::vector<CourseInfo> &vCourseInfo,std::string filePath){
	std::ifstream in; //�����ļ�
	in.open(filePath);
	if(!in){
		std::cout<<"�����ļ�ʧ��"<<std::endl;
		return 1;
	}

	CourseInfo tmp_CourseInfo;

	std::string courseName; //�γ�����
	std::string teacherName; //��ʦ����
	std::string SurplusStuNum;//����ʣ������
	std::string credit; //ѧ��
	std::string CourseTime; //�Ͽ�ʱ�� �磺10304������һ�ĵ����Ľڿ�
	std::string CourseWeek; //�Ͽ��ܴ�

    while(!in.fail()){

		in>>courseName; //�γ�����
		in>>credit; //ѧ��
		in>>SurplusStuNum;//����ʣ������
		in>>teacherName; //��ʦ����
		in>>CourseWeek; //�Ͽ��ܴ�
		in>>CourseTime; //�Ͽ�ʱ�� �磺10304������һ�ĵ����Ľڿ�

		//����γ�ʣ������С��-10���򲻶�ȡ�ÿγ���Ϣ
		if(SurplusStuNum<="-10")
			continue;
		if(tmp_CourseInfo.Set(courseName,teacherName,credit,CourseTime,CourseWeek)){
			vCourseInfo.push_back(tmp_CourseInfo);
			//�ɹ������CourseInfo����֮����������Щ����������
			//�����ڶ����ļ���β��ʱ����ظ��������
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
	//��ǰѧ���Ƿ����
	bool subjectExist=false;
	std::vector<CourseInfo> vTmp;

	for(int i=0;i<allCourse.size();i++){
		subjectExist=false;

		decltype(courseHasBeenSorted.size()) j;
		for(j=0;j<courseHasBeenSorted.size();j++){
			//���allCourse�еĿγ���courseSorted�е�ĳ���γ�������ͬ,��ÿγ̴���
			//ֱ�Ӱɸÿγ̵�������ӽ�courseSorted����
			//������courseSorted�����һ���µ�ѧ�ƣ��ټ���ÿγ�
			if(allCourse[i].courseName==courseHasBeenSorted[j][0].courseName){
				subjectExist=true;
				break;
			}
		}
		//��������´���ŵ��ڶ���for���棬��ô����ÿ�ʼ��ʱ�򲻻ᱻִ��
		//һ��ʼ����ִ�У��ᵼ�¸ô������Զ���ᱻִ��
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

	//����ѡ�γ̺�δѡ�γ̽��жԱ�
	//���γ��Ƿ��г�ͻ
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
		//������ý�λ���򽫵�ǰλ��һ��Ȼ��break
		//�����Ҫ��λ���򱾴�ѭ��ʲô������
		//ֱ��������һ��ѭ��������һλ��һ�������ǰ��������
		if((courseHasBeenSorted[i].size()-1)!=courseIndexCirculated[i]){
			courseIndexCirculated[i]++;
			for(int j=i-1;j>=0;j--){
				//��iǰ������λ������
				courseIndexCirculated[j]=0;
			}
			break;
		}
	}
}

bool isCirculateOver(const std::vector<std::vector<CourseInfo>> &courseHasBeenSorted,
					const std::vector<int> &courseIndexYouSelect){
	//��λ�Ƚϣ��������courseIndexArg[i]��courseIndexYouSelect[i]����
	//��ֱ�ӿ����ж�û��ѭ����
	for(int i=0;i<courseHasBeenSorted.size();i++)
		if((courseHasBeenSorted[i].size()-1)!=courseIndexYouSelect[i]){
			return false;
		}
	return true;
}

bool CourseHasConflict(const std::vector<CourseInfo> &courseSelected,
					const std::vector<int> &courseIndex,
					const std::vector<std::vector<CourseInfo>> &courseHasBeenSorted){
	//������ѡ�γ�֮��û�г�ͻ
	//�Ƚ���ѡ�γ̺�Ҫѡ�γ̽��м��
	//���γ��Ƿ��ͻ
	for(int i=0;i<courseSelected.size();i++)
		for(int j=0;j<courseIndex.size();j++)
			//����γ��г�ͻ��ֱ�ӷ�����
			if(courseSelected[i].isConflictWith(courseHasBeenSorted[j][courseIndex[j]]))
				return true;

	//�������Ƚ�Ҫѡ�γ��Լ�֮����û�г�ͻ
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
	outputFileStream<<"һ����"<<result.size()<<"�ַ�����"<<std::endl<<std::endl;

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




