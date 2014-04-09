#include <iostream>
using namespace std;

// efficient exponentiation without recursion
long pow(long x, int n)
{
	if (n == 0) return 1;
	long res = x;
	long ext = 1;
	while (n > 0)
	{
		if (n == 1) return res*ext;
		if (n % 2 != 0)
		{
			ext *= x;
		}
		res = res*res;
		n = n/2;
	}
}

// efficient exponentiation with recursion
long pow_r(long x, int n)
{
    if (n == 0) return 1;
    if (n == 1) return x;
    if (n % 2 == 0) return pow_r(x*x,n/2);
    else return pow_r(x*x,n/2) * x;
}

int main()
{
	cout<<pow(2,4)<<endl;
	cout<<pow(3,5)<<endl;
}