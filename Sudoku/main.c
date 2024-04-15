#include "Sudoku.h"

int main(int argc, char** argv)
{
	init_possible_numbers();
	load_sudoku_numbers(argc == 2 ? argv[1] : "puzzle-003.txt");
	clear_sudoku_screen();
	draw_sudoku_borders();	
	draw_sudoku_numbers();
	solve_sudoku_puzzle();

	return 0;
}
