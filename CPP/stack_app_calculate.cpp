#include <iostream>
#include <stack>
#include <string>

using namespace std;

/*
 * do the infix and postfix operation
 * calculator using stack
 *
 */
 
// handle string
// format: num + ' '+operate hand
// no space between operator hand
 void infix(string & expr)
 {
	string tmp= expr;
	expr = "";
	char top_char;
	int i = 0;
	int len = tmp.length();
	stack<char> stk_char;
	int left_bracket = 0;
	bool num_flag = false;
	while (i < len)
	{
		if (tmp[i] == ' ')
		{
			++i;
			continue;
		}
		if ('0' <= tmp[i] && tmp[i] <= '9' || tmp[i] == '.')
		{
			expr += tmp[i];
			num_flag = true;
		}
		else
		{
			if (num_flag)
			{
				expr += ' ';
				num_flag = false;
			}
			// decide the prority of the operator
			if (stk_char.empty())
			{
				if (tmp[i] == '(')
				{
					++left_bracket;
				}
				stk_char.push(tmp[i]);
			}
			else
			{
				switch(tmp[i])
				{
					case '(':
						++left_bracket;
						stk_char.push(tmp[i]);
						break;
					case ')':
						if (left_bracket == 0)
						{
							cout<<"brackets not match!"<<endl;
							exit(0);
						}
						// push until left_bracket;
						while (stk_char.top() != '(')
						{
							expr += stk_char.top();
							stk_char.pop();
						}
						stk_char.pop();
						--left_bracket;
						break;
					case '+':
					case '-':
						// push itself when encounter high prority
						top_char = stk_char.top();
						if (top_char == '(' )
							stk_char.push(tmp[i]);
						// push other when encounter low prority
						else
						{							
							while ( top_char == '+' || top_char == '-' || 
							         top_char == '*' || top_char == '/')
							{
								expr += top_char;
								stk_char.pop();
								if (stk_char.empty())
								{
									break;
								}
								top_char = stk_char.top();
							}
							stk_char.push(tmp[i]);
						}
						break;
					case '*':
					case '/':
						// push itself when encounter high prority
						top_char = stk_char.top();
						if (top_char == '(' || top_char == '+' || top_char == '-')
							stk_char.push(tmp[i]);
						// push other when encounter low prority
						else
						{							
							while ( top_char == '*' || top_char == '/')
							{
								expr += top_char;
								stk_char.pop();
								if (stk_char.empty())
								{
									break;
								}
								top_char = stk_char.top();
							}
							stk_char.push(tmp[i]);
						}
						break;
						
						
						
				}
			}
		}
		++i;
	}
	if (expr[expr.length()-1] <='9' && expr[expr.length()-1] >='0')
		expr += ' ';
	while (!stk_char.empty())
	{
		expr += stk_char.top();
		stk_char.pop();
	}
 }

double postfix(string &expr)
 {
	stack<double> stk_double;
	int i = 0;
	int len = expr.length();
	double num_int = 0;
	double num_frac = 0;
	bool isDot = false;
	int index = 1;
	while (i < len)
	{
		// extract number
		if ('0'<=expr[i] && expr[i]<= '9')
		{
			if (isDot)
			{
				num_frac = num_frac * 10 + (expr[i] - '0');
				index *= 10;
			}
			else
			{
				num_int = num_int * 10 + expr[i] - '0';
			}
		}
		
		else if (expr[i] == ' ')
		{
			stk_double.push(num_int + num_frac/index);
			num_int = 0;
			num_frac = 0;
			index = 1;
			isDot = false;
		}
		else if (expr[i] == '.')
		{
			isDot = true;
		}
		else
		{
			/*if ('0'<=expr[i-1] && expr[i-1]<='9')
			{
				stk_double.push(num_int + num_frac/index);
				num_int = 0;
				num_frac = 0;
				index = 1;
				isDot = false;
			}*/
			// else
			{
				num_frac = stk_double.top();
				stk_double.pop();
				num_int = stk_double.top();
				stk_double.pop();
				switch(expr[i])
				{
				case '+':
					stk_double.push(num_int + num_frac); break;
				case '-':
					stk_double.push(num_int - num_frac); break;
				case '*':
					stk_double.push(num_int * num_frac); break;
				case '/':
					if (num_frac < 1e-12)
					{
						cout<<"Divided by zero"<<endl;
						exit(0);
					}
					stk_double.push(num_int / num_frac);break;

				default:
					cout<<"error"; break;		
				}
				num_int = 0;
				num_frac = 0;
			}
		}
		
		// caculate
		++i;
	}
	
	return stk_double.top();
 }

 int main()
 {
	string aa = "1+2.6*(34 + (8*9)/6 + 1) - 5";
	infix(aa);	
	cout<<aa<<endl;
	cout<<postfix(aa)<<endl;
	cout<<1+2.6*(34 + (8*9)/6 + 1) - 5<<endl;
	return 0;
 }