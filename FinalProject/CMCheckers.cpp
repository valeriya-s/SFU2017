#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <string>
using namespace std;
 

const int MAX_ARRAY_SIZE = 18; 
const int MIN_ARRAY_SIZE = 8; 
const int MAX_PIECES = 72; //
const int NOPLAYER = 0;
const int WHITEWINS = 1; //
const int REDWINS = 2;
const int NOONEWINS = 0; //
const int WHITESOLDIER = 1;
const int WHITEMULE = 2;
const int WHITEKING = 3;
const int REDSOLDIER = 4;
const int REDMULE = 5;
const int REDKING = 6;
const int WHITEPLAYER = 1;
const int REDPLAYER = 2;
 
void InitializeBoard( int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard );
 
void DisplayBoard( int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard);
 
int CountJumps( int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLocArray[], int yLocArray[] );
 
bool CheckList( int inArray1[], int inArray2[], int xIndex, int yIndex);
 
int CountMove1Squares( int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLocArray[],  int yLocArray[] );
 
bool IsMove1Square( int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLoc, int yLoc);
 
bool IsJump( int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE],int numRowsInBoard, int player, int xLoc, int yLoc);
 
bool MakeMove( int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int fromSquareNum, int toSquareNum, bool &jumped );
 
bool CheckWin(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard);
 
int main()
{
    int checker[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE];
    int xIndicesMove[MAX_PIECES];
    int yIndicesMove[MAX_PIECES];
    int xIndicesJump[MAX_PIECES];
    int yIndicesJump[MAX_PIECES];
 
    const int MAXROWS = 18;
    const int MINROWS = 8;
    const int MAXTRIES = 3;
	const int DONE = 0;
 
    int numrows = 0;
    int tries = 1;
    int index = 0;
    int entermove = 0;
	int aftermove = 0;
	int playerturn = WHITEPLAYER;

	int numjumps = 0;
    int yindices = 0;
    int xindices = 0;
	int nextyindices = 0;
	int nextxindices = 0;
	int move = 0;
 
	string mycolour;
	string oppcolour;
	int mysoldier = 0;
	int oppsoldier = 0;
	int myking = 0;
	int oppking = 0;
	int mymule = 0;
	int oppmule = 0;
	int valid = 1;

	bool valid2 = false;
	bool jumped = false;
 
    do
    {
        cout << "Enter the number of squares along each edge of the board" << endl;
 
        if ( !(cin >> numrows) )
        {
            cerr << "ERROR: Board size is not an integer.";
            cerr << "\n" << MINROWS << " <= number of squares <= " << MAXROWS << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }
		else if( (numrows%2) == 1 )
        {
            cerr << "ERROR: Board size odd.";
            cerr << "\n" << MINROWS << " <= number of squares <= " << MAXROWS << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }
        else if( numrows < MINROWS )
        {
            cerr << "ERROR: Board size too small.";
            cerr << "\n" << MINROWS << " <= number of squares <= " << MAXROWS << endl;
            cin.clear();
            cin.ignore(1000, '\n');
           
        }
        else if( numrows > MAXROWS )
        {
            cerr << "ERROR: Board size too big.";
            cerr << "\n" << MINROWS << " <= number of squares <= " << MAXROWS << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }
        else
        {
            break;
            tries = 1;
        }
        tries ++;
    } while ( tries <= MAXTRIES );
 
    if ( tries > MAXTRIES )
    {
        cerr << "ERROR: too many errors enterng the size of the board";
        return 1;
    }
 
    InitializeBoard(checker, numrows);
 
    DisplayBoard(checker, numrows);
   
    cout << endl << endl << endl;
 
	for(int moves = 1; moves < numrows*numrows; moves++)
	{
		playerturn = moves%2;

		if(playerturn == 0)
		{
			playerturn += 2;
		}

		if (playerturn == WHITEPLAYER)
		{
			mycolour = "White";
			oppcolour = "Red";
			myking = WHITEKING;
			oppking = REDKING;
			mysoldier = WHITESOLDIER;
			oppsoldier = REDSOLDIER;
			mymule = WHITEMULE;
			oppmule = REDMULE;
		}
		else
		{
			mycolour = "Red";
			oppcolour = "White";
			myking = REDKING;
			oppking = WHITEKING;
			mysoldier = REDSOLDIER;
			oppsoldier = WHITESOLDIER;
			mymule = REDMULE;
			oppmule = WHITEMULE;
		}
	
		move = CountMove1Squares(checker, numrows, playerturn, xIndicesMove, yIndicesMove);
		numjumps = CountJumps(checker, numrows, playerturn, xIndicesJump, yIndicesJump);

		if (move > 0 || numjumps > 0)
		{
			cout << mycolour << " takes a turn" << endl;
		}
		else 
		{
			char exitthingy;
			cout << mycolour << " is unable to move\nGAME OVER, " << oppcolour << " has won" << endl;
			cin >> exitthingy;
			exit(0);
		}
	
		do
		{
			cout << "Enter square number of the checker you want to move" << endl;

			if(!(cin >> entermove)) 
			{
				cerr << "ERROR: you did not enter an integer.\nTry again" << endl;
				cin.clear();
				cin.ignore(1000, '\n');
			}
			else
			{
				yindices = entermove/numrows;
				xindices = entermove%numrows;

				if(entermove < 0 || entermove > (numrows*numrows-1))
				{
					cerr << "ERROR: that square is not on the board.\nTry again" << endl;
					cin.clear();
					cin.ignore(1000, '\n');
				}
				else if( yindices == 0 && (xindices == 2 || xindices == 4)) // exception 
				{
					cerr << "ERROR: that square is empty.\nTry again" << endl;
					cin.clear();
					cin.ignore(1000, '\n');
				}
				else if(checker[yindices][xindices] == oppmule || checker[yindices][xindices] == oppsoldier || checker[yindices][xindices] == oppking) //5,4,6
				{
					cerr << "ERROR: that square contains an opponent's checker.\nTry again" << endl;
					cin.clear();
					cin.ignore(1000, '\n');
				}
				else if(checker[yindices][xindices] == NOPLAYER) //  empty space
				{
					cerr << "ERROR: that square is empty.\nTry again" << endl;
					cin.clear();
					cin.ignore(1000, '\n');
				}
				else if((CheckList(xIndicesJump,yIndicesJump, xindices, yindices) == false) && numjumps >0)
				{
					cerr << "ERROR: You can jump with another checker, you may not move your chosen checker.\nTry again" << endl;
					cout << "You can jump with checker on the following squares: ";

					for (int h=0; h < numjumps; h++)
					{
						cout << yIndicesJump[h]*numrows+ xIndicesJump[h]*numrows << " ";
					}
					cout << endl;
					continue;
					}
				else if( !(CheckList(xIndicesMove, yIndicesMove, xindices, yindices) == false) && numjumps <= 0)
				{
					cerr << "ERROR: There is no legal move for this checker.\nTry again" << endl;
					cin.clear();
					cin.ignore(1000, '\n');
					
				}
				else
				{
					valid = DONE;
					break;
				}
			}
		}while (valid!=DONE);
	
	
		valid = 1;
		valid2 = false;

		while(!valid2)
		{
			cout << "Enter square number of the square you want to move your checker to" << endl;

			if (!(cin >> aftermove))
			{
				cerr << "ERROR: you did not enter an integer\nTry again" << endl;
				cin.clear();
				cin.ignore(1000, '\n');
			}
			else
			{
				yindices = aftermove/numrows;
				xindices = aftermove%numrows;

				if ( aftermove < 0 || aftermove > (numrows*numrows-1))
				{
					cerr << "ERROR: It is not possible to move to a square that is not on the board\nTry again" << endl;
					cin.clear();
					cin.ignore(1000, '\n');
				}
				else if( checker[yindices][xindices] != NOPLAYER)
				{
					cerr << "ERROR: it is not possible to move to a square that is already occupied\nTry again" << endl;
					cin.clear();
					cin.ignore(1000,'\n');
				}
				else if( !(MakeMove(checker, numrows, playerturn, entermove, aftermove, jumped)))
				{
					cerr << "ERROR: moving to that square is not legal\nTry again" << endl;
					cin.clear();
					cin.ignore(1000, '\n');
				}
				else
				{
					valid2 = true;
					break;
				}
			}
		}

		while(jumped == true)
		{
			yindices = aftermove/numrows;
			xindices = aftermove%numrows;

			entermove = aftermove;

			if(IsJump(checker, numrows, playerturn, xindices, yindices))
			{
				do
				{
					jumped = false;
					cout << "You can jump again, Please enter the next square you wish to move your checker to" << endl;
					
					if( !(cin >> aftermove))
					{
						cerr << "You did not enter an integer\nTry again" << endl;
						cin.clear();
						cin.ignore(1000, '\n');
						nextyindices = aftermove/numrows;
						nextxindices = aftermove%numrows;
					}
					else if(aftermove > numrows*numrows || aftermove < 0)
					{
						cerr << "ERROR: It is not possible to move to a square that is not on the board\nTry again" << endl;
						cin.clear();
						cin.ignore(1000, '\n');
					}
					else if(checker[nextyindices][nextxindices] !=0)
					{
						cerr << "ERROR: It is not possible to move to a square that is already occupied\nTry again" << endl;
						cin.clear();
						cin.ignore(1000, '\n');
					}
					else if( abs(xindices - nextxindices) == 1 || abs(yindices - nextyindices) == 1)
					{
						cerr << "ERROR: You can jumo with this checker, you must jump not move 1 space.\nTry again" << endl;
						cin.clear();
						cin.ignore();
					}

					if(!(MakeMove(checker, numrows, playerturn, entermove, aftermove, jumped)))
					{
						cerr << "ERROR: moving to that square is not legal, try again" << endl;
					}
					else if(!(MakeMove(checker, numrows, playerturn, entermove, aftermove, jumped)))
					{
						cerr<< "ERROR: moving to that square is not legal\nTry again" << endl;
						cin.clear();
						cin.ignore();
					}
					else
					{
						valid2 = true;
						xindices = nextxindices;
						yindices = nextyindices;
					}	
				}while (valid2 == false);
			}
		}
	

		if (CheckWin(checker, numrows))
		{
			cout << "Enter any character to terminate the game then press the enter key"<< endl;
			cin.get();
			exit(0);
		}
		else if (!(CheckWin(checker, numrows)))
		{
			DisplayBoard(checker, numrows);
			cout << endl << endl << endl;
		}

		if (playerturn == WHITEPLAYER)
		{
			playerturn = REDPLAYER;
		}
		else
		{
			playerturn = WHITEPLAYER;
		}
	}
	return 0;
}

