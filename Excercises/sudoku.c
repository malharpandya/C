/*
 * CSC A48 - Exercise 11 - Sudoku Solver
 * (c) F. Estrada, March 2019
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void print_sudoku(int sudoku[9][9])
{
  printf("The Sudoku contains:\n");
  for (int j=0; j<9; j++)
  {
    for (int i=0; i<9;i++)
    {
      printf("%d  ",sudoku[j][i]);
    }
    printf("\n");
  }
}

int check_replace(int sudoku[9][9], int row, int col, int num)
{
    for (int i = 0; i < 9; i++)
    {
        if (sudoku[row][i] == num || sudoku[i][col] == num) return 0;
    }
    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            if (sudoku[x + row - row%3][y + col - col%3] == num) return 0;
        }
    }
    return 1;
}

int find_rowcol(int sudoku[9][9])
{
    for (int row = 0; row < 9; row++)
    {
        for (int col = 0; col < 9; col++)
        {
            if (sudoku[row][col] == 0)
            {
                return (10 * row + col);
            }
        }
    }
    return -1;
}

int check_initial(int sudoku[9][9])
{
    for (int row = 0; row < 9; row++)
    {
        for (int col = 0; col < 9; col++)
        {
            int num = sudoku[row][col];
            if (num != 0)
            {
                sudoku[row][col] = 0;
                if (check_replace(sudoku, row, col, num) == 0)
                {
                    sudoku[row][col] = num;
                    return 0;
                }
                sudoku[row][col] = num;
            }
        }
    }
    return 1;
}

int actual_recursion(int sudoku[9][9], int depth)
{
    int rowcol = find_rowcol(sudoku);
    if (rowcol == -1) return 1;
    int row = rowcol / 10;
    int col = rowcol % 10;
    for (int i = 0; i < 10; i++)
    {
        if (check_replace(sudoku, row, col, i) == 1)
        {
            sudoku[row][col] = i;
            if (actual_recursion(sudoku, depth + 1)) return 1;
            sudoku[row][col] = 0;
        }
    }
    return 0;
}

void solve_sudoku(int sudoku[9][9], int depth)
{
    if (check_initial(sudoku) == 1) actual_recursion(sudoku, depth);
}

#ifndef __testing

int main()
{
  
   int Sudoku[9][9]={
       {5, 3, 0, 0, 7, 0, 0, 0, 0},
       {6, 0, 0, 1, 9, 5, 0, 0, 0},
       {0, 9, 8, 0, 0, 0, 0, 6, 0},
       {8, 0, 0, 0, 6, 0, 0, 0, 3},
       {4, 0, 0, 8, 0, 3, 0, 0, 1},
       {7, 0, 0, 0, 2, 0, 0, 0, 6},
       {0, 6, 0, 0, 0, 0, 2, 8, 0},
       {0, 0, 0, 4, 1, 9, 0, 0, 5},
       {0, 0, 0, 0, 8, 0, 0, 7, 9}};
    
    int test_hard_for_humans[9][9] = {
        {8, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 3, 6, 0, 0, 0, 0, 0},
        {0, 7, 0, 0, 9, 0, 2, 0, 0},
        {0, 5, 0, 0, 0, 7, 0, 0, 0},
        {0, 0, 0, 0, 4, 5, 7, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 3, 0},
        {0, 0, 1, 0, 0, 0, 0, 6, 8},
        {0, 0, 8, 5, 0, 0, 0, 1, 0},
        {0, 9, 0, 0, 0, 0, 4, 0, 0}};
    
    int test_empty[9][9] = {0};
    
    int test_minimum[9][9] ={
        {0, 0, 0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 2, 3},
        {0, 0, 4, 0, 0, 5, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 3, 0, 6, 0, 0},
        {0, 0, 7, 0, 0, 0, 5, 8, 0},
        {0, 0, 0, 0, 6, 7, 0, 0, 0},
        {0, 1, 0, 0, 0, 4, 0, 0, 0},
        {5, 2, 0, 0, 0, 0, 0, 0, 0}};
    
    int test_bruteforce_killer[9][9] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 3, 0, 8, 5},
        {0, 0, 1, 0, 2, 0, 0, 0, 0},
        {0, 0, 0, 5, 0, 7, 0, 0, 0},
        {0, 0, 4, 0, 0, 0, 1, 0, 0},
        {0, 9, 0, 0, 0, 0, 0, 0, 0},
        {5, 0, 0, 0, 0, 0, 0, 7, 3},
        {0, 0, 2, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 4, 0, 0, 0, 9}};


    /*printf("Input puzzle is:\n");
    print_sudoku(Sudoku);
    solve_sudoku(Sudoku,0);
    printf("Solution is:\n");
    print_sudoku(Sudoku);
    printf("\n====================================\n");
    printf("Input puzzle is:\n");
    print_sudoku(test_hard_for_humans);
    solve_sudoku(test_hard_for_humans,0);
    printf("Solution is:\n");
    print_sudoku(test_hard_for_humans);
    printf("\n====================================\n");
    printf("Input puzzle is:\n");
    print_sudoku(test_empty);
    solve_sudoku(test_empty,0);
    printf("Solution is:\n");
    print_sudoku(test_empty);
    printf("\n====================================\n");
    printf("Input puzzle is:\n");
    print_sudoku(test_minimum);
    solve_sudoku(test_minimum,0);
    printf("Solution is:\n");
    print_sudoku(test_minimum);
    printf("\n====================================\n");*/
    printf("Input puzzle is:\n");
    print_sudoku(test_bruteforce_killer);
    solve_sudoku(test_bruteforce_killer,0);
    printf("Solution is:\n");
    print_sudoku(test_bruteforce_killer);
}
#endif
