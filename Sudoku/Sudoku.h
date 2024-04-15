#pragma once
#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>

/*
* Good source for unsolved Sudoku puzzles:
* https://sandiway.arizona.edu/sudoku/examples.html
*/

void load_sudoku_numbers(char* filename);
void clear_sudoku_screen();
void draw_sudoku_borders();
void draw_sudoku_numbers();
void solve_sudoku_puzzle();

void new_solved_number(int col, int row, int num);
void init_possible_numbers();
void print_possible_numbers();
void print_possible_numbers_box(int x, int y);
void remove_possible_number(int col, int row, int num);
