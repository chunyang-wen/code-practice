/**
 * problem 1005
 */
 
#include<iostream>

using namespace std;

int main() {
    short N;
    while (cin>>N) {
        if (N == 0) {
            break;
        }
        short paperNum = (N%4 == 0? N>>2:(N>>2)+1);
        cout<< "Printing order for "<<N<<" pages:"<<endl;
        // bool isFront = true;
        for (short ii = 0; ii < (paperNum<<1) && ii < N; ii++) {
            cout<<"Sheet "<<ii/2 + 1<<", ";
            // cout<<(ii%2 == 0? "front: ":"back : ");
            if (ii%2 == 0) {
                if ((paperNum<<2 ) - ii > N) {
                    cout<<"front: Blank, ";
                }
                else {
                    cout<<"front: "<<(paperNum<<2 ) - ii<<", ";
                }
                cout<< ii + 1;
            }
            else {
                // cout<<"back : ";
                cout<<"back : "<< ii + 1<<", ";
                if ((paperNum<<2 ) - ii > N) {
                    cout<<"Blank";
                }
                else {
                    cout<<(paperNum<<2 ) - ii;
                }
            }
            cout<<endl;
        }
    }
    return 0;
}
/*

Printing order for 1 pages:
Sheet 1, front: Blank, 1
Printing order for 14 pages:
Sheet 1, front: Blank, 1
Sheet 1, back : 2, Blank
Sheet 2, front: 14, 3
Sheet 2, back : 4, 13
Sheet 3, front: 12, 5
Sheet 3, back : 6, 11
Sheet 4, front: 10, 7
Sheet 4, back : 8, 9
Printing order for 4 pages:
Sheet 1, front: 4, 1
Sheet 1, back : 2, 3

 */