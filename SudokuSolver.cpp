#include <bits/stdc++.h>
using namespace std;

#define BLANK 0 // BLANK is used for empty cells in sudoku grid
int N;

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
    cout << "Enter the size of Sudoku grid\n";
    cin >> N;
    vector<vector<int>> grid(N,vector<int>(N,0));
    cout <<  "Enter the space separated Sudoku Grid(Enter 0 to indicate empty cells)\n";
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            cin >> grid[i][j];
        }
    }
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

//3 0 6 5 0 8 4 0 0
//5 2 0 0 0 0 0 0 0
//0 8 7 0 0 0 0 3 1
//0 0 3 0 1 0 0 8 0
//9 0 0 8 6 3 0 0 5
//0 5 0 0 9 0 6 0 0
//1 3 0 0 0 0 2 5 0
//0 0 0 0 0 0 0 7 4
//0 0 5 2 0 6 3 0 0
