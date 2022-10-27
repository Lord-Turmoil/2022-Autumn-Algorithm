/*
** E
*/
#include <cstdio>
#include <string>
#include <unordered_set>

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

const int SIZE = 100005;
const int LENGTH = 5;

const int PID[] = { 0x1, 0x2, 0x4 };
const int SCR[] = { 0, 3, 1, 0 };

std::unordered_set<std::string> pool;
std::unordered_set<std::string> player[3];

int main()
{
	int score[3];
	int flag;
	int cnt;
	int t;
	int n;
	char buffer[5];

	scanf("%d", &t);
	while (t--)
	{
		score[0] = score[1] = score[2] = 0;
		pool.clear();
		player[0].clear();
		player[1].clear();
		player[2].clear();
		scanf("%d", &n);
		for (int p = 0; p < 3; p++)
		{
			for (int i = 0; i < n; i++)
			{
				scanf("%s", buffer);
				pool.insert(buffer);
				player[p].insert(buffer);
			}
		}

		for (auto it = pool.begin(); it != pool.end(); it++)
		{
			cnt = 0;
			flag = 0;

			for (int i = 0; i < 3; i++)
			{
				if (player[i].find(*it) != player[i].end())
				{
					cnt++;
					flag |= PID[i];
				}
			}
			for (int i = 0; i < 3; i++)
			{
				if (flag & PID[i])
					score[i] += SCR[cnt];
			}

#ifdef INTERNAL
			printf("\t> %s\n", it->c_str());
			printf("\t> %d\n", flag);
#endif
		}

		printf("%d %d %d\n", score[0], score[1], score[2]);
	}

	return 0;
}
