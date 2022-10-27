/********************************************************************
** E1 - F
*/

#include <cstdio>
#include <cstring>

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

const int SIZE = 100010;

struct Node
{
	int color;
	int flip;
	Node* left;
	Node* right;
};

Node node[SIZE];

void AddChild(Node* root, Node* child);
void Dye(Node* root);
int main()
{
	int t;
	int n, q;

	scanf("%d", &t);
	while (t--)
	{
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
		{
			node[i].flip = 0;
			node[i].left = node[i].right = nullptr;
		}

		int parent;
		for (int i = 2; i <= n; i++)
		{
			scanf("%d", &parent);
			AddChild(&node[parent], &node[i]);
		}
		for (int i = 1; i <= n; i++)
			scanf("%1d", &node[i].color);

		scanf("%d", &q);
		int id;
		for (int i = 0; i < q; i++)
		{
			scanf("%d", &id);
			node[id].flip++;
		}

		Dye(&node[1]);

		for (int i = 1; i <= n; i++)
			printf("%1d", node[i].color);
		putchar('\n');
	}

	return 0;
}

void AddChild(Node* root, Node* child)
{
	if (root->left == nullptr)
		root->left = child;
	else
		root->right = child;
}

void Dye(Node* root)
{
	if (!root)
		return;

	if (root->flip & 1)
		root->color = 1 - root->color;

	if (root->left)
	{
		root->left->flip += root->flip;
		Dye(root->left);
	}
	if (root->right)
	{
		root->right->flip += root->flip;
		Dye(root->right);
	}
}


