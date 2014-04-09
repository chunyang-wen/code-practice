
/**
 * It implements the a-star algorithm from wikipedia.
 * It uses mahantan distance as the priority.
 * @author : Chunyang Wen
 */

#include <iostream>
#include <vector>
#include <deque>
#include <cmath>
#include <string>
#include <algorithm>

using namespace std;
const int DIMENSION = 3;

class Board
{
public:

	// initial board
	Board()
	{
		char board[DIMENSION][DIMENSION]={0};
		assign(board);
	}

	void get_board()
	{
		for (int i = 0; i < DIMENSION; ++i)
		{
			for (int j = 0; j < DIMENSION; ++j)
			{
				cin>>board[i][j];
				if (board[i][j] == 'x')
				{
					row = i;
					col = j;
				}
			}
		}
	}

	Board(char board[DIMENSION][DIMENSION])
	{
		assign(board);
	}
	
	Board(const Board& lhs)
	{
		assign(lhs.board);
	}

	Board &operator=(const Board&lhs)
	{
		assign(lhs.board);
		return *this;
	}

	int manhatan_distance()
	{
		// sum of Manhattan distances between blocks and goal
        int manhattanDist = 0;
        for (int i = 0; i < DIMENSION; i++)
		{
            for (int j = 0; j < DIMENSION; j++)
			{
                if ('x' == board[i][j])
				{
                    continue;
                }
                int blockValue = board[i][j] - 1 - '0';

                int row = blockValue / DIMENSION;
                int col = blockValue % DIMENSION;
                manhattanDist = manhattanDist + abs(double(row - i))
                        + abs(double(col - j));

            }
        }
        return manhattanDist;
	}

	const Board get_twin_board()
	{
		// a board obtained by exchanging two adjacent blocks in the same row
		// exchange two blocks in the first row
		char twin_board[DIMENSION][DIMENSION];
		for (int i = 0; i < DIMENSION; i++)
		{
			for (int j = 0; j < DIMENSION; j++)
			{
				twin_board[i][j] = board[i][j];
			}
		}

		for (int i = 0; i < DIMENSION; i++)
		{
			for (int j = 0; j < DIMENSION - 1; j++) 
			{
				if (twin_board[i][j] != 'x' && twin_board[i][j + 1] != 'x') 
				{
					int tmp = twin_board[i][j];
					twin_board[i][j] = twin_board[i][j + 1];
					twin_board[i][j + 1] = tmp;
					return Board(twin_board);
				}
			}
		}
		return Board(twin_board);
	}

	bool isGoal() {
		// is this board the goal board?

		for (int i = 0; i < DIMENSION; i++)
		{
			for (int j = 0; j < DIMENSION; j++)
			{
				if (board[i][j] != 'x'
					&& board[i][j] != (DIMENSION * i + j + 1 + '0'))
				{
						return false;
				}
			}
		}
		return true;
    }

	void exchange_positison(int i, int j)
	{
		int row = this->row;
		int col = this->col;
		this->row = i;
		this->col = j;
		this->board[row][col] = this->board[i][j];
		this->board[i][j] = 'x';
	}

	bool equal(const Board& lhs)
	{
		for (int i = 0; i < DIMENSION; ++i)
		{
			for (int j = 0; j < DIMENSION; ++j)
			{
				if (this->board[i][j] != lhs.board[i][j])
				{
					return false;
				}
			}
		}
		return true;
	}

	void assign(const char board[DIMENSION][DIMENSION])
	{
		for (int i = 0; i < DIMENSION; i++)
		{
			for (int j = 0; j < DIMENSION; j++)
			{
				this->board[i][j] = board[i][j];
				if (board[i][j] == 'x')
				{
					this->row = i;
					this->col = j;
				}
			}
		}
	}
public:
	char board[DIMENSION][DIMENSION];	
	int row;
	int col;
};



struct Node
{
	Board board;
	int priority;
	int moves;
	string previous_moves;
};


struct Comp
{
	bool operator()(const Node *lhs, const Node *rhs)
	{
		return lhs->priority > rhs->priority;
	}
};

typedef vector<Node*> MinPQ;

