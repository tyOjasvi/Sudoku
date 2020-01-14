#include<iostream>
#include<cstdlib>

 #include<time.h>
#include<ctime>
#include <iomanip>
#include <stdlib.h>
#include <unistd.h>
#include <bits/stdc++.h>
#define N 9
using namespace std;
int grid[N][N];


void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;

    // Stroing start time
    clock_t start_time = clock();

    // looping till required time is not acheived
    while (clock() < start_time + milli_seconds)
        ;
}

class user{
    int score;
    char name[20];
    int life;
    int level;
    public:
    user()
    {
        score = 0;
        life = 2;
    }

    int random_generator(int m)
    {
        int r;
        r = rand()%m + 1;

        return r;
    }

    void fillDiagonal()
    {

        for (int i = 0; i<N; i=i+3)
            fillBox(i, i);
    }
    void fillBox(int row,int col)
    {
        int num;
        for (int i=0; i<3; i++)
        {
            for (int j=0; j<3; j++)
            {
                do
                {
                    num = random_generator(N);
                }
                while (UsedInBox(row, col, num));

                grid[row+i][col+j] = num;
            }
        }
    }

    bool fillRemaining(int i, int j)
    {

        if (j>=N && i<N-1)
        {
            i = i + 1;
            j = 0;
        }
        if (i>=N && j>=N)
            return true;

        if (i < 3)
        {
            if (j < 3)
                j = 3;
        }
        else if (i < N-3)
        {
            if (j==(int)(i/3)*3)
                j =  j + 3;
        }
        else
        {
            if (j == N-3)
            {
                i = i + 1;
                j = 0;
                if (i>=N)
                    return true;
            }
        }

        for (int num = 1; num<=N; num++)
        {
            if (isSafe(i, j, num))
            {
                grid[i][j] = num;
                if (fillRemaining(i, j+1))
                    return true;

                grid[i][j] = 0;
            }
        }
        return false;
    }

    void removeDigits()
    {
        int count = level;
        while (count != 0)
        {
            int cellId = random_generator(N*N);


            int i = (cellId/N);
            int j = cellId%9;
            if (j != 0)
                j = j - 1;
            if (grid[i][j] != 0)
            {
                count--;
                grid[i][j] = 0;
            }
        }
    }

    void fillValues()
    {

        fillDiagonal();
        fillRemaining(0, 3);
        removeDigits();
    }
    void get_data()
    {
        int p;
        cout<<"\n Honoured to make your acquaintance, fellow warrior. What should we call you?";
        cout<<"\n Answer: ";
        cin>>name;
        cout<<"\n Choose the Level of Your Experience: ";
        cout<<"\n 1. ROOKIE";
        cout<<"\n 2. AMATEUR";
        cout<<"\n 3. VETERAN";
        cout<<"\n Enter Your Choice, "<<name<<" : ";
        cin>>p;

        switch(p)
        {
            case 1: level = 10;
                    break;

            case 2: level = 24;
                    break;
            case 3: level = 35;
                    break;
            default: cout<<"\n Hmmm, Maybe you are Rookie";
                     level = 10;
                     break;
        }
    }

       bool FindUnassignedLocation(int &row, int &col)

    {

        for (row = 0; row < N; row++)

            for (col = 0; col < N; col++)

                if (grid[row][col] == 0)

                    return true;

        return false;

    }

    bool UsedInRow(int row, int num)

    {

        for (int col = 0; col < N; col++)

            if (grid[row][col] == num)

                return true;

        return false;

    }

    bool UsedInCol(int col, int num)

    {

        for (int row = 0; row < N; row++)

            if (grid[row][col] == num)

                return true;

        return false;

    }


    bool UsedInBox(int boxStartRow, int boxStartCol, int num)

    {

        for (int row = 0; row < 3; row++)

            for (int col = 0; col < 3; col++)

                if (grid[row+boxStartRow][col+boxStartCol] == num)

                    return true;

        return false;

    }


    bool isSafe(int row, int col, int num)

    {

        return !UsedInRow(row, num) && !UsedInCol(col, num) &&

               !UsedInBox(row - row % 3 , col - col % 3, num);

    }


    bool SolveSudoku()

    {

        int row, col;

        if (!FindUnassignedLocation(row, col))

           return true;

        for (int num = 1; num <= 9; num++)

        {

            if (isSafe(row, col, num))

            {

                grid[row][col] = num;

                if (SolveSudoku())
                {
                    grid[row][col] = 0;
                    return true;

                }
                grid[row][col] = 0;


            }

        }

        return false;

    }

     void printGrid()

    {

        for (int row = 0; row < N; row++)

        {

            for (int col = 0; col < N; col++)

                cout<<" "<<grid[row][col]<<"  ";

            cout<<endl;

        }

    }


    void check( int i, int j, int val)
    {
        grid[i][j] = val;

        if(SolveSudoku())
        {
            cout<<"\n Congratulations, You are Getting Closer to Conquering the Sudoku-Verse";
            score+=10;
            cout<<"\n SCORE: "<<score;

            cout<<"\n The Edited Grid Is:"<<endl;
            printGrid();
        }
        else
        {
            grid[i][j] = 0;

            if(life==0)
            {
                cout<<"\n GAME OVER";
                exit(0);
            }

            else
            {
                life-=1;
                cout<<"\n Careful There, You Lost a Life";
                cout<<"LIFE = "<<life;
            }
        }
    }

    bool filled()
    {
        int r, c;

        if(!FindUnassignedLocation(r,c))
        {
            return true;
        }

        else
        {
            return false;
        }
    }



};



int main()
{

 user u;
 u.get_data();
  u.fillValues();
  cout<<endl<<endl<<"You have Total 2 Lives! So play carefully!!";
 delay(2);
 system("cls");

 /* Time function returns the time since the
        Epoch(jan 1 1970). Returned time is in seconds. */
    time_t start, end;

    /* You can call it like this : start = time(NULL);
     in both the way start contain total time in seconds
     since the Epoch. */
    time(&start);

    // unsync the I/O of C and C++.
    ios_base::sync_with_stdio(false);
 cout<<"\n Warrior, this is what your battlefield looks like today:"<<endl;
 cout<<"\n";
 u.printGrid();
 while(!u.filled())
 {
    int i, j, k;

    cout<<"\n Enter Row You Wish To Fill";
    cin>>i;
    cout<<"\n Enter Column You Wish To Fill";
    cin>>j;
    cout<<"\n Enter The Value You Wish To Fill";
    cin>>k;

    if( grid[i][j]==0)
    {
    u.check(i, j, k);
    }
    else
    {
        cout<<"\n Looks like you are attempting to fill an already filled location!!";
        cout<<"\n Please make an alternative choice among the unfilled blocks!!";
        continue;
    }
 }

  // Recording end time.
    time(&end);

    // Calculating total time taken by the program.
    double time_taken = double(end - start);

 cout<<"\n Excellent Work!! You Conquered the Sudoku-Verse!!";

     cout << "Time taken for you to solve the Sudoku is : " << fixed
         << time_taken << setprecision(5);
    cout << " sec " << endl;

 return 0;
}
