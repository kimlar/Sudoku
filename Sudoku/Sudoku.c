#include "Sudoku.h"
#include <stdlib.h>
//#include <stdbool.h>
#include "ConsoleUtils.h"
#include "Solver.h"

int solved_numbers[9][9] = { 0 };
int possible_numbers[9][9][9] = { 0 };

void load_sudoku_numbers(char* filename)
{
	FILE* puzzlefile = fopen(filename, "r");
	if (!puzzlefile)
	{
		set_text_color(Red);
		printf("ERROR: Could not load file: %s\n", filename);
		set_text_color(White);
		exit(1);
	}

	int ch;
	int i = -1;
	//int x = 0;
	//int y = 0;
	// Loop to extract every characters
	while (1)
	{
		// Reading file
		ch = fgetc(puzzlefile);

		// End of file indicator
		if (feof(puzzlefile))
			break;

		// Displaying every characters
		if (ch > 47 && ch < 58)
		{
			i++;
			//x = i % 9;
			//y = i / 9;
			//solved_numbers[x][y] = ch - 48; // Need to adjust to get 0-9 correctly
			int number = ch - 48;
			if(number != 0)
				new_solved_number((i % 9), (i / 9), number); // Need to adjust to get 0-9 correctly
		}
	}

	fclose(puzzlefile);
}

void clear_sudoku_screen()
{
	set_text_color(White);
	set_back_color(Black);
	set_cursor_position(0, 0);
	system("cls");
}

void draw_sudoku_borders()
{
	set_text_color(BrightBlack);
	set_cursor_position(0, 0);

	printf("\xC9\xCD\xD1\xCD\xD1\xCD\xCB\xCD\xD1\xCD\xD1\xCD\xCB\xCD\xD1\xCD\xD1\xCD\xBB\n");
	printf("\xBA \xB3 \xB3 \xBA \xB3 \xB3 \xBA \xB3 \xB3 \xBA\n");
	printf("\xC7\xC4\xC5\xC4\xC5\xC4\xD7\xC4\xC5\xC4\xC5\xC4\xD7\xC4\xC5\xC4\xC5\xC4\xB6\n");
	printf("\xBA \xB3 \xB3 \xBA \xB3 \xB3 \xBA \xB3 \xB3 \xBA\n");
	printf("\xC7\xC4\xC5\xC4\xC5\xC4\xD7\xC4\xC5\xC4\xC5\xC4\xD7\xC4\xC5\xC4\xC5\xC4\xB6\n");
	printf("\xBA \xB3 \xB3 \xBA \xB3 \xB3 \xBA \xB3 \xB3 \xBA\n");
	printf("\xCC\xCD\xD8\xCD\xD8\xCD\xCE\xCD\xD8\xCD\xD8\xCD\xCE\xCD\xD8\xCD\xD8\xCD\xB9\n");
	printf("\xBA \xB3 \xB3 \xBA \xB3 \xB3 \xBA \xB3 \xB3 \xBA\n");
	printf("\xC7\xC4\xC5\xC4\xC5\xC4\xD7\xC4\xC5\xC4\xC5\xC4\xD7\xC4\xC5\xC4\xC5\xC4\xB6\n");
	printf("\xBA \xB3 \xB3 \xBA \xB3 \xB3 \xBA \xB3 \xB3 \xBA\n");
	printf("\xC7\xC4\xC5\xC4\xC5\xC4\xD7\xC4\xC5\xC4\xC5\xC4\xD7\xC4\xC5\xC4\xC5\xC4\xB6\n");
	printf("\xBA \xB3 \xB3 \xBA \xB3 \xB3 \xBA \xB3 \xB3 \xBA\n");
	printf("\xCC\xCD\xD8\xCD\xD8\xCD\xCE\xCD\xD8\xCD\xD8\xCD\xCE\xCD\xD8\xCD\xD8\xCD\xB9\n");
	printf("\xBA \xB3 \xB3 \xBA \xB3 \xB3 \xBA \xB3 \xB3 \xBA\n");
	printf("\xC7\xC4\xC5\xC4\xC5\xC4\xD7\xC4\xC5\xC4\xC5\xC4\xD7\xC4\xC5\xC4\xC5\xC4\xB6\n");
	printf("\xBA \xB3 \xB3 \xBA \xB3 \xB3 \xBA \xB3 \xB3 \xBA\n");
	printf("\xC7\xC4\xC5\xC4\xC5\xC4\xD7\xC4\xC5\xC4\xC5\xC4\xD7\xC4\xC5\xC4\xC5\xC4\xB6\n");
	printf("\xBA \xB3 \xB3 \xBA \xB3 \xB3 \xBA \xB3 \xB3 \xBA\n");
	printf("\xC8\xCD\xCF\xCD\xCF\xCD\xCA\xCD\xCF\xCD\xCF\xCD\xCA\xCD\xCF\xCD\xCF\xCD\xBC\n");

	set_text_color(White);
}

