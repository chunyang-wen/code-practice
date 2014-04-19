/**
 * Normally, a backtrace method is enough to solve the problem.
 * There is another dynamic method provided by google search engine.
 */


#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

const int N = 101;

int combinations[N] = {1,1};

void calc_combinations()
{
	/* dynamic method to get all the combinations can reach within 100 */
	int i = 1;
	int j ;

	while (i < N)
	{
		j = i + 1;
		while ( j < N)
		{
			if (j * i < N)
				++combinations[j*i];
			++j;
		}
		++i;
	}
}

bool is_prime[N] = {false};
void calc_prime_table()
{
	int a[] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,
		73,79,83,89,97};
	for (int i = 0; i < sizeof(a)/sizeof(int); ++i)
		is_prime[a[i]] = true;
}

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

bool calc_factor(long long n, vector<int> &factors)
{
	/* Factorizing asap. */

	/* n is less than 100. */
	if (n <= 100)
	{
		factors.push_back(static_cast<int>(n));
		return true;
	}

	int i = N -1;
	while (i > 1)
	{
		if (n%i)
		{
			--i;
		}
		else
		{
			factors.push_back(i);			
			n /= i;
			--i;
			if(n < 100)
			{
				factors.push_back(static_cast<int>(n));
				return true;
			}
		}
	}
	return false;
}

struct Comp
{
	bool operator()(const int lhs, const int rhs)
	{
		return lhs > rhs;
	}
};

int main()
{
	calc_combinations();
	vector<int> factors1;
	vector<int> factors2;
	vector<int> result;
	vector<int> result_combinations;
	vector<int>::iterator ite_b;
	vector<int>::iterator ite_e;
	vector<int>::iterator ite_b1;
	vector<int>::iterator ite_e1;

	int a,b;
	int i;
	while(cin>>a>>b)
	{
		if ( a < b)
			iter_swap(&a, &b);
		if (a <= 100)
		{
			cout<<a<<endl;
			continue;
		}

		if (!calc_factor(a, factors1))
		{
			cout<<b<<endl;
			factors1.clear();
			continue;
		}
		calc_factor(b, factors2);

		/* now we have intersection of factors1 and factors2, stored in result. */
		set_intersection(factors1.begin(),factors1.end(),factors2.begin(),factors2.end(),back_inserter(result),Comp());

		/* we focus on the small number b. */
		if (result.empty())
		{
			cout<<a<<endl;
			factors1.clear();
			factors2.clear();
			result.clear();
			continue;
		}

		ite_b = result.begin();
		ite_e = result.end();
		ite_e1 = factors2.end();
		int gcd_of_two;
		while (ite_b != ite_e)
		{
			ite_b1 = factors2.begin();
			result_combinations.push_back(combinations[*ite_b]);
			while (ite_b1 != ite_e1)
			{
				if (*ite_b > *ite_b1)
				{
					gcd_of_two = gcd(*ite_b, *ite_b1);
					if (gcd_of_two > 1)
						result_combinations.back() -= combinations[*ite_b/gcd_of_two];
				}

				++ite_b1;
			}
				++ite_b;
		}

		if (*min(result_combinations.begin(), result_combinations.end()) < 2)
			cout<<b<<endl;
		else
			cout<<a<<endl;


		factors1.clear();
		factors2.clear();
		result.clear();
		result_combinations.clear();

	}
	return 0;
}

/*
#include<iostream>
#include<cmath>

using namespace std;

bool check(int a,int b,int from) {
    if(a==1&&b==1) return true;
    if(a<from&&b<from||from>100) return false;
    if(a%from==0) {
        if(check(a/from,b,from+1)) return true;
    }
    if(b%from==0) {
        if(check(a,b/from,from+1)) return true;
    }
    if(check(a,b,from+1)) return true;
    return false;
}

int main() {
    int a,b;
    while(cin>>a>>b) {
        if(!check((a>b?b:a),1,2)||check(a,b,2)) cout<<(a>b?a:b)<<endl;
        else cout<<(a>b?b:a)<<endl;
    }
    return 0;
}
*/

