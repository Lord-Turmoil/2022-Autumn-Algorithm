/********************************************************************
** T2 - Interval Tree
*/

#include <cstdio>
#include <algorithm>
#include <vector>

// For dynamic memory allocation.
const size_t BLOCK_SIZE = 65536;

// MOD for fibonacci sequence.
const long long MOD = 1000000007;

/*
**+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
** Interval Tree Region
**+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
*/
struct Interval
{
	int left;
	int right;

	Interval() {}	// trivial
	Interval(int _left, int _right) : left(_left), right(_right) {}
};

struct Node
{
	Node* left;
	Node* right;
	Interval key;

	Node()
	{
		left = right = nullptr;
	}

	bool isLeaf() const { return (!left) && (!right); }
};

// memory allocator
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
** Implementation of interval tree. I couldn't find any reference, so
** I realised it by myself.
**
** The basic idea of this is quite similar to segment tree, but its
** leaf stores an interval instead of a point. The value of each node
** is an interval which represents the largest potential interval it
** can cover. But for leaves, it just represent the actual interval
** added to the tree. For example, node A has two child B[4, 10] and
** C[20, 25], then the value of A should be [4, 25].
**
** What's more, it is a complete binary tree, and all leafs' values
** are not overlapping with each other, which is made sure by Insert()
** function.
**
** Let there be N intervals, since it has a structure of a binary tree,
** so I guess its time complexity of insert and delete is O(logN), and
** memory complexity is at least O(2N).
**
** Here, we assume that all intervals are closed, including left and
** right point.
*/
class IntervalTree
{
public:
	IntervalTree() : m_root(nullptr) {}

	// Insert an interval into the tree.
	void Insert(Interval interval);
	// Remove an interval from the tree.
	void Remove(Interval interval);
	// Search if a point is within any interval of the tree.
	bool WithinSearch(int index);

	// For debug purpose. Show the tree in in-order.
	void Show();

private:
	bool _WithinSearch(Node* root, int index);
	void _Insert(Node*& root, Interval interval);
	void _Remove(Node*& root, Interval interval);

	void _Show(Node* root);

	// Some utility functions.
	static inline int	_Intersect(const Interval& i1, const Interval& i2);
	static inline int	_IntersectLoose(const Interval& i1, const Interval& i2);
	static inline bool	_Within(const Interval& i1, int index);

	Node* m_root;	// Root of the tree.
	BlockAllocator<Node> m_alloc;	// Memory allocator.
};

void IntervalTree::Insert(Interval interval)
{
	if (!m_root)
	{
		m_root = m_alloc.Allocate();
		m_root->key = interval;
		return;
	}

	_Insert(m_root, interval);
}

void IntervalTree::Remove(Interval interval)
{
	if (m_root)
		_Remove(m_root, interval);
}

bool IntervalTree::WithinSearch(int index)
{
	if (m_root)
		return _WithinSearch(m_root, index);
	return false;
}

void IntervalTree::Show()
{
	printf("In-Order: ");
	if (m_root)
	{
		_Show(m_root);
		putchar('\n');
	}
	else
		printf("Empty\n");
}

bool IntervalTree::_WithinSearch(Node* root, int index)
{
	if (root->isLeaf())
		return _Within(root->key, index);

	/*
	** Its a complete binary tree, so non-leaf node must
	** have two children. And as stated above, their
	** intervals are not overlapping with each other.
	*/
	if (_Within(root->key, index))
	{
		if (_Within(root->left->key, index))
			return _WithinSearch(root->left, index);
		else if (_Within(root->right->key, index))
			return _WithinSearch(root->right, index);

		return false;
	}

	return false;
}

