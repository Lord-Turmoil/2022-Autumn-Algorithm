/********************************************************************
** C4 - E
*/

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

#include <cstdio>
#include <cctype>
#include <cstring>
#include <queue>

const int LETTER_NUM = 26;
const int SYMBOL_NUM = LETTER_NUM * 2;

struct HuffmanNode
{
	int id;
	int weight;
	HuffmanNode* left;
	HuffmanNode* right;

	HuffmanNode(int _id, int _weight)
	{
		id = _id;
		weight = _weight;
		left = right = nullptr;
	}
};

struct CompareHuffmanNode
{
	bool operator()(HuffmanNode* n1, HuffmanNode* n2)
	{
		return n1->weight > n2->weight;
	};
};

constexpr int char_to_int(char ch)
{
	return islower(ch) ? (ch - 'a') : (ch - 'A' + LETTER_NUM);
}

constexpr int int_to_char(int d)
{
	return (d < LETTER_NUM) ? (d + 'a') : (d - LETTER_NUM + 'A');
}

int frequency[SYMBOL_NUM];
int length[SYMBOL_NUM];

void dfs(HuffmanNode* root, int depth);
void destroy(HuffmanNode* root);
int main()
{
	char ch;

	while (isalpha(ch = getchar()))
		frequency[char_to_int(ch)]++;

	std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, CompareHuffmanNode> heap;
	for (int i = 0; i < SYMBOL_NUM; i++)
	{
		if (frequency[i] > 0)
			heap.push(new HuffmanNode(i, frequency[i]));
	}

	// Only one kind of letter, then length should be 1.
	if (heap.size() == 1)
	{
		printf("%d\n", frequency[heap.top()->id]);
		delete heap.top();
		return 0;
	}


	HuffmanNode* left;
	HuffmanNode* right;
	HuffmanNode* mid;
	while (heap.size() > 1)
	{
		left = heap.top();
		heap.pop();
		right = heap.top();
		heap.pop();

		mid = new HuffmanNode(-1, left->weight + right->weight);
		mid->left = left;
		mid->right = right;

		heap.push(mid);
	}

	dfs(heap.top(), 0);
	heap.pop();

#ifdef INTERNAL
	for (int i = 0; i < SYMBOL_NUM; i++)
		printf("%d ", length[i]);
	putchar('\n');
#endif

	long long ans = 0;
	for (int i = 0; i < SYMBOL_NUM; i++)
		ans += 1LL * frequency[i] * length[i];

	printf("%lld\n", ans);

	return 0;
}

void dfs(HuffmanNode* root, int depth)
{
	if (root->id != -1)
		length[root->id] = depth;

	if (root->left)
		dfs(root->left, depth + 1);
	if (root->right)
		dfs(root->right, depth + 1);
}

void destroy(HuffmanNode* root)
{
	if (root->left)
		destroy(root->left);
	if (root->right)
		destroy(root->right);

	delete root;
}
