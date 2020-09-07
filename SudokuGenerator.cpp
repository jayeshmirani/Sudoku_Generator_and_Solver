#include<bits/stdc++.h>
using namespace std;
int N;

bool NotInRow(vector<vector<int>> mat,int i,int num)
{
    for (int j=0; j<N; j++)
        if (mat[i][j] == num)
            return false;
    return true;
}

bool NotInCol(vector<vector<int>> mat,int j,int num)
{
    for (int i=0; i<N; i++)
        if (mat[i][j] == num)
            return false;
    return true;
}

bool NotInBox(vector<vector<int>> mat,int rowStart, int colStart, int num)
{
    int sqrt_N= sqrt(N);
    for (int i = 0; i<sqrt_N; i++)
    {
        for (int j = 0; j<sqrt_N; j++)
        {
            if (mat[rowStart+i][colStart+j]==num)
                return false;
        }
    }
    return true;
}

void fillDiagonal(vector<vector<int>> &mat) // Fill the diagonal matrices of sqrt(N)xsqrt(N) dimensions with random no.s from 1 to N
{
    int sqrt_N= sqrt(N);
    for (int row=0; row<N; row+=sqrt_N)
    {
        for (int i=0; i<sqrt_N; i++)
        {
            for (int j=0; j<sqrt_N; j++)
            {
                int num=(rand()%N) +1;
                while (!NotInBox(mat, row, row, num)) // starting element of a diagonal matrix has row=col
                    num = (rand()%N) +1;
                mat[row+i][row+j] = num;
            }
        }
    }
}

bool fillRemaining(vector<vector<int>> &mat,int i, int j) // A recursive function to fill non diagonal matrices
{
    int sqrt_N= sqrt(N),row_num=i/sqrt_N;
    if(j>= row_num*sqrt_N && j< (row_num+1)*sqrt_N)
        j= (row_num+1)*sqrt_N;

    if(j>=N)
    {
        if(i<N-1)
        {
            i++;
            j = 0;
        }
        else
            return true;
    }
    row_num=i/sqrt_N;
    if(j>= row_num*sqrt_N && j< (row_num+1)*sqrt_N)
        j= (row_num+1)*sqrt_N;
    for (int num = 1; num<=N; num++)
    {
        if (NotInRow(mat,i, num) && NotInCol(mat,j, num) && NotInBox(mat,i-i%sqrt_N, j-j%sqrt_N,num))
        {
            mat[i][j] = num;
            if (fillRemaining(mat,i, j+1))
                return true;
            mat[i][j] = 0;
        }
    }
    return false;
}

void removeElements(vector<vector<int>> &mat, int k)
{
    while(k)
    {
        int i = (rand())%N;
        int j = (rand())%N;
        if (mat[i][j])
        {
            k--;
            mat[i][j] = 0;
        }
    }
}

int main()
{
    cout << "\nEnter size N of sudoku of dimensions NxN (N must be a perfect square): ";
    cin >> N;
    float sqrt_N = sqrt(N);
    if(floor(sqrt_N)-sqrt_N==0)
    {
        vector<vector<int>> mat;
        for(int i=0;i<N;i++)
        {
            mat.push_back(vector<int>{0});
            for(int j=1;j<N;j++)
                mat[i].push_back(0);
        }
        fillDiagonal(mat);
        bool ans=fillRemaining(mat,0, int(sqrt_N));
//        if(fillRemaining(mat,0, int(sqrt_N)))
//        {
            cout << "\nEnter the no. of elements to be deleted randomly from the puzzle";
            int k;
            cin >> k;
            removeElements(mat,k);
            cout << "\nSudoku puzzle generated is:\n";
            for(int i=0;i<N;i++)
            {
                for(int j=0;j<N;j++)
                {
                    if(mat[i][j])
                        cout << mat[i][j] << " ";
                    else
                        cout << "_ ";
                }
            cout << endl;
            }
//        }
    }
    else
        cout << "\n Invalid Input";
}

