#include<iostream>
#include<string>
#include<fstream>
using namespace std;

struct Node {
    Node* prev;
    Node* next;
    bool isPrinted;
    char data;
};

Node* find(Node& node) {
    if (node.next == NULL) {
        return &node;
    }
    Node* tmp = node.next;
	while (tmp->next != NULL) {
		tmp = tmp->next;
	}
	return tmp;
}

void clear(Node& node) {
	Node* tmp = node.next;
	while (tmp != NULL) {
		Node* tmp_next = tmp->next;
		tmp = NULL;
		// tmp->prev = NULL;
		tmp = tmp_next;
		if (tmp != NULL) {
			tmp->prev = NULL;
		}

	}
}


int main() {
	// int len;
	// cin>>len;
	Node a[25]; // moved, the value is set to be -1
    for (char i = 0; i < 25; i++) {
        a[i].prev = NULL;
        a[i].next = NULL;
        a[i].isPrinted = false;
        a[i].data = i;
    }
	string order;
	unsigned short blockNum;
	// unsigned short num;
	bool move_pile; // true for move, false for pile
	bool on_over; // true for on, false for over
	// cin>>blockNum;
	// cin.get();
	ifstream in("order.txt");
	if (in == NULL) {
		exit(0);
	}
	in>>blockNum;
	while (in>>order) {
        // cout<<order<<endl;
		if(order[0] == 'q') {
			break;
		}
		if (order[0] == 'm') {
			move_pile = true;
		}
		else {
			move_pile = false;
		}
		unsigned short block_a;
		in>>block_a;
		in>>order;
		if(order == "onto") {
			on_over = true;
		}
		else {
			on_over = false;
		}
		unsigned short block_b;
		in>>block_b;
		if (find(a[block_a]) == find(a[block_b])) {
			continue;
		}
		if (move_pile && on_over) {
			// a and b clear
			// move a onto b
			clear(a[block_a]);
			clear(a[block_b]);
			if (a[block_a].prev != NULL) {
				a[block_a].prev->next = NULL;
			}
			a[block_b].next = &a[block_a];
            a[block_a].prev = &a[block_b];
			
		}
		else if (move_pile && (!on_over)) {
			// clear a
			// move a to b or blocks containing b
			clear(a[block_a]);
            Node* tmp =  find(a[block_b]);
			// a[block_a] = -1;
			if(a[block_a].prev != NULL) {
				a[block_a].prev->next = NULL;
			}
			a[tmp->data].next = &a[block_a];
            a[block_a].prev = &a[tmp->data];
		}
		else if ((!move_pile) && on_over) {
			// clear b
			// pile a and above to b
			clear(a[block_b]);
			Node* tmp = a[block_b].next;
			if(a[block_a].prev != NULL) {
				a[block_a].prev->next = NULL;
			}
			a[block_b].next = &a[block_a];
            a[block_a].prev = &a[block_b];
		}
		else {
			// pile a and above to b or blocks containing b
			Node* tmp = find(a[block_b]);
            tmp->next = &a[block_a];
			if(a[block_a].prev != NULL) {
				a[block_a].prev->next = NULL;
			}
            a[block_a].prev = &a[block_b];
		}
		
	}

	// in.close();

	for (char i = 0; i < blockNum; i++ ) {
		if (i < 10) {
			cout<<" "<<(unsigned)i<<": ";
		}
		else {
			cout<<(unsigned)i<<": ";
		}

		if (a[i].isPrinted) {
			// cout<<" ";
			cout<<endl;			
			continue;
		}
		if (a[i].prev != NULL) {
			cout<<endl;
			continue;
		}
		// cout<<"  ";
		// cout<<(unsigned)i;
		if (a[i].prev == NULL && a[i].next == NULL) {
			cout<<" "<<(unsigned)(i);
			a[i].isPrinted = true;
			cout<<endl;
			continue;			
		}
		else {
			// char tmp = i;
			cout<<" "<<(unsigned)i;
			// a_bool[i] = true;
            a[i].isPrinted = true;
            Node* tmp = a[i].next;
			while (tmp != NULL) {
				cout<<" "<<(unsigned)(tmp->data);
				tmp->isPrinted = true;
				tmp = tmp->next;
				if (tmp == NULL) {
					cout<<endl;
					break;
				}
			}
			// cout<<(unsigned)tmp<<endl;
			// cout<<endl;
		}
	}
	return 0;
}