/********************************************************************
** Insert an interval to the interval tree. It will do some extra
** merge to simplify the tree, or to maintain the form of a complete
** binary tree.
*/
void IntervalTree::_Insert(Node*& root, Interval interval)
{
	/*
	** Since the values are integer, so [1, 3] and [4, 5]
	** should be merged to [1, 5].
	*/
	int ret = _IntersectLoose(root->key, interval);

	if (ret < 0)
	{
		/*
		** interval doesn't overlap with the current node, so
		** a new leaf has to be added, and another new node is
		** needed as their parent.
		*/
		Node* node = m_alloc.Allocate();
		node->key = interval;
		Node* newRoot = m_alloc.Allocate();
		newRoot->key.left = interval.left;
		newRoot->key.right = root->key.right;

		newRoot->left = node;
		newRoot->right = root;

		root = newRoot;
	}
	else if (ret > 0)
	{
		/*
		** Similar to the case above.
		*/
		Node* node = m_alloc.Allocate();
		node->key = interval;
		Node* newRoot = m_alloc.Allocate();
		newRoot->key.left = root->key.left;
		newRoot->key.right = interval.right;

		newRoot->left = root;
		newRoot->right = node;

		root = newRoot;
	}
	else
	{
		/*
		** The interval overlaps with the current node, which is
		** more complicated.
		*/
		if (root->isLeaf())
		{
			root->key.left = std::min(root->key.left, interval.left);
			root->key.right = std::max(root->key.right, interval.right);
		}
		else
		{
			/*
			** The interval is sure to be added, so the value of the
			** current node has to update to the largest potential
			** interval. But if the interval totally covers the current
			** node, then the subtree of the current node can all merge
			** into one node.
			*/
			Interval key = root->key;
			if ((interval.left <= key.left) && (key.right <= interval.right))
			{
				root->key = interval;
				root->left = nullptr;
				root->right = nullptr;
				return;
			}

			/*
			** Since the value of node is already the potentially largest,
			** so it doesn't need later modification.
			*/
			root->key.left = std::min(root->key.left, interval.left);
			root->key.right = std::max(root->key.right, interval.right);

			int retLeft = _IntersectLoose(root->left->key, interval);
			int retRight = _IntersectLoose(root->right->key, interval);
			if ((retLeft == 0) && (retRight == 0))
			{
				/*
				** interval connects.
				*/
				if (root->left->isLeaf() && root->right->isLeaf())
				{
					// Two leaves can merge to one node.
					root->left = root->right = nullptr;
				}
				else
				{
					/*
					** In this case the merge becomes complicated, so
					** we just split the interval to insert them seperately.
					*/
					_Insert(root->left, Interval(interval.left, root->right->key.left - 1));
					_Insert(root->right, Interval(root->right->key.left, interval.right));
				}
			}
			else if (retLeft == 0)	// Overlaps only with left child.
				_Insert(root->left, interval);
			else if (retRight == 0)	// Overlaps only with right child.
				_Insert(root->right, interval);
			else
			{
				/*
				** Overlaps with no child, then new node must be added.
				** However, this can be treated as case "ret != 0" above.
				** Here, a little optimization? To make the new potential
				** interval smaller.
				*/
				if ((interval.right - root->left->key.left) < \
					(root->right->key.right - interval.left))
				{
					_Insert(root->left, interval);
				}
				else
					_Insert(root->right, interval);
			}
		}
	}
}

void IntervalTree::_Show(Node* root)
{
	printf("[%d, %d] ", root->key.left, root->key.right);

	if (!root->isLeaf())
	{
		_Show(root->left);
		_Show(root->right);
	}
}


/********************************************************************
** Remove the interval from the interval tree.
*/
void IntervalTree::_Remove(Node*& root, Interval interval)
{
	int ret = _Intersect(root->key, interval);

	// If not overlapping
	if (ret != 0)
		return;

	Interval key = root->key;

	// The whole node is removed.
	if ((interval.left <= key.left) && (key.right <= interval.right))
	{
		root = nullptr;
		return;
	}

	if (root->isLeaf())
	{
		if (interval.left <= key.left)
		{
			// Only remove the left part.
			root->key.left = interval.right + 1;
		}
		else if (interval.right >= key.right)
		{
			// Only remove the right part.
			root->key.right = interval.left - 1;
		}
		else
		{
			/*
			** Remove middle part, node is split to two.
			** This can be done by adding two children.
			*/
			Node* left = m_alloc.Allocate();
			left->key.left = key.left;
			left->key.right = interval.left - 1;
			Node* right = m_alloc.Allocate();
			right->key.left = interval.right + 1;
			right->key.right = key.right;
			root->left = left;
			root->right = right;
		}
	}
	else
	{
		/*
		** The case that two children are all removed only occurs
		** when the whole node is removed, so here, it is impossible
		** to remove both children.
		*/
		if (_Intersect(root->left->key, interval) == 0)
			_Remove(root->left, interval);
		if (_Intersect(root->right->key, interval) == 0)
			_Remove(root->right, interval);

		if (!root->left || !root->right)
		{
			/*
			** There must be at least one not nullptr. So if
			** one child is removed completely, then it can just
			** be the other one.
			*/
			if (root->left)
				root = root->left;
			else
				root = root->right;
		}
		else
		{
			/*
			** If both children are ok, it should update its
			** interval since it may shorten a little.
			*/
			root->key.left = root->left->key.left;
			root->key.right = root->right->key.right;
		}
	}
}

