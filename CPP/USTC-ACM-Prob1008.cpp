/**
 * Using containers to store the dictonary.
 * The basic idea is to construct a map between sorted words and words from dictonary.
 * Each query will be sorted in order to find the list of words it can generate.
 * @author : Chunyang Wen
 */

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

struct Comp_string
{
	bool operator()(const string &lhs, const string &rhs)
	{
		int len1 = lhs.length();
		int len2 = rhs.length();
		int i = 0;
		while (i < len1 && i < len2)
		{
			if(lhs[i] < rhs[i])
				return true;
			else if (lhs[i] > rhs[i])
				return false;
			else
				++i;
		}
		if (len1 < len2)
			return true;
		else
			return false;
	}
};


typedef map<string, vector<string>, Comp_string> Dictonary;

void get_dict(Dictonary &dict)
{
	string word;

	while (cin>>word)
	{
		if (word[0] == 'X')
			return;

		string sorted_word;
		sorted_word = word;
		sort(sorted_word.begin(), sorted_word.end());
		if (dict.find(sorted_word) != dict.end() )
			dict[sorted_word].push_back(word);
		else
		{
			dict[sorted_word] = vector<string>();
			dict[sorted_word].push_back(word);
		}
	}
}

void sort_dict(Dictonary &dict)
{
	Dictonary::iterator ite_begin = dict.begin();
	Dictonary::iterator ite_end = dict.end();
	while (ite_begin != ite_end)
	{
		sort(ite_begin->second.begin(),ite_begin->second.end());
		++ite_begin;
	}
}

void print_list(Dictonary &dict, const string &word)
{
	if (dict.find(word) == dict.end())
	{
		cout<<"NOT A VALID WORD"<<endl;
		cout<<"******"<<endl;
		return;
	}
	vector<string> word_list(dict[static_cast<string>(word)]);
	vector<string>::iterator ite_begin = word_list.begin();
	vector<string>::iterator ite_end = word_list.end();
	while (ite_begin != ite_end)
	{
		cout<<*ite_begin<<endl;
		++ite_begin;
	}
	cout<<"******"<<endl;
}


void print_dict(Dictonary &dict)
{
	string word;
	while (cin>>word)
	{
		if (word[0] == 'X')
			return;
		sort(word.begin(), word.end());
		print_list(dict, word);
	}
}


int main()
{
	Dictonary dict;

	get_dict(dict);

	sort_dict(dict);

	print_dict(dict);

	return 0;
}