/*
#include <iostream.h>
#include <fstream.h>

#include <iomanip.h>

unsigned* factorList(unsigned n, unsigned& size)
{
  unsigned listSize = 100;
  unsigned* fact = new unsigned[listSize];
  unsigned nFacts = 0;
  fact[nFacts++] = 1;
  unsigned i;
  for (i = 2; i*i <= n; ++i)
    if (n % i == 0)
      {
        if (nFacts == listSize)
          {
            unsigned* old = fact;
            listSize *= 2;
            fact = new unsigned[listSize];
            for (unsigned j = 0; j < nFacts; ++j)
              fact[j] = old[j];
            delete[] old;
          }
        fact[nFacts++] = i;
      }
  {
    unsigned* old = fact;
    listSize = 2*nFacts;
    if (fact[nFacts-1] * fact[nFacts-1] == n)
      --listSize;
    fact = new unsigned[listSize];
    for (unsigned j = 0; j < nFacts; ++j)
      fact[j] = old[j];
    delete[] old;
  }
  for (i = 0; i < nFacts; ++i)
    fact[listSize-1-i] = n/fact[i];
  size = listSize;
  return fact;
}

int main()
{
  ifstream in("gizilch.inp");
  unsigned score1, score2;
  while (in >> score1 >> score2)
    {
      if (score1 > score2)
        { unsigned t = score1; score1 = score2; score2 = t; }

      unsigned size1;
      unsigned* factors1 = factorList(score1, size1);
      unsigned size2;
      unsigned* factors2 = factorList(score2, size2);

      // after num==k, feasible[i,j] is k>0 if the score pair (i,j) is possible
      // with only "grapes" labelled 1 to k (and not 1 to k-1), 0 otherwise
      unsigned tblsize = size1*size2;
      unsigned* feasible = new unsigned[tblsize];
      for (unsigned i = tblsize; i--; )
        feasible[i] = 0;
      feasible[0] = 1;

      unsigned f1next = 0;
      unsigned f2next = 0;

      while (f1next < size1 || f2next < size2)
        {
          unsigned num;
          if (f1next == size1)
            num = factors2[f2next++];
          else if (factors1[f1next] < factors2[f2next])
            num = factors1[f1next++];
          else
            {
              if (factors1[f1next] == factors2[f2next])
                ++f1next;
              num = factors2[f2next++];
            }
          if (num > 100)
            break;

          unsigned k = 0;
          for (unsigned i = 0; i < size1; ++i)
            for (unsigned j = 0; j < size2; ++j, ++k)
              if (feasible[k] && feasible[k] < num)
                // see what new pairs can be validated with grape "num"
                {
                  unsigned ii, f1 = factors1[i]*num;
                  for (ii =  i+1; factors1[ii] != f1 && ii < size1; ++ii)
                    {}
                  if (ii < size1)
                    {
                      unsigned p = ii*size2+j;
                      if (! feasible[p]) feasible[p] = num;
                    }
 
                  unsigned jj, f2 = factors2[j]*num;
                  for (jj =  j+1; factors2[jj] != f2 && jj < size2; ++jj)
                    {}
                  if (jj < size2)
                    {
                      unsigned p = i*size2+jj;
                      if (! feasible[p]) feasible[p] = num;
                    }
                }
          if (feasible[tblsize-1] == num)
            break;
        }

      // see what is possible...
      unsigned winscore;
      if (feasible[tblsize-1])
        winscore = score2;      // both could be honest
      else if (!feasible[(size1-1)*size2])
        winscore = score2;      // 1 definitely lied
      else
        winscore = score1;      // they can't both be honest, so 1 wins
 
      cout << winscore << "\n";
      delete[] feasible;
      delete[] factors2;
      delete[] factors1;
    }
  return 0;
} 
*/
