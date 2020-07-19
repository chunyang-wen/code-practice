#include <iostream>
using namespace std;

enum FileType {
    File = 0,
    Directory = 1,
    Link = 2,
    FileTypeCount,
};

enum Access {
    Read = 1,
    Write = 2,
    Exec = 4,
};

enum class NewAccess {
    Read = 8,
    Write = 16,
    Exec = 32,
};

ostream& operator<<(ostream& os, NewAccess na) {
    switch (na) {
        case NewAccess::Read: cout << "Read" << endl; break;
        case NewAccess::Write: cout << "Write" << endl; break;
        case NewAccess::Exec: cout << "Exec" << endl; break;
    }
    return os;
}


int main() {
    cout << FileTypeCount << endl;
    cout << Read << " " << (Read == 1) << endl;
    cout << NewAccess::Read << endl;
    cout << (static_cast<int>(NewAccess::Read) == 8) << endl;
    return 0;
}
