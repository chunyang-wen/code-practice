/**
 * Decypt the number is easy, but it should be noticed that 
 * % operation has a different meaning with built-in operator.
 * @author : Chunyang Wen
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

void char_to_code(const string &code_chars, vector<int> &code_int)
{
	int len = code_chars.length();
	int i = 0;
	while (i < len)
	{
		if (code_chars[i] == '_')
		{
			code_int.push_back(0);
		}
		else if (code_chars[i] == '.')
		{
			code_int.push_back(27);
		}
		else
		{
			code_int.push_back(code_chars[i] - 'a' + 1);
		}
		++i;
	}
}

void code_to_char(const vector<int> &code_int, string &code_chars)
{
	int len = code_int.size();
	int i = 0;
	while (i < len)
	{
		if (code_int[i] == 0)
		{
			code_chars.push_back('_');
		}
		else if (code_int[i] == 27)
		{
			code_chars.push_back('.');
		}
		else
		{
			code_chars.push_back(code_int[i] + 'a' - 1);
		}
		++i;
	}
	// code_chars.push_back('\0');
}


void untwist(const vector<int> &cipered_code, vector<int> &plain_code, const int &key)
{
	int len = cipered_code.size();
	int i   = 0;
	int cur_code;
	while (i < len)
	{
		cur_code = cipered_code[i];
		cur_code -= (cur_code + i) /28 * 28;
		plain_code[(key*i)%len] = cur_code + i;
		++i;
	}
}

int main()
{
	int key;
	string cipered_text="";
	string plain_text="";
	int cipered_text_len;
	vector<int> cipered_code;
	vector<int> plain_code;
	while(cin>>key)
	{
		if (!key)
			break;
		cin>>cipered_text;
		cipered_text_len = cipered_text.length();

		plain_code.assign(cipered_text_len, 0);

		char_to_code(cipered_text, cipered_code);

		untwist(cipered_code, plain_code, key);

		code_to_char(plain_code, plain_text);

		cout<<plain_text<<endl;

		// clear used space
		cipered_code.clear();
		plain_code.clear();
		plain_text.clear();

	}
	return 0;
}


