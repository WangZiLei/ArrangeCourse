#include <iostream>
#include <vector>
#include <string>

using namespace std;
int Test(vector<vector<int>> &a);

int main(){
	vector<vector<int>> b(2);
	Test(b);

	vector<vector<int>> a=b;

	for(int i=0;i<a.size();i++){
		for(int j=0;j<a[i].size();j++){
			cout<<a[i][j]<<" ";
		}
		cout<<endl;
	}

	return 0;
}

int Test(vector<vector<int>> &a){
	//vector<vector<int> > a(2);
	a[0].resize(5);
	a[1].resize(3);
	a[0][4]=9;
	a[1].push_back(6);
	vector<int> t;
	t.push_back(5);
	a.push_back(t);
	a[1][2]=3;


    cout<<endl;
	return 0;
}