deque<Node*> neigh(Node* current, Node* previous)
{
	deque<Node*> neighbors;
	
	/* move up */
	if (current->board.row > 0)
	{	
		Node* temp_node = new Node;
		temp_node->board = current->board;	
		temp_node->board.exchange_positison(temp_node->board.row - 1, temp_node->board.col);
		if (!previous || !temp_node->board.equal(previous->board))
		{
			temp_node->previous_moves = current->previous_moves + "u";
			temp_node->moves = current->moves + 1;
			temp_node->priority = temp_node->moves + temp_node->board.manhatan_distance();
			neighbors.push_back(temp_node);
		}
		else
			delete temp_node;
	}

	
	/* move down */
	if (current->board.row < DIMENSION - 1)
	{	
		Node* temp_node = new Node;
		temp_node->board = current->board;	
		temp_node->board.exchange_positison(temp_node->board.row + 1, temp_node->board.col);
		if (!previous || !temp_node->board.equal(previous->board))
		{
			temp_node->previous_moves = current->previous_moves + "d";
			temp_node->moves = current->moves + 1;
			temp_node->priority = temp_node->moves + temp_node->board.manhatan_distance();
			neighbors.push_back(temp_node);
		}
		else
			delete temp_node;
	}

	
	/* move left */
	if (current->board.col > 0)
	{
		Node* temp_node = new Node;
		temp_node->board = current->board;	
		temp_node->board.exchange_positison(temp_node->board.row, temp_node->board.col-1);
		if (!previous || !temp_node->board.equal(previous->board))
		{
			temp_node->previous_moves = current->previous_moves + "l";
			temp_node->moves = current->moves + 1;
			temp_node->priority = temp_node->moves + temp_node->board.manhatan_distance();
			neighbors.push_back(temp_node);
		}
		else
			delete temp_node;
	}

	
	/* move right */
	if (current->board.col < DIMENSION - 1)
	{
		Node* temp_node = new Node;
		temp_node->board = current->board;	
		temp_node->board.exchange_positison(temp_node->board.row, temp_node->board.col+1);
		if (!previous || !temp_node->board.equal(previous->board))
		{
			temp_node->previous_moves = current->previous_moves + "r";
			temp_node->moves = current->moves + 1;
			temp_node->priority = temp_node->moves + temp_node->board.manhatan_distance();
			neighbors.push_back(temp_node);
		}
		else
			delete temp_node;
	}

	return neighbors;

}
template<class Iterator>
bool find(Iterator beg1, Iterator end1, Node* &target)
{
	while (beg1 != end1)
	{
		if((*beg1)->board.equal(target->board))
		{
			target = *beg1;
			return true;
		}
		++beg1;
	}
	return false;
}


void clear(MinPQ &min_pq)
{
	MinPQ::iterator ite_b1 = min_pq.begin();
	MinPQ::iterator ite_e1 = min_pq.end();
	while (ite_b1 != ite_e1)
	{
		delete *ite_b1;

		++ite_b1;
	}
}

bool solve(MinPQ &initial_solver_queue,
		   MinPQ &initial_closed_queue,
		   Node *&current, Node *&previous)
{
	bool is_solve;
	pop_heap(initial_solver_queue.begin(), initial_solver_queue.end(), Comp());
	current = initial_solver_queue.back();

	initial_solver_queue.pop_back();
	initial_closed_queue.push_back(current);

	is_solve = current->board.isGoal();

	if (is_solve) return true;

	/* add neighbors */
	deque<Node*> neighbor = neigh(current, previous);
	Node *temp1, *temp2;
	while (!neighbor.empty())
	{
		temp2 = temp1 = neighbor.front();
		neighbor.pop_front();
		/* found in closed set, continue. */
		if (find(initial_closed_queue.begin(), 
			initial_closed_queue.end(), temp1) )
			continue;

		/* not in open set or has high priority. */
		if (find(initial_solver_queue.begin(),
			initial_solver_queue.end(), temp1))
		{
			/* found! */
			if(temp1->moves > temp2->moves)
			{
				/* update priority */
				temp1->priority = temp2->priority;
				temp1->previous_moves = temp2->previous_moves;
				temp1->moves = temp2->moves;
				make_heap(initial_solver_queue.begin(),
					initial_solver_queue.end(), Comp());
			}
		}
		else
		{
			/* not found! */
			initial_solver_queue.push_back(temp1);
			push_heap(initial_solver_queue.begin(),
				initial_solver_queue.end(), Comp());
		}			
	}
	previous = current;
	return false;
}

int main()
{
	MinPQ initial_solver_queue,twin_solver_queue;
	MinPQ initial_closed_queue,twin_closed_queue;

	Board initial_board;
	initial_board.get_board();
	Board twin_board(initial_board.get_twin_board());

	Node* initial_node = new Node;
	initial_node->board = initial_board;
	initial_node->moves = 0;
	initial_node->previous_moves = "";
	initial_node->priority = initial_board.manhatan_distance() + initial_node->moves;

	Node* twin_node = new Node;
	twin_node->board = twin_board;
	twin_node->moves = 0;
	twin_node->previous_moves = "";
	twin_node->priority = twin_board.manhatan_distance() + twin_node->moves;

	bool is_solve = false,is_solve_twin = false;

	initial_solver_queue.push_back(initial_node);
	twin_solver_queue.push_back(twin_node);

	Node* current, *previous = NULL, *previous_twin = NULL;

	while ( !(is_solve | is_solve_twin) )
	{
		
		is_solve = solve(initial_solver_queue,
			initial_closed_queue, current, previous);

		if (is_solve)
		{
			cout<<current->previous_moves<<endl;
			break;
		}

		is_solve_twin = solve(twin_solver_queue,
			twin_closed_queue, current, previous_twin);
		if (is_solve_twin)
		{
			break;
		}
	}

	if (is_solve_twin)
		cout<<"unsolvable"<<endl;

	/* garbage collection */
	clear(initial_solver_queue);
	clear(initial_closed_queue);
	clear(twin_solver_queue);
	clear(twin_closed_queue);

	return 0;
}