#include<iostream>
#include<string>
#include<cstring>
#include<algorithm>
// #include<vector>
using namespace std;

int main() {
	// vector<int> myvec(128);
	string str;
	char aa[128];
	memset(ascii,0,128);
	while (cin>>str) {
		int i = 0;
		int j = str.length();
		while (i < j) {
			aa[str[i]]++;
		}
	}
	return 0;
}