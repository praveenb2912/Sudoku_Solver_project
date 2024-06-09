#include <iostream>
#include <algorithm>
#include <vector>
#include <array>
using namespace std;


#define DIM 6
#define BLANK 0
#define SPACE " "
#define LINE "|"
#define NEW_ROW "-------------------------------------"
#define GRID_FULL make_pair(6, 6)

// Prints the Soduko grid
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

// Returns a boolean which indicates whether any assigned entry
// in the specified row matches the given number. 
bool used_in_row(int grid[DIM][DIM], int row, int num)
{
	for (int col = 0; col < DIM; col++)
		if (grid[row][col] == num)
		{
			return true;
		}
	return false;
}

// Returns a boolean which indicates whether any assigned entry
// in the specified column matches the given number. 
bool used_in_col(int grid[DIM][DIM], int col, int num)
{
	for (int row = 0; row < DIM; row++)
		if (grid[row][col] == num)
		{
			return true;
		}
	return false;
}

// Returns a boolean which indicates whether any assigned entry
// within the specified 3x3 box matches the given number. 
bool used_in_box(int grid[DIM][DIM], int box_start_rpw, int box_start_col, int num)
{
	for (int row = 0; row < 3; row++)
		for (int col = 0; col < 3; col++)
			if (grid[row + box_start_rpw][col + box_start_col] == num) 
			{
				return true;
			}
	return false;
}

// Returns a boolean which indicates whether it will be legal to assign
// num to the given row,col location.
bool is_safe(int grid[DIM][DIM], int row, int col, int num)
{
	// Check if 'num' is not already placed in current row,
	// current column and current 3x3 box 
	return !used_in_row(grid, row, num) &&
		!used_in_col(grid, col, num) &&
		!used_in_box(grid, row - row % 3, col - col % 3, num);
}

// Searches the grid to find an entry that is still unassigned and has 
//the minimum remaining values
pair<int, int> get_unassigned_location(int grid[DIM][DIM])
{
	int min_count = 10;
    pair<int, int> best_location = GRID_FULL;

    for (int row = 0; row < DIM; row++)
    {
        for (int col = 0; col < DIM; col++)
        {
            if (grid[row][col] == BLANK)
            {
                int count = 0;
                for (int num = 1; num <= 9; num++)
                {
                    if (is_safe(grid, row, col, num))
                    {
                        count++;
                    }
                }
                if (count < min_count)
                {
                    min_count = count;
                    best_location = make_pair(row, col);
                }
            }
        }
    }

    return best_location;

}

// Takes a partially filled-in grid and attempts to assign values to
// all unassigned locations in such a way to meet the requirements
// for Sudoku solution (non-duplication across rows, columns, and boxes) 
bool solve_soduko(int grid[DIM][DIM])
{
	// If the Soduko grid has been filled, we are done
	if (GRID_FULL == get_unassigned_location(grid))
	{
		return true; 
	}

	// Get an unassigned Soduko grid location
	pair<int, int> row_and_col = get_unassigned_location(grid);
	int row = row_and_col.first;
	int col = row_and_col.second;

	// Consider digits 1 to 9
	for (int num = 1; num <= 9; num++)
	{
		// If placing the current number in the current
		// unassigned location is valid, go ahead
		if (is_safe(grid, row, col, num))
		{
			// Make tentative assignment
			grid[row][col] = num;

			// Do the same thing again recursively. If we go 
			// through all of the recursions, and in the end 
			// return true, then all of our number placements 
			// on the Soduko grid are valid and we have fully
			// solved it
			if (solve_soduko(grid))
			{
				return true;
			}

			// As we were not able to validly go through all 
			// of the recursions, we must have an invalid number
			// placement somewhere. Lets go back and try a 
			// different number for this particular unassigned location
			grid[row][col] = BLANK;
		}
	}

	// If we have gone through all possible numbers for the current unassigned
	// location, then we probably assigned a bad number early. Lets backtrack 
	// and try a different number for the previous unassigned locations.
	return false; 
}

int main()
{
	cout << "********************************\n\n\tSudoku Solver\n\n********************************" << endl << endl;

	int grid[DIM][DIM] = { { 0, 9, 0, 0, 0, 3 },
				{ 0, 0, 5, 0, 6, 0 },
				{ 3, 0, 0, 1, 0, 0 },
				{ 0, 0, 2, 0, 0, 5 },
				{ 0, 4, 0, 6, 0, 0 },
				{ 1, 0, 0, 0, 2, 0 }
				};

	print_grid(grid);

	if (true == solve_soduko(grid))
	{
		//calls the print function
		print_grid(grid);
	}
	else
	{
		cout << "No solution exists for the given Soduko" << endl << endl;
	}

	return 0;
}
