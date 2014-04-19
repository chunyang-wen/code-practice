#include<iostream>

using namespace std;

bool check(long coconut,long people) {
	long i;
	for(i=0;i<people;i++) {
		coconut--;
		if(coconut%people!=0||coconut<0) return false;
		coconut=coconut/people*(people-1);
	}
	if(coconut%people!=0) return false;
	return true;
}


int main() {
	long m,n;
	cin>>n;

	while(n>=0) {
		cout<<n<<" coconuts, ";
		for(m=10;m>=2;m--) {
			if(check(n,m)) {
				cout<<m<<" people and 1 monkey"<<endl;
				break;
			}
		}
		if(m==1) cout<<"no solution"<<endl;
		cin>>n;
	}
	return 0;
}