void InitializeBoard( int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard )
{
    for ( int i=0; i < numRowsInBoard; i++ ) // initialize array to 0
    {
        for (int j=0; j<numRowsInBoard; j++)
        {
            CMCheckersBoard[i][j] = 0;
        }
    }
    for (int i=0; i<numRowsInBoard; i++)
    {
            int num = numRowsInBoard-1;
            int num2 = (numRowsInBoard-2)/2;
            int num3 = num2 + 1;
        for (int j=0; j<numRowsInBoard; j++)
        {
            if (i==0 && (j%2) == 1) // first row and odd
            {
                CMCheckersBoard[i][j] = WHITEMULE; // white mule
            }
            else if ((i%2)==1 && i<num2 && (j%2)==0) // odd row & even column
            {
                CMCheckersBoard[i][j] = WHITESOLDIER;
            }
            else if ((i%2)==0 && i<num2 && (j%2)==1) // even row & odd column
            {
                CMCheckersBoard[i][j] = WHITESOLDIER;
            }
            else if ((i%2)==1 && i>num3 && (j%2)==0 && i!=num) // odd row & even column
            {
                CMCheckersBoard[i][j] = REDSOLDIER;
            }
            else if ((i%2)==0 && i>num3 && (j%2)==1) // even row & odd column
            {
                CMCheckersBoard[i][j] = REDSOLDIER;
            }
            else if (i==num && (j%2)==0)
            {
                CMCheckersBoard[i][j] = REDMULE;
            }
            else
            {
                CMCheckersBoard[i][j] = NOPLAYER;
            }
        }
    }
}
 
void DisplayBoard( int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard)
{
    for (int i=0; i<numRowsInBoard; i++)
    {
        for (int j=0; j<numRowsInBoard; j++)
        { 
            if (CMCheckersBoard[i][j] == 1)
            {
                cout << fixed << setw(4) << "WS";
 
            }
 
            else if (CMCheckersBoard[i][j] == 2)
            {
 
                cout << setw(4) << "WM";
 
            }
            else if (CMCheckersBoard[i][j] == 3)
            {
 
                cout << setw(4) << "WK";
 
            }
            else if (CMCheckersBoard[i][j] == 4)
            {
 
                cout << setw(4) << "RS";
            }
            else if (CMCheckersBoard[i][j] == 5)
            {
 
                cout << setw(4) << "RM";
 
            }
            else if (CMCheckersBoard[i][j] == 6)
            {
 
                cout << setw(4) << "RK";
 
            }
            else
            {
                int number = j+(i*numRowsInBoard);
                cout << setw(4) << number;
            }
        }
        cout << endl;
    }
}
 
