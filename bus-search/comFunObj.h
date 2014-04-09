#ifndef _COMFUNOBJ_
#define _COMFUNOBJ_

#include<string>

using std::string;

struct ltString
	{
		bool operator()(const string& s1, const string& s2) const
		{
			return (s1.compare(s2) < 0 );
		}
	};

#endif // _COMFUNOBJ_
