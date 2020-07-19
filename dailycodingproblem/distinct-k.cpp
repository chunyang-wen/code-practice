#include <iostream>
#include <string>
#include <map>

using namespace std;

int longest_substring(const string& s, int k) {
    map<char, int> m;
    int i = 0, j = 0;
    int result = -1;
    int size = s.size();
    while (j < size) {
        if (m.size() == k) {
            if (m.find(s[j]) == m.end()) {
                while (m.size() >= k) {
                    m[s[i]]--;
                    if (m[s[i]] == 0) {
                        m.erase(s[i]);
                    }
                    ++i;
                }
            }
        }
        ++m[s[j]];
        ++j;
        result = max(result, j - i);
    }
    return result;
}

int main() {

    cout << longest_substring("abcba", 2) << endl;
    cout << longest_substring("abbba", 2) << endl;

    return EXIT_SUCCESS;
}