void draw_sudoku_numbers()
{
	set_text_color(Green);

	for (int j = 0; j < 9; j++)
	{
		for (int i = 0; i < 9; i++)
		{
			set_cursor_position((j + 1) * 2, (i + 1) * 2);
			if (solved_numbers[i][j] != 0)
				printf("%d\n", solved_numbers[i][j]);
		}
	}

	set_text_color(White);
	set_cursor_position(20, 0);
}

/*
void draw_sudoku_new_number(int col, int row)
{
	set_text_color(Yellow);
	set_cursor_position((row + 1) * 2, (col + 1) * 2);
	printf("%d\n", solved_numbers[col][row]);
	set_text_color(White);
	set_cursor_position(20, 0);
}
*/

void solve_sudoku_puzzle()
{
	//print_possible_numbers();

	//solve_possible_numbers();
	//solve_possible_numbers();

	//print_possible_numbers();

	int number_of_passes = 3;
	for (int i = 0; i < number_of_passes; i++)
	{
		//printf("New round\n");
		solve_possible_numbers();
	}
	printf("Number of passes: %d\n", number_of_passes);

	//print_possible_numbers_box(3, 3);
	
	print_possible_numbers();

	

	/*
	// Place text cursor at the end
	set_cursor_position(25, 0);
	set_text_color(White);
	set_back_color(Black);
	printf("Done\n");
	*/
}

void new_solved_number(int col, int row, int num)
{
	// NOTE: When new solved number is found this function internally removes all possible number except for the found number
	solved_numbers[col][row] = num;
	remove_possible_number(col, row, num);


	set_text_color(Yellow);
	set_cursor_position((row + 1) * 2, (col + 1) * 2);
	printf("%d\n", solved_numbers[col][row]);
	set_text_color(White);
	set_cursor_position(20, 0);
}

void init_possible_numbers()
{
	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			//printf("[%d %d] ", col, row);
			for (int i = 0; i < 9; i++)
			{
				possible_numbers[col][row][i] = i + 1;
				//printf("%d ", possible_numbers[col][row][i]);
			}
			//printf("\n");
		}
	}
}

void print_possible_numbers()
{
	printf("Possible numbers:\n");
	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			printf("[%d %d] ", col, row);
			for (int i = 0; i < 9; i++)
			{
				if (possible_numbers[col][row][i] != 0)
					set_text_color(Green);
				printf("%d ", possible_numbers[col][row][i]);
				set_text_color(White);
			}
			printf("\n");
		}
	}
}

void print_possible_numbers_box(int x, int y)
{
	for (int j = y; j < (y + 3); j++)
	{
		for (int i = x; i < (x + 3); i++)
		{
			printf("[%d %d] ", i, j);
			for (int k = 0; k < 9; k++)
			{
				printf("%d ", possible_numbers[i][j][k]);
			}
			printf("\n");
		}
	}
}

void remove_possible_number(int col, int row, int num)
{
	// Remove all possible numbers on the newly found number
	for (int i = 0; i < 9; i++)
		possible_numbers[col][row][i] = 0;

	// Remove all same numbers on the same row
	for (int i = 0; i < 9; i++)
		possible_numbers[i][row][num - 1] = 0;

	// Remove all same numbers on the same column
	for (int i = 0; i < 9; i++)
		possible_numbers[col][i][num - 1] = 0;

	// Remove all same numbers on the same box
	for (int j = 0; j < 3; j++)
		for (int i = 0; i < 3; i++)
			possible_numbers[(col / 3) * 3 + i][(row / 3) * 3 + j][num - 1] = 0;

	// Add the newly found number
	possible_numbers[col][row][num - 1] = num;
}
