#include <iostream>
#include <sstream>
#include <string>

using namespace std;

string encode(const string& str) {
    int prev = -1;
    int count = 0;
    ostringstream os;
    for (const char c: str) {
        if (prev == -1) {
            prev = c;
            count = 1;
        } else if (prev == c) {
            ++count;
        } else {
            os << count << (char)prev;
            prev = c;
            count = 1;
        }
    }
    if (count != 0)
        os << count << (char)prev;
    return os.str();
}

void test() {
    cout << encode("AABBCDEF") << endl;
    cout << encode("ABBBBCCDDDEEEF") << endl;
    cout << encode("") << endl;
}

int main() {
    test();
    return 0;
}