int CountJumps( int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLocArray[], int yLocArray[] )
{
    for (int i = 0; i < MAX_PIECES; i++)
    {
        xLocArray[i] = -1;
        yLocArray[i] = -1;
    }
    int counter = 0;
   
    for (int i = 0; i < numRowsInBoard; i++)
    {
        for (int j = 0; j < numRowsInBoard; j++)
        {
            if (player == WHITEPLAYER && CMCheckersBoard[i][j] == WHITESOLDIER || CMCheckersBoard[i][j] == WHITEMULE || CMCheckersBoard[i][j] == WHITEKING)
            {
                if (IsJump(CMCheckersBoard, numRowsInBoard, 1, j, i))
                {
                    xLocArray[counter] = j;
                    yLocArray[counter] = i;
                    counter++;
                }
            }
            else if (player == REDPLAYER && CMCheckersBoard[i][j] == WHITESOLDIER || CMCheckersBoard[i][j] == REDMULE || CMCheckersBoard[i][j] == REDKING)
            {
                if (IsJump(CMCheckersBoard, numRowsInBoard, 2, j, i))
                {
                    xLocArray[counter] = j;
                    yLocArray[counter] = i;
                    counter++;
                }
            }
        }
    }
    return counter;
}

bool CheckList( int inArray1[], int inArray2[], int xIndex, int yIndex)
{
	for (int i =0; i < MAX_PIECES; i++)
	{
		if (inArray1[i] == xIndex && inArray2[i] == yIndex)
		{
			return true;
		}
	}
	return false;
}

