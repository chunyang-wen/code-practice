/*************************************************************
 Problem 1036
 Long Sum
 Time Limit: 1000ms
 Memory Limit: 65536kb
 Description
 A and B are both integers, which have at most 300 decimal
 digits. Please calculate their sum.
 Input
 Each line of the input contains two decimal integers A and
 B separated with a space character. (0<=A,B<10^300)
 Output
 For each line of input, print the value of A+B in decimal
 form on a line by itself.
 Sample Input
 1 1
 1234567890 10000000010

 Sample Output
 2
 11234567900 
 **************************************************************/

#include<iostream>
#include<string>
using namespace std;


int main() {
	
	string left,right;
	while (cin >> left >> right) {
		unsigned lenA = left.size();
		unsigned lenB = right.size();
		char carry = 0;
        if (lenA < lenB) {
            string c = left;
            left = right;
            right = c;
            unsigned tmp = lenA;
            lenA = lenB;
            lenB = tmp;
        }
        
        while (lenB) {
            char tmp = left[lenA - 1] + right[lenB - 1] -
                             48 - 48 + carry;
            if (tmp > 9) {
                left[lenA - 1] = tmp%10 + 48;
                carry = 1;
            }
            else {
                left[lenA - 1] = tmp + 48;
                carry = 0;
            }
            lenA--;
            lenB--;
        }
        while (lenA) {
            if (carry) {
                char tmp = left[lenA - 1] - 48 + carry;
                if (tmp > 9) {
                    left[lenA - 1] = tmp%10 + 48;
                    carry = 1;
                }
                else {
                    carry = 0;
                    left[lenA - 1] = tmp + 48;
                }
            }
            else {
                break;
            }
            lenA--;
        }
        if(lenA == 0) {
            if (carry) {
                cout<<'1'<<left<<endl;
            }
            else {
                cout<<left<<endl;;
            }
        }
        else {
            cout<<left<<endl;
        }
	}
	// system("pause");
	return 0;
}