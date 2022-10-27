/********************************************************************
** E2 - E
*/

#include <cstdio>

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

const int DISK_NUM = 24;

const char POLE[] = { 'A', 'B', 'C' };
const int MOD = 3;

enum DIR
{
	LEFT = 0,
	RIGHT
};


struct Disk
{
	int pole;
	DIR dir;
};


void move_disk(int n, int step);
void move_single(int id, int step);

Disk disk[DISK_NUM];

int main()
{
	int n;
	char dir;

	while (scanf("%d", &n) != EOF)
	{
		for (int i = 1; i <= n; i++)
		{
			scanf(" %c", &dir);
			if (dir == 'l')
				disk[i].dir = LEFT;
			else
				disk[i].dir = RIGHT;
			disk[i].pole = 0;
		}

		move_disk(n, 1);
		putchar('\n');
	}

	return 0;
}


/******************************************************************************
 * move_disk -- Move disks for a given step.                                  *
 *                                                                            *
 *    This will move disk 1 to n 1 or 2 steps left from the original pole.    *
 *                                                                            *
 * INPUT:   n    -- Move disks 1 to n.                                        *
 *          step -- How many steps to make.                                   *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/10/01 Tony : Created.                                               *
 *============================================================================*/
void move_disk(int n, int step)
{
	if (n == 1)
		move_single(n, step);
	else
	{
		if (step == 1)
		{
			if (disk[n].dir == LEFT)
			{
				move_disk(n - 1, 2);
				move_single(n, 1);
				move_disk(n - 1, 2);
			}
			else
			{
				move_disk(n - 1, 1);
				move_single(n, 2);
				move_disk(n - 1, 2);
				move_single(n, 2);
				move_disk(n - 1, 1);
			}
		}
		else	// step == 2
		{
			if (disk[n].dir == LEFT)
			{
				move_disk(n - 1, 2);
				move_single(n, 1);
				move_disk(n - 1, 1);
				move_single(n, 1);
				move_disk(n - 1, 2);
			}
			else
			{
				move_disk(n - 1, 1);
				move_single(n, 2);
				move_disk(n - 1, 1);
			}
		}
	}
}


/******************************************************************************
 * move_single -- Move a single disk.                                         *
 *                                                                            *
 *    This move disk id 1 or 2 steps left from the original pole.             *
 *                                                                            *
 * INPUT:   id                                                                *
 *          step                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/10/01 Tony : Created.                                               *
 *============================================================================*/
void move_single(int id, int step)
{
	if (disk[id].dir == LEFT)
	{
		for (int i = 0; i < step; i++)
		{
			int tar = (disk[id].pole - 1 + MOD) % MOD;

			printf("move %d from %c to %c\n", id, POLE[disk[id].pole], POLE[tar]);

			disk[id].pole = tar;
		}
	}
	else
	{
		step = 3 - step;	// 1 -> 2, 2 -> 1
		for (int i = 0; i < step; i++)
		{
			int tar = (disk[id].pole + 1) % MOD;

			printf("move %d from %c to %c\n", id, POLE[disk[id].pole], POLE[tar]);

			disk[id].pole = tar;
		}
	}
}

