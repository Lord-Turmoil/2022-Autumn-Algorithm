/********************************************************************
** T2 - Size Balanced Tree
*/

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

#include <cstdio>
#include <algorithm>
#include <vector>

#ifdef INTERNAL
const size_t BLOCK_SIZE = 256;
#else
const size_t BLOCK_SIZE = 65536;
#endif


struct Interval
{
	int left;
	int right;

	Interval() {}
	Interval(int _left, int _right) : left(_left), right(_right) {}
};

struct Node
{
	Node* left;
	Node* right;

	Interval key;
	int upper;      // upper bound

	int size;

	Node()
	{
		left = right = nullptr;
		size = 1;
	}
};

template<typename T>
class BlockAllocator
{
public:
	BlockAllocator()
	{
		m_curPool = new T[BLOCK_SIZE];
		m_nextNode = m_curPool;
		m_pool.push_back(m_curPool);
	}

	~BlockAllocator()
	{
		for (auto pool : m_pool)
			delete[] pool;
	}

	T* Allocate()
	{
		T* node = m_nextNode;
		m_nextNode++;
		if (m_nextNode - m_curPool >= BLOCK_SIZE)
		{
			m_curPool = new T[BLOCK_SIZE];
			m_nextNode = m_curPool;
			m_pool.push_back(m_curPool);
		}
		return node;
	}

private:
	std::vector<T*> m_pool;
	T* m_curPool;
	T* m_nextNode;
};

/********************************************************************
** Sort by the left of interval.
*/
class SBTree
{
public:
	SBTree() : m_root(nullptr), m_size(0) {}

	void Insert(Interval interval) { _Insert(m_root, interval); }
	bool WithinSearch(int index) { return _WithinSearch(m_root, index); }

private:
	bool _WithinSearch(Node* root, int index);
	void _Insert(Node*& root, Interval interval);
	void _Maintain(Node*& root, bool flag);
	void _LeftRotate(Node*& root);
	void _RightRotate(Node*& root);

	Node* m_root;
	int m_size;

	BlockAllocator<Node> m_alloc;
};

bool SBTree::_WithinSearch(Node* root, int index)
{
	if (!root)
		return false;

	int left = root->key.left;
	int right = root->key.right;

	if (left <= index && index <= right)
		return true;

	if (root->left && (index < left))
		return _WithinSearch(root->left, index);
	if (root->right && (index > right))
		return _WithinSearch(root->right, index);

	return false;
}

void SBTree::_Insert(Node*& root, Interval interval)
{
	if (!root)
	{
		root = m_alloc.Allocate();
		root->key = interval;
		root->upper = interval.right;
	}
	else
	{
		Interval key = root->key;
		root->size++;
		if (interval.left < key.left)
		{
			_Insert(root->left, Interval(interval.left, std::min(interval.right, key.left - 1)));
			_Maintain(root, false);
		}
		if (interval.right > key.right)
		{
			_Insert(root->right, interval);
			_Maintain(root, true);
		}
	}
}

void SBTree::_Maintain(Node*& root, bool flag)
{
	if (!flag)  // left has been changed, so only check left
	{
		int ll_size = ((root->left) && (root->left->left)) ? (root->left->left->size) : 0;
		int lr_size = ((root->left) && (root->left->right)) ? (root->left->right->size) : 0;
		int r_size = (root->right) ? (root->right->size) : 0;
		if (ll_size > r_size)
			_RightRotate(root);
		else if (lr_size > r_size)
		{
			_LeftRotate(root->left);
			_RightRotate(root);
		}
		else
			return;
	}
	else		// right has been changed
	{
		int rr_size = ((root->right) && (root->right->right)) ? (root->right->right->size) : 0;
		int rl_size = ((root->right) && (root->right->left)) ? (root->right->left->size) : 0;
		int l_size = (root->left) ? (root->left->size) : 0;
		if (rr_size > l_size)
		{
			_LeftRotate(root);
		}
		else if (rl_size > l_size)
		{
			_RightRotate(root->right);
			_LeftRotate(root);
		}
		else
			return;
	}
	_Maintain(root->left, false);
	_Maintain(root->right, true);
	_Maintain(root, true);
	_Maintain(root, false);
}

void SBTree::_LeftRotate(Node*& root)
{
	Node* newRoot = root->right;
	if (!newRoot)
		return;

	root->right = newRoot->left;
	newRoot->left = root;
	newRoot->size = root->size;

	root->size = 1;
	if (root->left)
		root->size += root->left->size;
	if (root->right)
		root->size += root->right->size;

	root = newRoot;
}

void SBTree::_RightRotate(Node*& root)
{
	Node* newRoot = root->left;

	if (!newRoot)
		return;

	root->left = newRoot->right;
	newRoot->right = root;
	newRoot->size = root->size;

	root->size = 1;
	if (root->left)
		root->size += root->left->size;
	if (root->right)
		root->size += root->right->size;

	root = newRoot;
}

int main()
{
	int n, m;
	int left, right;
	int op, x;
	SBTree tree;
	SBTree dump;

	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++)
	{
		scanf("%d %d", &left, &right);
		tree.Insert(Interval(left, right));
	}

	for (int i = 0; i < m; i++)
	{
		scanf("%d", &op);
		if (op == 1)
		{
			scanf("%d %d", &left, &right);
			tree.Insert(Interval(left, right));
		}
		else if (op == 2)
		{
			scanf("%d %d", &left, &right);
			dump.Insert(Interval(left, right));
		}
		else
		{
			scanf("%d", &x);
			if (tree.WithinSearch(x) && !dump.WithinSearch(x))
				printf("true\n");
			else
				printf("false\n");
		}
	}

	return 0;
}
