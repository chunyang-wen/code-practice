#include <algorithm>
#include<iostream>
#include <string>
#include <vector>
#include <set>
#include <functional>

using namespace std;

vector<string> combinations_of_words(const set<string>& dict, const string& str) {
    vector<string> result;

    int min_len = INT_MAX, max_len = INT_MIN;
    for_each(begin(dict), end(dict), [&](const string& s) {
        min_len = min(min_len, static_cast<int>(s.size()));
        max_len = max(max_len, static_cast<int>(s.size()));
    });

    cout << "min_len: " << min_len << " max_len: " << max_len << endl;
    vector<bool> cache(str.size()+1, true);

    function<bool(int)> split = [&](int start) {

        if (start >= str.size()) return true;

        int limit = min(start + max_len, static_cast<int>(str.size()));
        cout << "limit: " << limit << endl;
        for (int i = start + min_len; i <= limit; ++i) {
            string cur = str.substr(start, i - start);
            cout << "i: " << i << " cur: " << cur << endl;
            if (dict.find(cur) == dict.end() || !cache[i]) {
                cout << "bad: " << cur << endl;
                cache[i] = false;
                continue;
            }
            result.push_back(cur);
            if (split(i)) {
                return true;
            }
            cache[i] = false;
            result.pop_back();
        }
        return false;
    };

    split(0);

    return result;
}

int main() {

    set<string> dict {"quick", "brown", "the", "fox"};
    auto x = combinations_of_words(dict, "thequickbrownfox");
    copy(begin(x), end(x), ostream_iterator<string>(cout, ","));
    cout << endl;

    set<string> dict1 {"bedd", "bath", "bedbath", "and", "beyond"};
    auto xx = combinations_of_words(dict1, "bedbathandbeyond");
    copy(begin(xx), end(xx), ostream_iterator<string>(cout, ","));
    cout << endl;


    return 0;
}
