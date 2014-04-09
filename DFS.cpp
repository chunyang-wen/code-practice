/*****************************************************************************
 * a depth-first-search algorithm is implemented
 * the input is ajacent list description of the graph
 * author: Zebras Wen
 * date: 2012.10.06
 * version: 0.0
 * reference:
 *****************************************************************************/
 
 #include<iostream>
 #include<cstdlib>
 #include<ctime>
 #include<fstream>
 #include<string>
 using namespace std;

 template<class T>
 class Node;

 template<class T>
 class Graph;

 template<class T>
 struct NeighNode {
	 Node<T>** nextNode;
	 NeighNode<T>* nextNeigh;
 };

 #define _DEBUG_ 0
 // #undef _DEBUG_

 template<typename T>
 class Node {
 private:
    T data; // data of the node
	struct NeighNode<T>* head;
    int label;
    bool isVisited;
    // string nodeName;
 public:
    Node(T data, Node<T>** next, bool isVisited, int label) {
        this->data = data;
        this->isVisited = isVisited;
        this->label = label;
		// struct next
		head = new NeighNode<T>();
		if (next == NULL) {
			head->nextNeigh = NULL;
			head->nextNode = NULL;
		}
		else {
			NeighNode<T>* neigh = new NeighNode<T>();
			// head->nextNode = NULL;
			head->nextNeigh = neigh;
			neigh->nextNeigh = NULL;
			neigh->nextNode = next;
		}
    }
    Node() {
    }
    
    /**
     * set label of current node.
     */
    void setLabel(int label) {
        this->label = label;
    }
    
    /**
     * get the current label.
     */
    int getLabel() {
        return label;
    }
    
    /**
     * get next unvisited neighbor.
     */
    Node<T>** getNeighbor() {
		NeighNode<T>* tmp = head->nextNeigh;
		while (NULL != tmp) {
			if ((*(tmp->nextNode))->isVisited) {
				tmp = (tmp)->nextNeigh;
            }
            else {
                break;
            }
			// tmp = tmp->nextNeigh;
        }
		if (tmp != NULL && (*(tmp->nextNode)) != NULL) {
			(*(tmp->nextNode))->isVisited = true;
		}
        return tmp == NULL ?NULL:(tmp->nextNode);
    }
    
    /**
     * reset the neighbor after reading neighbors
     */
    void resetNeighbor() {
		NeighNode<T>* tmp = head->nextNeigh;
		while (NULL != (tmp)) {
			(*(tmp->nextNode))->isVisited = false;
			tmp = tmp->nextNeigh;
		}
        #ifdef _DEBUG_
        cout<<"reseted"<<endl;
        #endif
    }
    /**
     * add a neighbor to current node.
     */
    void addNeighbor(Node<T>** neighbor) {
		struct NeighNode<T>* neigh = head;
		while (neigh->nextNeigh != NULL ){
			neigh = neigh->nextNeigh;
		}
		NeighNode<T>* neighNode = new NeighNode<T>();
		neigh->nextNeigh = neighNode;
		neighNode->nextNode = neighbor;
		neighNode->nextNeigh = NULL;
    }
    /**
     * get its parent.
     */
    Node<T>** getPrev() {
        return this->prev;
    }
    
    /**
     * operator =
     */
     Node<T>& operator=(Node<T>* node) {
        this->data = node->data;
        this->isVisited = node->isVisited;
        this->next = node->next;
        this->label = node->label;
        this->prev = node->prev;
     }
     
     ~Node() {
        // delete the struct
        NeighNode<T>* tmp = head->nextNeigh;
        while (NULL != tmp) {
            #ifdef _DEBUG_
            cout<<"delete neigh"<<endl;
            #endif
            NeighNode<T>* tmp1 = tmp;
            tmp = tmp->nextNeigh;
            delete tmp1;
        }
        delete head;
		head = NULL;
        #ifdef _DEBUG_
        cout<<"delete neigh"<<endl;
        #endif
     }
    
 };
 
 template<class T>
 class Graph {
 private:
    int nodeNum;
    Node<T>** graph;
 public:
    /**
     * the txt file to store the node.
     * the following is the format of the txt file.
     * nodeNum
     * startNode endNode
     */
    Graph(string addr) {
        ifstream in(addr.c_str());
        if (NULL == in) {
            cerr<<"error reading file"<<endl;
            exit(1);
        }
        // reading data in the ajacent list
        in>>nodeNum;
        #ifdef _DEBUG_
        cout<<"nodeNum: "<<nodeNum<<endl;
        #endif
        graph = new Node<T>*[nodeNum+1];
		for (int ii = 0; ii < nodeNum + 1; ii++) {
			*(graph+ii) = NULL;
		}
        int nodeName;
        int nodeNeighbor;
        int i = 0;
        while (!in.eof() ) {
            in>>nodeName;
            in>>nodeNeighbor;
            #ifdef _DEBUG_
            cout<<"nodeName: "<<nodeName<<endl;
            cout<<"neighbor: "<<nodeNeighbor<<endl;
            #endif
            // Node(T data, Node<T>* next, bool isVisited, int label)
			if (0 == nodeNeighbor) {
				*(graph+nodeName) = new Node<T>(nodeName, NULL, 
                                              false, 0);
				continue;
			}
            else if (*(graph+nodeName) == NULL) {
                *(graph+nodeName) = new Node<T>(nodeName, (graph + nodeNeighbor), 
                                              false, 0);
            }
            else {
                (*(graph+nodeName))->addNeighbor((graph+nodeNeighbor));
            }
            i++;
            #ifdef _DEBUG_
            cout<<"i: "<<i<<endl;
            #endif
        }       
        #ifdef _DEBUG_
        cout<<"read successful"<<endl;
        #endif
        in.close();
    }
    
    void DFS() {
    }
    
    void printLabel() {
    }
    
    void printNode() {
        if (0 == nodeNum) {
            return;
        }
        for (int i = 1; i< nodeNum+1; i++) {
            // cout<<(*(graph+i))->getLabel()<<" ";
            printNode(i);
        }
        cout<<endl;
    }
    
    // print the neighbor of node i
    void printNode(int i) {
        // static bool reset = false;
        cout<<"Node: "<<i<<endl;
        // if (reset) {
            // (*(graph + i))->resetNeighbor();
            // reset = !reset;
        // }
        Node<T>** tmp = (*(graph + i))->getNeighbor();
        // reset = !reset;
        while ((tmp) != NULL) {
            cout<<(*tmp)->getLabel()<<" ";
            tmp = (*(graph + i))->getNeighbor();
        }
        cout<<endl;
		(*(graph + i))->resetNeighbor();
    }
    
    ~Graph() {
        for (int i = 0; i< nodeNum + 1; i++) {
            delete *(graph+i);
            #ifdef _DEBUG_
            cout<<"delete graph"<<endl;
            #endif
        }
        delete[]graph;
		graph = NULL;
    }
 };
 
 
 
 int main(int argc, char* argv[]) {
    Node<int>* testNode = new Node<int>(1, NULL, false, 1000);
	Node<int>* testNode1 = new Node<int>(1, NULL, false, 1001);
    Node<int>* neighNode = new Node<int>(2, NULL, false, 1000);
    neighNode->addNeighbor(&testNode);
	neighNode->addNeighbor(&testNode1);
    cout<<(*(neighNode->getNeighbor()))->getLabel()<<endl;
    string addr_str = "D:\\tmp\\graph.txt";
    // char* addr = "D:\\test\\graph.txt";
    Graph<int> graph(addr_str);
    graph.printNode(3);
    graph.printNode();
    // cerr<<"shit"<<endl;
    delete testNode;
    delete testNode1;
    delete neighNode;
    return EXIT_SUCCESS;
 }
 
 
 