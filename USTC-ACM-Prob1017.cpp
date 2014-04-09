/**
 * Using the requirements that the problem supplies.
 * Be careful with some extreme cases: such as a tree with no nodes,  multiple trees.
 * Build the tree and find the root and then test the requirements.
 * @author : Chunyang Wen
 */

#include <iostream>
#include <vector>
#include <map>
#include <utility>

using namespace std;

/*
struct Node
{
	int id;
	bool visited;
};

struct Com_Node
{
	bool operator()(const Node &lhs, const Node &rhs)
	{
		return lhs.id < rhs.id;
	}
};
*/

/*typedef vector<Node> Neigh;*/

typedef map<int, pair<bool, vector<int> > > Tree;

int build_tree(Tree &tree)
{
	int cur_id;
	int neigh_id;
	while(1)
	{
		cin>>cur_id;
		cin>>neigh_id;

		if(!(cur_id | neigh_id))
			break;
		if (cur_id == -1)
			return -2;

		if (tree.find(cur_id) == tree.end())
		{
			tree[cur_id] = make_pair(false, vector<int>());
		}

		if (tree.find(neigh_id) == tree.end())
		{
			tree[neigh_id] = make_pair(false, vector<int>());
		}

		tree[cur_id].second.push_back(neigh_id);
		tree[neigh_id].first = true;
	}

	Tree::iterator ite_b = tree.begin();
	Tree::iterator ite_e = tree.end();
	int cur_root = -1;
	int next_root = -1;
	while (ite_b != ite_e)
	{
		if (!ite_b->second.first)
		{
			next_root = cur_root;
			cur_root = ite_b->first;
		}
		ite_b->second.first = false;
		++ite_b;
	}

	if (next_root != -1)
	{
		return -1;
	}
	else if (cur_root == -1)
	{
		return -1;
	}
	else
	{
		return cur_root;
	}


}

bool is_a_tree(Tree &tree, int root)
{

	tree[root].first = true;
	vector<int> first_level = tree[root].second;
	if(first_level.size() == 0)
		return true;
	
	vector<int>::iterator ite_b = first_level.begin();
	vector<int>::iterator ite_e = first_level.end();

	while (ite_b != ite_e)
	{
		if(tree[*ite_b].first == true)
			return false;

		bool sub_level = is_a_tree(tree, *ite_b);
		if (!sub_level)
			return false;
		++ite_b;
			
	}
	return true;
}

int main()
{
	Tree tree;
	int root;
	int i = 1;
	while (1)
	{
		root = build_tree(tree);

		if (-2 == root)
			return 0;
		else if (tree.empty())
			cout<<"Case "<<i<<" is a tree."<<endl;	
		else if (-1 == root)
			cout<<"Case "<<i<<" is not a tree."<<endl;
		else
		{
			if (is_a_tree(tree, root))
				cout<<"Case "<<i<<" is a tree."<<endl;
			else
				cout<<"Case "<<i<<" is not a tree."<<endl;
		}
		tree.clear();
		++i;
	}

	int c = 3;
	const int x = c;

	return 0;
}