/********************************************************************
** If i1 and i2 are overlapping with each other, then return 0.
** If i2 is on the left of i1, return -1.
** If i2 is on the right of i1, return 1.
*/
int IntervalTree::_Intersect(const Interval& i1, const Interval& i2)
{
	if (i2.right < i1.left)
		return -1;
	if (i2.left > i1.right)
		return 1;
	return 0;
}

/********************************************************************
** Loose check will take [1, 5], [6, 10] as overlapping.
*/
int	IntervalTree::_IntersectLoose(const Interval& i1, const Interval& i2)
{
	if (i2.right < i1.left - 1)
		return -1;
	if (i2.left > i1.right + 1)
		return 1;
	return 0;
}

/********************************************************************
** Check if one point is within an interval or not.
*/
bool IntervalTree::_Within(const Interval& interval, int index)
{
	return (interval.left <= index) && (index <= interval.right);
}


/*
**+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
** Fibonacci Region
**+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
*/
// Use matrix exponentiation to calculate fibonacci quickly.
struct Matrix
{
	long long a, b;
	long long c, d;

	Matrix operator*(const Matrix& m)
	{
		Matrix ret;

		ret.a = (a * m.a + b * m.c) % MOD;
		ret.b = (a * m.b + b * m.d) % MOD;
		ret.c = (c * m.a + c * m.c) % MOD;
		ret.d = (c * m.b + c * m.d) % MOD;

		return ret;
	}
};

Matrix qpow(Matrix m, int p)
{
	Matrix ret;

	ret.a = ret.d = 1;
	ret.b = ret.c = 0;

	while (p > 0)
	{
		if (p & 1)
			ret = ret * m;
		m = m * m;
		p >>= 1;
	}

	return ret;
}

int fib(int x)
{
	Matrix m;

	m.a = 0;
	m.b = 1;
	m.c = 1;
	m.d = 1;

	return (int)qpow(m, x).b;
}


/*
**+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
** Main function.
**+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
*/
int main()
{
	int n, m;
	int op;
	int left, right;
	int x, y;
	IntervalTree tree;

	/*
	** n is the how many intervals are previously stored in
	** the tree.
	** m is the operation num.
	*/
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++)
	{
		scanf("%d %d", &left, &right);
		tree.Insert(Interval(left, right));
	}

	for (int i = 0; i < m; i++)
	{
		scanf("%d", &op);
		if (op == 1)		// Insert
		{
			scanf("%d %d", &left, &right);
			tree.Insert(Interval(left, right));
		}
		else if (op == 2)	// Delete
		{
			scanf("%d %d", &left, &right);
			tree.Remove(Interval(left, right));
		}
		else if (op == 3)	// Modify
		{
			scanf("%d %d", &left, &right);
			scanf("%d %d", &x, &y);
			tree.Remove(Interval(left, right));
			tree.Insert(Interval(fib(x), fib(y)));
		}
		else if (op == 4)	// Search
		{
			scanf("%d", &x);
			if (tree.WithinSearch(x))
				printf("true\n");
			else
				printf("false\n");
		}
		else				// Show
			tree.Show();
	}

	return 0;
}

/*
********** Sample input **********
0 12
1 1 5
5
1 10 15
5
1 20 25
5
1 6 9
5
2 21 22
5
2 0 100
5
********** Sample output **********
In-Order: [1, 5]
In-Order: [1, 15] [1, 5] [10, 15]
In-Order: [1, 25] [1, 15] [1, 5] [10, 15] [20, 25]
In-Order: [1, 25] [1, 15] [20, 25]
In-Order: [1, 25] [1, 15] [20, 25] [20, 20] [23, 25]
In-Order: Empty
*/