bool IsJump( int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLoc, int yLoc)
{
    if (player == WHITEPLAYER) 
    {
        if (CMCheckersBoard[yLoc][xLoc] == WHITESOLDIER || CMCheckersBoard[yLoc][xLoc] == WHITEMULE || CMCheckersBoard[yLoc][xLoc] == WHITEKING )
        {
			if (xLoc == 0) // first column
			{
				if (yLoc < numRowsInBoard - 2 && (CMCheckersBoard[yLoc + 1][xLoc + 1] == REDSOLDIER || CMCheckersBoard[yLoc + 1][xLoc + 1] == REDMULE || CMCheckersBoard[yLoc + 1][xLoc + 1] == REDKING) )
				{
					if (CMCheckersBoard[yLoc + 2][xLoc + 2] == NOPLAYER)
					{
						return true;
					}
				}
				else if (yLoc < numRowsInBoard - 2 && (CMCheckersBoard[yLoc + 1][numRowsInBoard - 1] == REDSOLDIER || CMCheckersBoard[yLoc + 1][numRowsInBoard - 1] == REDMULE || CMCheckersBoard[yLoc + 1][numRowsInBoard - 1] == REDKING) )
				{
					if (CMCheckersBoard[yLoc + 2][numRowsInBoard - 2] == NOPLAYER)
					{
						return true;
					}
				}
				else if (CMCheckersBoard[yLoc][xLoc] == WHITEKING && yLoc > 1 && yLoc < numRowsInBoard)
				{
					if (CMCheckersBoard[yLoc - 1][xLoc + 1] == REDSOLDIER || CMCheckersBoard[yLoc - 1][xLoc + 1] == REDMULE || CMCheckersBoard[yLoc - 1][xLoc + 1] == REDKING)
					{
						if (CMCheckersBoard[yLoc - 2][xLoc + 2] == NOPLAYER)
						{
							return true;
						}
					}
					else if (CMCheckersBoard[yLoc - 1][numRowsInBoard - 1] == REDSOLDIER || CMCheckersBoard[yLoc - 1][numRowsInBoard - 1] == REDMULE || CMCheckersBoard[yLoc - 1][numRowsInBoard - 1] == REDKING)
					{
						if (CMCheckersBoard[yLoc - 2][numRowsInBoard - 2] == NOPLAYER)
						{
							return true;
						}
					}
				}
				else
				{
					return false;
				}
			}
			else if (xLoc == 1) // second column
			{
				if (yLoc < numRowsInBoard - 2 && (CMCheckersBoard[yLoc + 1][xLoc + 1] == REDSOLDIER || CMCheckersBoard[yLoc + 1][xLoc + 1] == REDMULE || CMCheckersBoard[yLoc + 1][xLoc + 1] == REDKING) )
				{
					if (CMCheckersBoard[yLoc + 2][xLoc + 2] == 0)
					{
						return true;
					}
				}
				else if (yLoc < numRowsInBoard - 2 && (CMCheckersBoard[yLoc + 1][xLoc - 1] == REDSOLDIER || CMCheckersBoard[yLoc + 1][xLoc - 1] == REDMULE || CMCheckersBoard[yLoc + 1][xLoc - 1] == REDKING) )
				{
					if (CMCheckersBoard[yLoc + 2][numRowsInBoard - 1] == NOPLAYER)
					{
						return true;
					}
				}
				else if (CMCheckersBoard[yLoc][xLoc] == WHITEKING && yLoc > 1 && yLoc < numRowsInBoard)
				{
					if (CMCheckersBoard[yLoc - 1][xLoc + 1] == REDSOLDIER || CMCheckersBoard[yLoc - 1][xLoc + 1] == REDMULE || CMCheckersBoard[yLoc - 1][xLoc + 1] == REDKING)
					{
						if (CMCheckersBoard[yLoc - 2][xLoc + 2] == NOPLAYER)
						{
							return true;
						}
					}
					else if (CMCheckersBoard[yLoc - 1][xLoc - 1] == REDSOLDIER || CMCheckersBoard[yLoc - 1][xLoc - 1] == REDMULE || CMCheckersBoard[yLoc - 1][xLoc - 1] == REDKING)
					{
						if (CMCheckersBoard[yLoc - 2][numRowsInBoard - 1] == NOPLAYER)
						{
							return true;
						}
					}
				}
				else
				{
					return false;
				}
			}
			else if (xLoc == numRowsInBoard - 1) //last column
			{
				if (yLoc < numRowsInBoard - 2 && (CMCheckersBoard[yLoc + 1][0] == REDSOLDIER || CMCheckersBoard[yLoc + 1][0] == REDMULE || CMCheckersBoard[yLoc + 1][0] == REDKING) )
				{
					if (CMCheckersBoard[yLoc + 2][1] == NOPLAYER)
					{
						return true;
					}
				}
				else if (yLoc < numRowsInBoard - 2 && (CMCheckersBoard[yLoc + 1][xLoc - 1] == REDSOLDIER || CMCheckersBoard[yLoc + 1][xLoc - 1] == REDMULE || CMCheckersBoard[yLoc + 1][xLoc - 1] == REDKING))
				{
					if (CMCheckersBoard[yLoc + 2][xLoc - 2] == NOPLAYER)
					{
						return true;
					}
				}
				else if (CMCheckersBoard[yLoc][xLoc] == WHITEKING && yLoc > 1 && yLoc < numRowsInBoard)
				{
					if (CMCheckersBoard[yLoc - 1][0] == REDSOLDIER || CMCheckersBoard[yLoc - 1][0] == REDMULE || CMCheckersBoard[yLoc - 1][0] == REDKING)
					{
						if (CMCheckersBoard[yLoc - 2][1] == NOPLAYER)
						{
							return true;
						}
					}
					else if (CMCheckersBoard[yLoc - 1][xLoc - 1] == REDSOLDIER || CMCheckersBoard[yLoc - 1][xLoc - 1] == REDMULE || CMCheckersBoard[yLoc - 1][xLoc - 1] == REDKING)
					{
						if (CMCheckersBoard[yLoc - 2][xLoc - 2] == NOPLAYER)
						{
							return true;
						}
					}
				}
				else
				{
					return false;
				}
			}
			else if (xLoc == numRowsInBoard - 2) //second last column
			{
				if (yLoc < numRowsInBoard - 2 && (CMCheckersBoard[yLoc + 1][xLoc + 1] == REDSOLDIER || CMCheckersBoard[yLoc + 1][xLoc + 1] == REDMULE || CMCheckersBoard[yLoc + 1][xLoc + 1] == REDKING) )
				{
					if (CMCheckersBoard[yLoc + 2][0] == NOPLAYER)
					{
						return true;
					}
				}
				else if (yLoc < numRowsInBoard - 2 && (CMCheckersBoard[yLoc + 1][xLoc - 1] == REDSOLDIER || CMCheckersBoard[yLoc + 1][xLoc - 1] == REDMULE || CMCheckersBoard[yLoc + 1][xLoc - 1] == REDKING))
				{
					if (CMCheckersBoard[yLoc + 2][xLoc - 2] == NOPLAYER)
					{
						return true;
					}
				}
				else if (CMCheckersBoard[yLoc][xLoc] == WHITEKING && yLoc > 1 && yLoc < numRowsInBoard)
				{
					if (CMCheckersBoard[yLoc - 1][xLoc + 1] == REDSOLDIER || CMCheckersBoard[yLoc - 1][xLoc + 1] == REDMULE || CMCheckersBoard[yLoc - 1][xLoc + 1] == REDKING)
					{
						if (CMCheckersBoard[yLoc - 2][0] == NOPLAYER)
						{
							return true;
						}
					}
					else if (CMCheckersBoard[yLoc - 1][xLoc - 1] == REDSOLDIER || CMCheckersBoard[yLoc - 1][xLoc - 1] == REDMULE || CMCheckersBoard[yLoc - 1][xLoc - 1] == REDKING)
					{
						if (CMCheckersBoard[yLoc - 2][xLoc - 2] == NOPLAYER)
						{
							return true;
						}
					}
				}
				else
				{
					return false;
				}
			}
			else
			{
				if (yLoc < numRowsInBoard - 2 && (CMCheckersBoard[yLoc + 1][xLoc + 1] == REDSOLDIER || CMCheckersBoard[yLoc + 1][xLoc + 1] == REDMULE || CMCheckersBoard[yLoc + 1][xLoc + 1] == REDKING))
				{
					if (CMCheckersBoard[yLoc + 2][xLoc + 2] == NOPLAYER)
					{
						return true;
					}
				}
				else if (yLoc < numRowsInBoard - 2 && (CMCheckersBoard[yLoc + 1][xLoc - 1] == REDSOLDIER || CMCheckersBoard[yLoc + 1][xLoc - 1] == REDMULE || CMCheckersBoard[yLoc + 1][xLoc - 1] == REDKING))
				{
					if (CMCheckersBoard[yLoc + 2][xLoc - 2] == NOPLAYER)
					{
						return true;
					}
				}
				else if (CMCheckersBoard[yLoc][xLoc] == WHITEKING && yLoc > 1 && yLoc < numRowsInBoard)
				{
					if (CMCheckersBoard[yLoc - 1][xLoc + 1] == REDSOLDIER || CMCheckersBoard[yLoc - 1][xLoc + 1] == REDMULE || CMCheckersBoard[yLoc - 1][xLoc + 1] == REDKING)
					{
						if (CMCheckersBoard[yLoc - 2][xLoc + 2] == NOPLAYER)
						{
							return true;
						}
					}
					else if (CMCheckersBoard[yLoc - 1][xLoc - 1] == REDSOLDIER || CMCheckersBoard[yLoc - 1][xLoc - 1] == REDMULE || CMCheckersBoard[yLoc - 1][xLoc - 1] == REDKING)
					{
						if (CMCheckersBoard[yLoc - 2][xLoc - 2] == NOPLAYER)
						{
							return true;
						}
					}
				}
				else
				{
					return false;
				}
			}
        }
    }
    else if (player == REDPLAYER)
    {
        if (CMCheckersBoard[yLoc][xLoc] == REDSOLDIER || CMCheckersBoard[yLoc][xLoc] == REDMULE || CMCheckersBoard[yLoc][xLoc] == REDKING )
        {
			if (xLoc == 0) // first column
			{
				if (yLoc > 1 && (CMCheckersBoard[yLoc - 1][xLoc + 1] == WHITESOLDIER || CMCheckersBoard[yLoc - 1][xLoc + 1] == WHITEMULE || CMCheckersBoard[yLoc - 1][xLoc + 1] == WHITEKING) )
				{
					if (CMCheckersBoard[yLoc - 2][xLoc + 2] == NOPLAYER)
					{
						return true;
					}
				}
				else if (yLoc > 1 && (CMCheckersBoard[yLoc - 1][numRowsInBoard - 1] == WHITESOLDIER || CMCheckersBoard[yLoc - 1][numRowsInBoard - 1] == WHITEMULE || CMCheckersBoard[yLoc - 1][numRowsInBoard - 1] == WHITEKING) )
				{
					if (CMCheckersBoard[yLoc - 2][numRowsInBoard - 2] == NOPLAYER)
					{
						return true;
					}
				}
				else if (CMCheckersBoard[yLoc][xLoc] == REDKING && yLoc < numRowsInBoard - 2)
				{
					if (CMCheckersBoard[yLoc + 1][xLoc + 1] == WHITESOLDIER || CMCheckersBoard[yLoc + 1][xLoc + 1] == WHITEMULE || CMCheckersBoard[yLoc + 1][xLoc + 1] == WHITEKING)
					{
						if (CMCheckersBoard[yLoc + 2][xLoc + 2] == NOPLAYER)
						{
							return true;
						}
					}
					else if (CMCheckersBoard[yLoc + 1][numRowsInBoard - 1] == WHITESOLDIER || CMCheckersBoard[yLoc + 1][numRowsInBoard - 1] == WHITEMULE || CMCheckersBoard[yLoc + 1][numRowsInBoard - 1] == WHITEKING)
					{
						if (CMCheckersBoard[yLoc + 2][numRowsInBoard - 2] == NOPLAYER)
						{
							return true;
						}
					}
				}
				else
				{
					return false;
				}
			}
			else if (xLoc == 1) // second column
			{
				if (yLoc > 1 && (CMCheckersBoard[yLoc - 1][xLoc + 1] == WHITESOLDIER || CMCheckersBoard[yLoc - 1][xLoc + 1] == WHITEMULE || CMCheckersBoard[yLoc - 1][xLoc + 1] == WHITEKING) )
				{
					if (CMCheckersBoard[yLoc - 2][xLoc + 2] == 0)
					{
						return true;
					}
				}
				else if (yLoc > 1 && (CMCheckersBoard[yLoc - 1][xLoc - 1] == WHITESOLDIER || CMCheckersBoard[yLoc - 1][xLoc - 1] == WHITEMULE || CMCheckersBoard[yLoc - 1][xLoc - 1] == WHITEKING) )
				{
					if (CMCheckersBoard[yLoc - 2][numRowsInBoard - 1] == NOPLAYER)
					{
						return true;
					}
				}
				else if (CMCheckersBoard[yLoc][xLoc] == REDKING && yLoc < numRowsInBoard - 2)
				{
					if (CMCheckersBoard[yLoc + 1][xLoc + 1] == WHITESOLDIER || CMCheckersBoard[yLoc + 1][xLoc + 1] == WHITEMULE || CMCheckersBoard[yLoc + 1][xLoc + 1] == WHITEKING)
					{
						if (CMCheckersBoard[yLoc + 2][xLoc + 2] == NOPLAYER)
						{
							return true;
						}
					}
					else if (CMCheckersBoard[yLoc + 1][xLoc - 1] == WHITESOLDIER || CMCheckersBoard[yLoc + 1][xLoc - 1] == WHITEMULE || CMCheckersBoard[yLoc + 1][xLoc - 1] == WHITEKING)
					{
						if (CMCheckersBoard[yLoc + 2][numRowsInBoard - 1] == NOPLAYER)
						{
							return true;
						}
					}
				}
				else
				{
					return false;
				}
			}
			else if (xLoc == numRowsInBoard - 1) // last column
			{
				if (yLoc > 1 && (CMCheckersBoard[yLoc - 1][0] == WHITESOLDIER || CMCheckersBoard[yLoc - 1][0] == WHITEMULE || CMCheckersBoard[yLoc - 1][0] == WHITEKING) )
				{
					if (CMCheckersBoard[yLoc - 2][1] == NOPLAYER)
					{
						return true;
					}
				}
				else if (yLoc > 1 && (CMCheckersBoard[yLoc - 1][xLoc - 1] == WHITESOLDIER || CMCheckersBoard[yLoc - 1][xLoc - 1] == WHITEMULE || CMCheckersBoard[yLoc - 1][xLoc - 1] == WHITEKING))
				{
					if (CMCheckersBoard[yLoc - 2][xLoc - 2] == NOPLAYER)
					{
						return true;
					}
				}
				else if (CMCheckersBoard[yLoc][xLoc] == REDKING && yLoc < numRowsInBoard - 2)
				{
					if (CMCheckersBoard[yLoc + 1][0] == WHITESOLDIER || CMCheckersBoard[yLoc + 1][0] == WHITEMULE || CMCheckersBoard[yLoc + 1][0] == WHITEKING)
					{
						if (CMCheckersBoard[yLoc + 2][1] == NOPLAYER)
						{
							return true;
						}
					}
					else if (CMCheckersBoard[yLoc + 1][xLoc - 1]  == WHITESOLDIER || CMCheckersBoard[yLoc + 1][xLoc - 1] == WHITEMULE || CMCheckersBoard[yLoc + 1][xLoc - 1] == WHITEKING)
					{
						if (CMCheckersBoard[yLoc + 2][xLoc - 2] == NOPLAYER)
						{
							return true;
						}
					}
				}
				else
				{
					return false;
				}
			}
			else if (xLoc == numRowsInBoard - 2) //second last column
			{
				if (yLoc > 1 && (CMCheckersBoard[yLoc - 1][xLoc + 1] == WHITESOLDIER || CMCheckersBoard[yLoc - 1][xLoc + 1] == WHITEMULE || CMCheckersBoard[yLoc - 1][xLoc + 1] == WHITEKING) )
				{
					if (CMCheckersBoard[yLoc - 2][0] == NOPLAYER)
					{
						return true;
					}
				}
				else if (yLoc > 1 && (CMCheckersBoard[yLoc - 1][xLoc - 1] == WHITESOLDIER || CMCheckersBoard[yLoc - 1][xLoc - 1] == WHITEMULE || CMCheckersBoard[yLoc - 1][xLoc - 1] == WHITEKING))
				{
					if (CMCheckersBoard[yLoc - 2][xLoc - 2] == NOPLAYER)
					{
						return true;
					}
				}
				else if (CMCheckersBoard[yLoc][xLoc] == REDKING && yLoc < numRowsInBoard - 2)
				{
					if (CMCheckersBoard[yLoc + 1][xLoc + 1] == WHITESOLDIER || CMCheckersBoard[yLoc + 1][xLoc + 1] == WHITEMULE || CMCheckersBoard[yLoc + 1][xLoc + 1] == WHITEKING)
					{
						if (CMCheckersBoard[yLoc + 2][0] == NOPLAYER)
						{
							return true;
						}
					}
					else if (CMCheckersBoard[yLoc + 1][xLoc - 1] == WHITESOLDIER || CMCheckersBoard[yLoc + 1][xLoc - 1] == WHITEMULE || CMCheckersBoard[yLoc + 1][xLoc - 1] == WHITEKING)
					{
						if (CMCheckersBoard[yLoc + 2][xLoc - 2] == NOPLAYER)
						{
							return true;
						}
					}
				}
				else
				{
					return false;
				}
			}
			else
			{
				if (yLoc > 1 && (CMCheckersBoard[yLoc - 1][xLoc + 1] == WHITESOLDIER || CMCheckersBoard[yLoc - 1][xLoc + 1] == WHITEMULE || CMCheckersBoard[yLoc - 1][xLoc + 1] == WHITEKING))
				{
					if (CMCheckersBoard[yLoc - 2][xLoc + 2] == NOPLAYER)
					{
						return true;
					}
				}
				else if (yLoc > 1 && (CMCheckersBoard[yLoc - 1][xLoc - 1] == WHITESOLDIER || CMCheckersBoard[yLoc - 1][xLoc - 1] == WHITEMULE || CMCheckersBoard[yLoc - 1][xLoc - 1] == WHITEKING))
				{
					if (CMCheckersBoard[yLoc - 2][xLoc - 2] == NOPLAYER)
					{
						return true;
					}
				}
				else if (CMCheckersBoard[yLoc][xLoc] == REDKING && yLoc < numRowsInBoard - 2)
				{
					if (CMCheckersBoard[yLoc + 1][xLoc + 1] == WHITESOLDIER || CMCheckersBoard[yLoc + 1][xLoc + 1] == WHITEMULE || CMCheckersBoard[yLoc + 1][xLoc + 1] == WHITEKING)
					{
						if (CMCheckersBoard[yLoc + 2][xLoc + 2] == NOPLAYER)
						{
							return true;
						}
					}
					else if (CMCheckersBoard[yLoc + 1][xLoc - 1] == WHITESOLDIER || CMCheckersBoard[yLoc + 1][xLoc - 1] == WHITEMULE || CMCheckersBoard[yLoc + 1][xLoc - 1] == WHITEKING)
					{
						if (CMCheckersBoard[yLoc + 2][xLoc - 2] == NOPLAYER)
						{
							return true;
						}
					}
				}
				else
				{
					return false;
				}
			}
        }
    }
	return false;
}

