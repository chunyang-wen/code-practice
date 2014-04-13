
/**
 * Solve it using the standard equation, that a smaller difference should be reached
 * each time.
 * Be careful about the output format and extreme cases.
 * Either one is zero, second is the factor of the first one, equal.
 * Take of the case of ceil and floor function when the argument is integer
 * itself.
 */

#include <iostream>
#include <cmath>

using namespace std;

int gcd(int lhs, int rhs)
{
	if (lhs == rhs)
		return lhs;
	while(rhs)
	{
		lhs ^= rhs;
		rhs ^= lhs; /* rhs = lhs */
		lhs ^= rhs; /* lhs = rhs */
		rhs %= lhs;
	}
	return lhs;
}

int main()
{
	int a,b; /* input two numbers */
	int divisor;
	int nom, den;

	int nom_next, den_next; // 

	int nom_1, nom_2;

	double prev;
	double next;

	// int up_limit;
	// int down_limit;
	bool is_last = false;

	while (cin>>a>>b)
	{
		if (is_last)
			cout<<endl;
		is_last = true;

		if (a== 0 || b == 0)
		{
			cout<<a<<"/"<<b<<endl;
			continue;
		}
		else if (a == b)
		{
			cout<<1<<"/"<<1<<endl;
			continue;
		}

		divisor = gcd(a,b);
		a /= divisor;
		b /= divisor;

		if (b == 1)
		{
			cout<<a<<"/"<<b<<endl;
			continue;
		}

		den = 1;
		if( (a%b) > (b>>1) )
		{
			nom = a/b + 1;
		}
		else
			nom = a/b == 0?1:a/b;
		cout<<nom<<"/"<<den<<endl;
		for (den_next = 2; den_next < b; ++den_next)
		{
			prev = double(nom) /den;
			next = double(a)/b;
			prev = abs(next - prev);

			nom_1 = (int)ceil(den_next * (next - prev)+0.00001);
			nom_2 = (int)floor(den_next * (next + prev)-0.00001);

			// nom_next = nom > den? den:nom;
			nom_1 = nom_1 < 1?1:nom_1;
			if (nom_2 < nom_1) continue;
			// nom = nom_next;
			den = den_next;
			nom = nom_1;
			cout<<nom<<"/"<<den<<endl;
			
		}
		cout<<a<<"/"<<b<<endl;

	}
	return 0;
}