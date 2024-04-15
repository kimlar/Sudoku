#include "Solver.h"
#include <stdio.h>

extern void new_solved_number(int col, int row, int num);
extern void remove_possible_number(int col, int row, int num);

extern int solved_numbers[9][9];
extern int possible_numbers[9][9][9];

void solve_possible_numbers()
{
	find_last_remaining_digit();
	
	find_last_cross_digit(0, 0);
	find_last_cross_digit(3, 0);
	find_last_cross_digit(6, 0);
	find_last_cross_digit(0, 3);
	find_last_cross_digit(3, 3);
	find_last_cross_digit(6, 3);
	find_last_cross_digit(0, 6);
	find_last_cross_digit(3, 6);
	find_last_cross_digit(6, 6);
}

void find_last_remaining_digit()
{
	int numberOfFound = 0;
	for (int j = 0; j < 9; j++)
	{
		for (int i = 0; i < 9; i++)
		{
			numberOfFound = 0;
			for (int k = 0; k < 9; k++)
			{
				if (possible_numbers[i][j][k] != 0)
				{
					numberOfFound++;
				}
			}
			//printf("[%d %d] numberOfFound %d\n", i, j, numberOfFound);
			if (numberOfFound == 1)
			{
				for (int n = 0; n < 9; n++)
				{
					if (possible_numbers[i][j][n] != 0)
					{
						new_solved_number(i, j, n + 1);
					}
				}
			}
		}
	}
}

void find_last_cross_digit(int x, int y)
{
	int found[9] = { 0 };
	int found_x[9] = { 0 };
	int found_y[9] = { 0 };
	for (int j = y; j < (y + 3); j++)
	{
		for (int i = x; i < (x + 3); i++)
		{
			for (int k = 0; k < 9; k++)
			{
				if (possible_numbers[i][j][k] != 0)
				{
					found[k]++;
					found_x[k] = i;
					found_y[k] = j;
				}
			}
		}
	}

	for (int k = 0; k < 9; k++)
	{
		if (found[k] == 1)
		{
			int count = 0;
			for (int n = 0; n < 9; n++)
			{
				if (possible_numbers[found_x[k]][found_y[k]][n] != 0)
					count++;
			}
			if (count > 1)
				new_solved_number(found_x[k], found_y[k], k + 1);
		}
	}
}
