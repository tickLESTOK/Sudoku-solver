#include <iostream>
using std::cout;
using std::endl;

#define DIM 9
#define BLANK 0
#define SPACE ' '          // Use a single character for space
#define LINE '|'
#define NEW_ROW "-------------------------------------"

// Prints the Sudoku grid

void print_grid(int grid[DIM][DIM])
{
	for (int i = 0; i < DIM; i++)
	{
		cout << SPACE << SPACE << SPACE << SPACE << endl;
		cout << NEW_ROW << endl;
		for (int j = 0; j < DIM; j++)
		{
			cout << SPACE;
			if (BLANK == grid[i][j])
			{
				cout << SPACE;
			}
			else
			{
				cout << grid[i][j];
			}
			cout << SPACE;
			cout << LINE;
		}
	}
	cout << endl << NEW_ROW << endl << endl;;
}

// Checks if a number is used in the specified row
bool used_in_row(const int grid[DIM][DIM], int row, int num)
{
    for (int col = 0; col < DIM; col++)
        if (grid[row][col] == num)
            return true;
    return false;
}

// Checks if a number is used in the specified column
bool used_in_col(const int grid[DIM][DIM], int col, int num)
{
    for (int row = 0; row < DIM; row++)
        if (grid[row][col] == num)
            return true;
    return false;
}

// Checks if a number is used in the 3x3 box starting at (box_start_row, box_start_col)
bool used_in_box(const int grid[DIM][DIM], int box_start_row, int box_start_col, int num)
{
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (grid[box_start_row + row][box_start_col + col] == num)
                return true;
    return false;
}

// Checks if it's safe to place a number at (row, col)
bool is_safe(const int grid[DIM][DIM], int row, int col, int num)
{
    int box_start_row = row - row % 3;
    int box_start_col = col - col % 3;
    return !used_in_row(grid, row, num) &&
           !used_in_col(grid, col, num) &&
           !used_in_box(grid, box_start_row, box_start_col, num);
}

// Finds an unassigned location in the grid
bool get_unassigned_location(const int grid[DIM][DIM], int &row, int &col)
{
    for (row = 0; row < DIM; row++)
        for (col = 0; col < DIM; col++)
            if (grid[row][col] == BLANK)
                return true;
    return false;
}

// Solves the Sudoku using backtracking
bool solve_sudoku(int grid[DIM][DIM])
{
    int row, col;

    if (!get_unassigned_location(grid, row, col))
        return true; // No unassigned location means the puzzle is solved

    for (int num = 1; num <= 9; num++)
    {
        if (is_safe(grid, row, col, num))
        {
            grid[row][col] = num;
            if (solve_sudoku(grid))
                return true;
            grid[row][col] = BLANK; // Backtrack
        }
    }
    return false;
}

int main()
{
    cout << "********************************\n\n\tSudoku Solver\n\n********************************" << endl << endl;

    int grid[DIM][DIM] = {
        {0, 9, 0, 0, 0, 0, 8, 5, 3},
        {0, 0, 0, 8, 0, 0, 0, 0, 4},
        {0, 0, 8, 2, 0, 3, 0, 6, 9},
        {5, 7, 4, 0, 0, 2, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 9, 0, 0, 6, 3, 7},
        {9, 4, 0, 1, 0, 8, 5, 0, 0},
        {7, 0, 0, 0, 0, 6, 0, 0, 0},
        {6, 8, 2, 0, 0, 0, 0, 9, 0}
    };

    print_grid(grid);

    if (solve_sudoku(grid))
    {
        cout << "Sudoku solved successfully:" << endl;
        print_grid(grid);
    }
    else
    {
        cout << "No solution exists!" << endl;
    }
    return 0;
}
