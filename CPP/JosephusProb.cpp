#include <iostream>
#include <deque>

// solve the problem of Josephus problem
using namespace std;

void JosephusProbSolver(int people, int passTimes)
{
	deque<int> JosephusCircle;

	int ii = 0;
	for (ii = 0; ii < people; ++ii)
	{
		JosephusCircle.push_back(ii+1);
	}
	ii = 1;
	deque<int>::iterator dBegin = JosephusCircle.begin();
	deque<int>::iterator dEnd   = JosephusCircle.end();
	while (!JosephusCircle.empty())
	{

		
		while (ii < passTimes)
		{
			++dBegin;
			if (dBegin == dEnd)
			{
				dBegin = JosephusCircle.begin();
			}
			++ii;
		}
		ii = 1;
		cout<<*dBegin<<endl;
		if (dBegin + 1 == dEnd)
		{
			JosephusCircle.erase(dBegin);
			dBegin = JosephusCircle.begin();
		}
		else
		dBegin = JosephusCircle.erase(dBegin);
		dEnd   = JosephusCircle.end();
	}
}

int JosephusProbSolver1(int people, int passTimes)
{
	int ii = 0;
	int jj = 2;
	while (jj <= people)
	{
		ii =  (ii + passTimes) % jj;
		++jj;
	}
	return ii + 1;
}

int JosephusProbSolver2(int people, int passTimes)
{
	int nn = 0;
	if (1 == people)
		nn =  1;
	else
	{
		nn = (JosephusProbSolver2(people-1,passTimes) + people - 1)%passTimes + 1;
	}
	// cout<<nn<<endl;
	return nn;
}

int JosephusProbSolver3(int N, int K)
{
	if (0 == K) return N;
	
	int first = K % N;

	while ( N > 1)
	{
		first = (first + K) % (N-1);
		--N;
	}
	return first;
}

int main()
{
	int N = 9;
	int K = 5;
	cout<<JosephusProbSolver1(N,K)<<endl;
	JosephusProbSolver(N,K);

	return 0;
}