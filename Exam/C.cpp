/********************************************************************
** Exam - C
*/

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

#include <cstdio>
#include <stack>
#include <queue>

void solve();
int main()
{
	int t;

	scanf("%d", &t);
	while (t--)
		solve();

	return 0;
}

void solve()
{
	int n;
	int op, x;

	std::stack<int> stack;
	std::priority_queue<int, std::vector<int>, std::greater<int>> heap;

	scanf("%d", &n);
	while (n--)
	{
		scanf("%d", &op);
		if (op == 1)
		{
			scanf("%d", &x);
			stack.push(x);
		}
		else if (op == 2)
		{
			if (stack.empty())
				printf("empty\n");
			else
				stack.pop();
		}
		else if (op == 3)
		{
			if (stack.empty())
				printf("empty\n");
			else
				printf("%d\n", stack.top());
		}
	}

	while (!stack.empty())
	{
		heap.push(stack.top());
		stack.pop();
	}

	while (!heap.empty())
	{
		printf("%d ", heap.top());
		heap.pop();
	}
	putchar('\n');
}
