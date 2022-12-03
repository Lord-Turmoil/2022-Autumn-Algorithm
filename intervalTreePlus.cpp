/********************************************************************
** T2 - Interval Tree
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

const long long MOD = 1000000007;

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

	Node()
	{
		left = right = nullptr;
	}

	bool isLeaf() const { return (!left) && (!right); }
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
class IntervalTree
{
public:
	IntervalTree() : m_root(nullptr) {}

	void Insert(Interval interval);
	void Remove(Interval interval);
	bool WithinSearch(int index) { return _WithinSearch(m_root, index); }

private:
	bool _WithinSearch(Node* root, int index);
	void _Insert(Node*& root, Interval interval);
	void _Remove(Node*& root, Interval interval);

	static inline int _Intersect(const Interval& i1, const Interval& i2);
	static inline bool _Within(const Interval& i1, int index);

	Node* m_root;
	BlockAllocator<Node> m_alloc;
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

bool IntervalTree::_WithinSearch(Node* root, int index)
{
	if (root->isLeaf())
		return _Within(root->key, index);

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

void IntervalTree::_Insert(Node*& root, Interval interval)
{
	int ret = _Intersect(root->key, interval);

	if (ret < 0)
	{
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
		if (root->isLeaf())
		{
			root->key.left = std::min(root->key.left, interval.left);
			root->key.right = std::max(root->key.right, interval.right);
		}
		else
		{
			root->key.left = std::min(root->key.left, interval.left);
			root->key.right = std::max(root->key.right, interval.right);
			int retLeft = _Intersect(root->left->key, interval);
			int retRight = _Intersect(root->right->key, interval);

			if ((retLeft == 0) && (retRight == 0))
			{
				// All segments are one. The rest are abandoned.
				root->left = root->right = nullptr;
			}
			else if (retLeft == 0)
				_Insert(root->left, interval);
			else if (retRight == 0)
				_Insert(root->right, interval);
			else
			{
				// must between left and right
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

void IntervalTree::_Remove(Node*& root, Interval interval)
{
	int ret = _Intersect(root->key, interval);

	if (ret != 0)
		return;

	Interval key = root->key;
	if ((interval.left <= key.left) && (key.right <= interval.right))
	{
		root = nullptr;
		return;
	}
	
	if (root->isLeaf())
	{
		if (interval.left <= key.left)
			root->key.left = interval.right + 1;
		else if (interval.right >= key.right)
			root->key.right = interval.left - 1;
		else
		{
			// split
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
		// It's impossible to remove both
		if (_Intersect(root->left->key, interval) == 0)
			_Remove(root->left, interval);
		if (_Intersect(root->right->key, interval) == 0)
			_Remove(root->right, interval);

		if (!root->left || !root->right)
		{
			if (root->left)
				root = root->left;
			else
				root = root->right;
		}
		else
		{
			root->key.left = root->left->key.left;
			root->key.right = root->right->key.right;
		}
		
	}
}

int IntervalTree::_Intersect(const Interval& i1, const Interval& i2)
{
	if (i2.right < i1.left)
		return -1;
	if (i2.left > i1.right)
		return 1;
	return 0;
}

bool IntervalTree::_Within(const Interval& interval, int index)
{
	return (interval.left <= index) && (index <= interval.right);
}

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

	return qpow(m, x).b;
}

int main()
{
	int n, m;
	int left, right;
	int op, x, y;
	IntervalTree tree;

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
			tree.Remove(Interval(left, right));
		}
		else if (op == 3)
		{
			scanf("%d %d", &left, &right);
			scanf("%d %d", &x, &y);
			tree.Remove(Interval(left, right));
			tree.Insert(Interval(fib(x), fib(y)));
		}
		else
		{
			scanf("%d", &x);
			if (tree.WithinSearch(x))
				printf("true\n");
			else
				printf("false\n");
		}
	}

	return 0;
}