bool IsMove1Square( int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLoc, int yLoc)
{
	if (player == WHITEPLAYER)
	{
		if (yLoc < numRowsInBoard && (CMCheckersBoard[yLoc][xLoc] == WHITEMULE || CMCheckersBoard[yLoc][xLoc] == WHITESOLDIER || CMCheckersBoard[yLoc][xLoc] == WHITEKING))
		{
			if (xLoc == 0) // leftmost column
			{
				if (CMCheckersBoard[yLoc+1][xLoc+1] == NOPLAYER)
				{
					return true;
				}
				else if (CMCheckersBoard[yLoc+1][numRowsInBoard-1] == NOPLAYER)
				{
					return true;
				}
				else if (CMCheckersBoard[yLoc][xLoc] == WHITEKING)
				{
					if (CMCheckersBoard[yLoc-1][xLoc+1] == NOPLAYER)
					{
						return true;
					}
					else if (CMCheckersBoard[yLoc-1][numRowsInBoard-1] == NOPLAYER)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
			}
			else if (xLoc == numRowsInBoard - 1) // rightmost column
			{
				if (CMCheckersBoard[yLoc+1][xLoc-1] == NOPLAYER)
				{
					return true;
				}	
				else if (CMCheckersBoard[yLoc+1][0] == NOPLAYER)
				{
					return true;
				}
				else if (CMCheckersBoard[yLoc][xLoc] == WHITEKING)
				{
					if (CMCheckersBoard[yLoc-1][xLoc-1] == NOPLAYER)
					{
						return true;
					}
					else if (CMCheckersBoard[yLoc-1][0] == NOPLAYER)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
			}
			else
			{
				if (CMCheckersBoard[yLoc+1][xLoc+1] == NOPLAYER)
				{
					return true;
				}
				else if (CMCheckersBoard[yLoc+1][xLoc-1] == NOPLAYER)
				{
					return true;
				}
				else if(CMCheckersBoard[yLoc][xLoc] == WHITEKING)
				{
					if(yLoc < numRowsInBoard && CMCheckersBoard[yLoc-1][xLoc+1] == NOPLAYER)
					{
						return true;
					}
					else if(yLoc < numRowsInBoard && CMCheckersBoard[yLoc-1][xLoc-1] == NOPLAYER)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
				else
				{
					return false;
				}
			}
		}
		else
		{
			return false;
		}
	}
		
	else if (player == REDPLAYER)
	{
		if (yLoc < numRowsInBoard && (CMCheckersBoard[yLoc][xLoc] == REDMULE || CMCheckersBoard[yLoc][xLoc] == REDSOLDIER || CMCheckersBoard[yLoc][xLoc] == REDKING))
		{
			if (xLoc == 0) // leftmost column
			{
				if (CMCheckersBoard[yLoc-1][xLoc+1] == NOPLAYER)
				{
					return true;
				}
				else if(CMCheckersBoard[yLoc-1][numRowsInBoard-1] == NOPLAYER)
				{
					return true;
				}
				else if (CMCheckersBoard[yLoc][xLoc] == REDKING)
				{
					if (CMCheckersBoard[yLoc+1][xLoc+1] == NOPLAYER)
					{
						return true;
					}
					else if (CMCheckersBoard[yLoc+1][numRowsInBoard-1] == NOPLAYER)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
			}
			else if (xLoc == numRowsInBoard - 1) // rightmost column
			{
				if (CMCheckersBoard[yLoc-1][xLoc-1] == NOPLAYER)
				{
					return true;
				}	
				else if (CMCheckersBoard[yLoc-1][0] == NOPLAYER)
				{
					return true;
				}
				else if (CMCheckersBoard[yLoc][xLoc] == REDKING)
				{
					if (CMCheckersBoard[yLoc+1][xLoc+1] == NOPLAYER)
					{
						return true;
					}
					else if (CMCheckersBoard[yLoc+1][0] == NOPLAYER)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
			}
			else
			{
				if (CMCheckersBoard[yLoc-1][xLoc-1] == NOPLAYER)
				{
					return true;
				}
				else if (CMCheckersBoard[yLoc-1][xLoc+1] == NOPLAYER)
				{
					return true;
				}
				else if (CMCheckersBoard[yLoc][xLoc] == WHITEKING)
				{
					if (CMCheckersBoard[yLoc+1][xLoc+1] == NOPLAYER)
					{
						return true;
					}
					else if (CMCheckersBoard[yLoc+1][xLoc-1] == NOPLAYER)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
				else
				{
					return false;
				}
			}
		}	
		else
		{
			return false;
		}
	}
	return false;
}

int CountMove1Squares( int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLocArray[],  int yLocArray[] )
{
	for (int i=0; i<numRowsInBoard; i++) // initialize at -1
	{
			xLocArray[i] = -1;
			yLocArray[i] = -1;
	}
	int amount = 0; // the numb of checkers that can be moved one square
	for (int i=0; i<numRowsInBoard; i++)
	{
		for (int j=0; j<numRowsInBoard; j++)
	 	{
			if(player == WHITEPLAYER)
			{
				// need ismove1square function
				if (CMCheckersBoard[i][j] == WHITESOLDIER || CMCheckersBoard[i][j] == WHITEMULE || CMCheckersBoard[i][j] == WHITEKING )
				{
					if ( IsMove1Square(CMCheckersBoard, numRowsInBoard, player, i, j) )
					{
						amount++;
					}
				}
			}
			else if(player == REDPLAYER)
			{
				if (CMCheckersBoard[i][j] == REDSOLDIER || CMCheckersBoard[i][j] == REDMULE || CMCheckersBoard[i][j] == REDKING )
				{
					if ( IsMove1Square(CMCheckersBoard, numRowsInBoard, player, i, j) )
					{
						amount++;
					}
				}
			}
		} 
	}
	return amount;
}

bool CheckWin( int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard)
{
	int redSoldierAmt = 0;
	int redMuleAmt = 0;
	int redKingAmt = 0;
	int whiteSoldierAmt = 0;
	int whiteMuleAmt = 0;
	int whiteKingAmt = 0;

	for (int i=0; i<numRowsInBoard; i++)
	{
		for (int j=0; j<numRowsInBoard; j++)
	 	{
			if ( CMCheckersBoard[i][j] == REDSOLDIER )
			{
				redSoldierAmt++;
			}
			else if ( CMCheckersBoard[i][j] == REDMULE )
			{
				redMuleAmt++;
			}
			else if ( CMCheckersBoard[i][j] == REDKING )
			{
				redKingAmt++;
			}
			else if ( CMCheckersBoard[i][j] == WHITESOLDIER )
			{
				whiteSoldierAmt++;
			}
			else if ( CMCheckersBoard[i][j] == WHITEMULE )
			{
				whiteMuleAmt++;
			}
			else if ( CMCheckersBoard[i][j] == WHITEKING )
			{
				whiteKingAmt++;
			}
		}
	}

	if ( redMuleAmt == 0 )
	{
		cout << "The Red Player has won the game by losing all of the Red Mules";
		return true;
	}
	if ( whiteMuleAmt == 0 )
	{
		cout << "The White Player has won the game by losing all of the White Mules";
		return true;
	}
	if ( redSoldierAmt == 0 && redKingAmt == 0 )
	{
		cout << "The White Player has won by capturing all of the red players soldiers and kings";
		return true;
	}
	if ( whiteSoldierAmt == 0 && whiteKingAmt == 0 )
	{
		cout << "The Red Player has won by capturing all of the white players soldiers and kings";
		return true;
	}

	return false;

}

bool MakeMove( int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int fromSquareNum, int toSquareNum, bool &jumped )
{
	char c = ' ';
	int xdistance = 0;
	int ydistance = 0;
	int temp = 0;
	int pieceInBetween=0;
	bool CanMove =0;

	xdistance = abs((fromSquareNum%numRowsInBoard) - (toSquareNum%numRowsInBoard));
	ydistance = abs((fromSquareNum/numRowsInBoard)- (toSquareNum/numRowsInBoard));
	pieceInBetween = (fromSquareNum + toSquareNum )/ 2;
	
	//distance between two pieces are greater than 2
	if ((xdistance > 2 && xdistance < numRowsInBoard-2)|| ydistance >2)
	{
		cerr<<"ERROR; Illegal move "<<endl;
		CanMove = 0;
	}
	//if selected destination is the same place
	else if (xdistance == 0 || ydistance == 0||(xdistance == 1 && ydistance == 2)||(xdistance == 2&&ydistance == 1))
	{
		cerr<<"ERROR; Illegal move "<<endl;
		CanMove = 0;
	}
	// jumping
	else if (xdistance == 2 && ydistance == 2 && CMCheckersBoard [fromSquareNum/numRowsInBoard][fromSquareNum%numRowsInBoard] >= 1 &&CMCheckersBoard [fromSquareNum/numRowsInBoard][fromSquareNum%numRowsInBoard] <= 3&& (CMCheckersBoard[pieceInBetween/numRowsInBoard][pieceInBetween%numRowsInBoard]>=0 && CMCheckersBoard[pieceInBetween/numRowsInBoard][pieceInBetween%numRowsInBoard]<=3))
	{
		cerr<<"ERROR; Illegal move "<<endl;
		CanMove = 0;		
	}
	else if (xdistance == 2 && ydistance == 2 && CMCheckersBoard [fromSquareNum/numRowsInBoard][fromSquareNum%numRowsInBoard] >= 4 &&CMCheckersBoard [fromSquareNum/numRowsInBoard][fromSquareNum%numRowsInBoard] <= 6&& (CMCheckersBoard[pieceInBetween/numRowsInBoard][pieceInBetween%numRowsInBoard]>=4 && CMCheckersBoard[pieceInBetween/numRowsInBoard][pieceInBetween%numRowsInBoard]<=6 || CMCheckersBoard[pieceInBetween/numRowsInBoard][pieceInBetween%numRowsInBoard]== 0))
	{
		cerr<<"ERROR; Illegal move "<<endl;
		CanMove = 0;	
	}
	// if white going wrong direction
	else if ((CMCheckersBoard [fromSquareNum/numRowsInBoard][fromSquareNum%numRowsInBoard] == 1 && ((fromSquareNum/numRowsInBoard)- (toSquareNum/numRowsInBoard) > 0 ))|| (CMCheckersBoard[fromSquareNum/numRowsInBoard][fromSquareNum%numRowsInBoard]== 2 && ((fromSquareNum/numRowsInBoard)- (toSquareNum/numRowsInBoard) > 0)))
	{
			cerr<<"Error;  Illegal move "<<endl;
			CanMove = 0;
	}
	//if red going wrong direction
	else if ((CMCheckersBoard [fromSquareNum/numRowsInBoard][fromSquareNum%numRowsInBoard] == 4 && ((fromSquareNum/numRowsInBoard)- (toSquareNum/numRowsInBoard) < 0 ))|| (CMCheckersBoard[fromSquareNum/numRowsInBoard][fromSquareNum%numRowsInBoard]== 5 && ((fromSquareNum/numRowsInBoard)- (toSquareNum/numRowsInBoard) < 0)))
	{
		cerr<<"Error;  Illegal move "<<endl;
		CanMove = 1;
	}
	//make move
	else 
	{
		CanMove = 1;
		//if moving one square
		if (xdistance == 1 && ydistance == 1)
		{
			temp = CMCheckersBoard [fromSquareNum/numRowsInBoard][fromSquareNum%numRowsInBoard];
			CMCheckersBoard [fromSquareNum/numRowsInBoard][fromSquareNum%numRowsInBoard] = CMCheckersBoard [toSquareNum/numRowsInBoard][toSquareNum%numRowsInBoard];
			CMCheckersBoard [toSquareNum/numRowsInBoard][toSquareNum%numRowsInBoard]=temp;
		}
		//if jumping
		if (xdistance == 2 && ydistance == 2)
		{
			jumped =1;
			temp = CMCheckersBoard [fromSquareNum/numRowsInBoard][fromSquareNum%numRowsInBoard];
			CMCheckersBoard [fromSquareNum/numRowsInBoard][fromSquareNum%numRowsInBoard] = CMCheckersBoard [toSquareNum/numRowsInBoard][toSquareNum%numRowsInBoard];
			CMCheckersBoard [toSquareNum/numRowsInBoard][toSquareNum%numRowsInBoard]=temp;

			CMCheckersBoard[pieceInBetween/numRowsInBoard][pieceInBetween%numRowsInBoard]=0;
		}
		//if moving and the checker is at the edge
		if (ydistance == 1 && xdistance ==(numRowsInBoard-1))
		{
			temp = CMCheckersBoard [fromSquareNum/numRowsInBoard][fromSquareNum%numRowsInBoard];
			CMCheckersBoard [fromSquareNum/numRowsInBoard][fromSquareNum%numRowsInBoard] = CMCheckersBoard [toSquareNum/numRowsInBoard][toSquareNum%numRowsInBoard];
			CMCheckersBoard [toSquareNum/numRowsInBoard][toSquareNum%numRowsInBoard]=temp;
		}
		// if jumping and the checker is at the edge
		if (ydistance == 2 && xdistance == (numRowsInBoard-2))
		{
			jumped = 1;
			if (player == 1)
			{
				temp = CMCheckersBoard [fromSquareNum/numRowsInBoard][fromSquareNum%numRowsInBoard];
				CMCheckersBoard [fromSquareNum/numRowsInBoard][fromSquareNum%numRowsInBoard] = CMCheckersBoard [toSquareNum/numRowsInBoard][toSquareNum%numRowsInBoard];
				CMCheckersBoard [toSquareNum/numRowsInBoard][toSquareNum%numRowsInBoard]=temp;
				if (fromSquareNum%numRowsInBoard== 0)
				{
					CMCheckersBoard [fromSquareNum/numRowsInBoard+1][numRowsInBoard-1]= 0;
				}
				else if (fromSquareNum%numRowsInBoard == numRowsInBoard-1)
				{
					CMCheckersBoard [fromSquareNum/numRowsInBoard+1][0] = 0;
				}
				else if (fromSquareNum%numRowsInBoard==1)
				{
					CMCheckersBoard [fromSquareNum/numRowsInBoard+1][0]= 0;
				}
				else if (fromSquareNum%numRowsInBoard == numRowsInBoard-2)
				{
					CMCheckersBoard [fromSquareNum/numRowsInBoard+1][numRowsInBoard-1]= 0;
				}
			}
			if (player == 2)
			{
				temp = CMCheckersBoard [fromSquareNum/numRowsInBoard][fromSquareNum%numRowsInBoard];
				CMCheckersBoard [fromSquareNum/numRowsInBoard][fromSquareNum%numRowsInBoard] = CMCheckersBoard [toSquareNum/numRowsInBoard][toSquareNum%numRowsInBoard];
				CMCheckersBoard [toSquareNum/numRowsInBoard][toSquareNum%numRowsInBoard]=temp;
				if (fromSquareNum%numRowsInBoard== 0)
				{
					CMCheckersBoard [fromSquareNum/numRowsInBoard-1][numRowsInBoard-1]= 0;
				}
				else if (fromSquareNum%numRowsInBoard == numRowsInBoard-1)
				{
					CMCheckersBoard [fromSquareNum/numRowsInBoard-1][0] = 0;
				}
				else if (fromSquareNum%numRowsInBoard==1)
				{
					CMCheckersBoard [fromSquareNum/numRowsInBoard-1][0]= 0;
				}
				else if (fromSquareNum%numRowsInBoard == numRowsInBoard-2)
				{
					CMCheckersBoard [fromSquareNum/numRowsInBoard-1][numRowsInBoard-1]= 0;
				}
			}
		}
	}
	
	if (CMCheckersBoard [toSquareNum/numRowsInBoard][toSquareNum%numRowsInBoard]==1||CMCheckersBoard [toSquareNum/numRowsInBoard][toSquareNum%numRowsInBoard]==2)
	{
		if (toSquareNum/numRowsInBoard== numRowsInBoard-1)
		{
			if (CMCheckersBoard [toSquareNum/numRowsInBoard][toSquareNum%numRowsInBoard]==1)
			{
				CMCheckersBoard [toSquareNum/numRowsInBoard][toSquareNum%numRowsInBoard]=3;
			}
			else if (CMCheckersBoard [toSquareNum/numRowsInBoard][toSquareNum%numRowsInBoard]==2)
			{
				CMCheckersBoard [toSquareNum/numRowsInBoard][toSquareNum%numRowsInBoard]=3;
				CanMove = 0;
				cout<<"White has created a Mule King, Red wins the game"<<endl;
				cout<<"Enter any character to terminate the game then press the enter key"<<endl;
				cin>>c;
				exit (3);
			}
		}
	}
	if (CMCheckersBoard [toSquareNum/numRowsInBoard][toSquareNum%numRowsInBoard]==4||CMCheckersBoard [toSquareNum/numRowsInBoard][toSquareNum%numRowsInBoard]==5)
	{
		if (toSquareNum/numRowsInBoard== 0)
		{
			if (CMCheckersBoard [toSquareNum/numRowsInBoard][toSquareNum%numRowsInBoard]==4)
			{
				CMCheckersBoard [toSquareNum/numRowsInBoard][toSquareNum%numRowsInBoard]=6;
			}
			else if (CMCheckersBoard [toSquareNum/numRowsInBoard][toSquareNum%numRowsInBoard]==5)
			{
				CMCheckersBoard [toSquareNum/numRowsInBoard][toSquareNum%numRowsInBoard]=3;
				CanMove = 0;
				cout<<"Red has created a Mule King,  White wins the game"<<endl;
				cout<<"Enter any character to terminate the game then press the enter key"<<endl;
				cin>>c;
				exit (4);
			}
		}
	}

return (CanMove);
}
