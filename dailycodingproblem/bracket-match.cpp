#include <iostream>
#include <string>
#include <stack>
#include <map>

using namespace std;


bool bracket_match(const string& str) {
    stack<char> st;
    map<char, char> m {{')', '('}, {']', '['}, {'}', '{'}};
    for (char c: str) {
        switch (c) {
            case '(':
            case '[':
            case '{':
                st.push(c); break;
            case ')':
            case ']':
            case '}':
                if (st.empty() || st.top() != m[c]) return false;
                st.pop();
                break;
            default:
                break;
        }
    }
    return st.empty();
}

int main() {

    cout << bracket_match("([])[]({})") << endl;
    cout << bracket_match("([)]") << endl;
    cout << bracket_match("((()") << endl;
    return 0;
}
