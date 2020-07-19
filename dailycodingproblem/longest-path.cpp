#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>
#include <string>

using namespace std;

enum class Type {
    File = 0,
    Folder = 1,
};

struct Path {
    string name;
    Type type;
    int indent;
    int length;
    Path(Type t, int ind, int len, string n): type(t), indent(ind), length(len), name(n) {}
};

bool contains(const string& s, char c) {
    for (char ss: s) {
        if (c == ss) return true;
    }
    return false;
}

int parse(const string& s) {
    if (s.empty()) return 0;
    int max_size = 0;
    vector<Path> st;
    int i = 0;
    int indent = 0;
    int size = s.size();

    while (i < size) {
        int j = i;
        while (j < size && s[j] != '\n') ++j;
        string sub = s.substr(i, j - i);
        int prev_size = st.empty() ? 0 : st.back().length;
        cout << "name: " << sub << " size: " << sub.size() << " indent: " << indent << endl;
        if (contains(sub, '.')) {
            // a file
            cout << "Find a file: " << sub << endl;
            for (auto p : st) {
                cout << p.name << ":" << p.length << ", ";
            }
            cout << endl;
            max_size = max(max_size, prev_size + (int)sub.size());
        } else {
            // a subdirectory
            while (!st.empty() && st.back().indent >= indent) st.pop_back();
            int prev_size = st.empty() ? 0 : st.back().length;
            Path p(Type::Folder, indent, prev_size + sub.size() + 1, sub);
            cout << "add folder: " << p.length << endl;
            st.push_back(p);
        }

        ++j;
        indent = 0;
        while (j < size && s[j] == '\t') {
            ++j;
            ++indent;
        }
        i = j;
    }

    return max_size;
}

int main() {
    string str = "dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext";
    cout << parse(str) << endl;
    string str1 = "dir";
    cout << parse(str1) << endl;
    string str2 = "dir\n\tdir2";
    cout << parse(str2) << endl;
    return 0;
}

