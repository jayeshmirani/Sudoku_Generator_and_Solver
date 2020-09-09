#include <bits/stdc++.h>
using namespace std;

#define BLANK 0 // BLANK is used for empty cells in sudoku grid
int N=9;

bool UsedInRow(vector<vector<int>> &grid, int row, int num)
{
    for (int col = 0; col < N; col++)
        if (grid[row][col] == num)
            return true;
    return false;
}

bool UsedInCol(vector<vector<int>> &grid, int col, int num)
{
    for (int row = 0; row < N; row++)
        if (grid[row][col] == num)
            return true;
    return false;
}

bool UsedInBox(vector<vector<int>> &grid, int boxStartRow,int boxStartCol, int num)
{
    int sqrt_N=sqrt(N);
    for (int row = 0; row < sqrt_N; row++)
        for (int col = 0; col < sqrt_N; col++)
            if (grid[row + boxStartRow][col + boxStartCol]== num)
                return true;
    return false;
}

bool isSafe(vector<vector<int>> &grid, int row,int col, int num)
{
    return grid[row][col] == BLANK && !UsedInRow(grid, row, num) && !UsedInCol(grid, col, num)
            && !UsedInBox(grid, row - row % 3,col - col % 3, num);
}

bool SolveSudoku(vector<vector<int>> &grid, stack<pair<int,int>> &blank_ind)
{
//    if (!FindBlankLocation(grid, row, col))
//        return true;
    if(blank_ind.empty())
        return true;
    pair<int,int> coordinates=blank_ind.top();
    blank_ind.pop();
    int row=coordinates.first, col=coordinates.second;
    for (int num = 1; num <= N; num++)
    {
        if (isSafe(grid, row, col, num))
        {
            grid[row][col] = num;
            if (SolveSudoku(grid, blank_ind))
                return true;
            grid[row][col] = BLANK;
        }
    }
    blank_ind.push(coordinates);
    return false; // triggers backtracking
}

int main()
{
    int N;
    cout << "Enter the size of the Sudoku Grid\n";
    cin >> N;
    vector<vector<int>> grid(N,vector<int>(N,0)); 
    stack<pair<int,int>> blank_ind;
    for(int i=N-1;i>=0;i--)
    {
        for(int j=N-1;j>=0;j--)
        {
            if(!grid[i][j])
                blank_ind.push({i,j});
        }
    }
    if (SolveSudoku(grid,blank_ind))
    {
        for (int row = 0; row < N; row++)
        {
            for (int col = 0; col < N; col++)
                cout << grid[row][col] << " ";
            cout << endl;
        }
    }
    else
        cout << "No solution exists";
    return 0;
}

//3 1 6 5 7 8 4 9 2
//5 2 9 1 3 4 7 6 8
//4 8 7 6 2 9 5 3 1
//2 6 3 4 1 5 9 8 7
//9 7 4 8 6 3 1 2 5
//8 5 1 7 9 2 6 4 3
//1 3 8 9 4 7 2 5 6
//6 9 2 3 5 1 8 7 4
//7 4 5 2 8 6 3 1 9
