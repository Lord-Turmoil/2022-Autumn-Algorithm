/********************************************************************
** Test - B
*/

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

#include <cstdio>
#include <string>
#include <unordered_set>

const int MAX_LENGTH = 28;

int main()
{
	std::unordered_set<std::string> list;
	char buffer[MAX_LENGTH];
	int n;
	bool flag;

	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%s", buffer);
		list.insert(buffer);
	}

	n--;
	flag = true;
	for (int i = 0; i < n; i++)
	{
		scanf("%s", buffer);
		list.erase(buffer);
	}

	printf("%s\n", list.begin()->c_str());

	return 0;
}