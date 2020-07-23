#include <iostream>
#include <string>
#include <functional>

using namespace std;


bool re_match(const string& str, const string& pattern) {

    function<bool(int, int)> match = [&](int start_str, int start_pattern) {

        int str_size = str.size();
        int pattern_size = pattern.size();
        cout << "str_i = " << start_str << " pattern_i = " << start_pattern << endl;
        if (start_str == str_size && start_pattern == pattern_size) {
            return true;
        }
        if (start_pattern >= pattern_size) return false;

        if (start_pattern < pattern_size - 1 && pattern[start_pattern+1] == '*') {
            // meet x*
            bool is_match = match(start_str, start_pattern+2);
            if (is_match) return true;
            for (; start_str < str_size; ++start_str) {
                if (pattern[start_pattern] == '.' || str[start_str] == pattern[start_pattern]) {
                    is_match = match(start_str+1, start_pattern+2);
                } else {
                    break;
                }
                if (is_match) return true;
            }
            return false;
        }

        if (start_str >= str_size) return false;
        if (pattern[start_pattern] == '.' || str[start_str] == pattern[start_pattern]) {
            return match(start_str+1, start_pattern+1);
        }
        return false;
    };

    return match(0, 0);
}

void test(const string& str, const string& pattern) {
    bool matched = re_match(str, pattern);
    cout << "Match: /" << str << "/ -- /" << pattern <<  "/ = " << matched << endl;
}


int main() {

    test("ray", "ra.");
    test("read", "re.");
    test("ra", "raz*");
    test("ra", "ra.*");
    test("rayyy", "ray*");
    test("chat", ".*at");
    test("chatx", ".*h");
    test("chatx", ".*.*");

    return 0;
}
