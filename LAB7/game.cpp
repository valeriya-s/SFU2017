#include <iostream>
#include <iomanip>
#include <math.h>
#include <fstream>
#include <string>

using namespace std;

void PrintGen(char lifeBoard[][40], ostream& outStream, 
			  int numRowsInBoard, int numColsInBoard, int generationNum);

void NextGen(char lifeBoard[][40], int numRowsInBoard, int numsColsInBoard);

int main()
{
	const int MAX_RANGE=40;
	const int MIN_RANGE=0;
	const char noOrg='.';
	const char yesOrg='X';

	ifstream inputFile;
	ofstream outputFile;
	char dataInput[100]={'\0'};
	char dataOutput[100]={'\0'};
	int rows;
	int columns;
	int numGens=0;
	char life[MAX_RANGE][MAX_RANGE] = {{NULL}, {NULL}};
	int colmnBorderCheck;
	int rowBorderCheck;

	cout << "Enter the name of the input file: ";
	cin >> dataInput;
	inputFile.open(dataInput);

	if ( inputFile.fail() )
	{
		cerr << "ERROR: input file not opened correctly";
		return 1;
	}

	cout << "Enter the name of the output file: ";
	cin >> dataOutput;
	outputFile.open(dataOutput);

	if ( outputFile.fail() )
	{
		cerr << "ERROR: ouput file not opened correctly";
		return 2;
	}

	if ( !(inputFile >> rows) )
	{
		cerr << "ERROR: Cannot read number of rows";
		return 3;
	}

	if ( rows>MAX_RANGE || rows<MIN_RANGE )
	{
		cerr << "ERROR: Read an illegal number of rows for the board";
		return 4;
	}

	if ( !(inputFile >> columns) )
	{
		cerr << "ERROR: Cannot read number of columns";
		return 5;
	}

	if ( columns>MAX_RANGE || columns<MIN_RANGE )
	{
		cerr << "ERROR: Read an illegal number of columns for the board";
		return 6;
	}

	if ( !(inputFile >> numGens) )
	{
		cerr << "ERROR: Cannot read the number of generations";
		return 7;
	}

	if ( numGens>MAX_RANGE || numGens<MIN_RANGE )
	{
		cerr << "ERROR: Read an illegal number of generations";
		return 8;
	}

	colmnBorderCheck=columns-1;
	rowBorderCheck=rows-1;

	for (int r=0; r<rows; r++)
	{
		for (int c=0; c<columns; c++)
		{
			if ( !(inputFile >> life[r][c]) )
			{
				cerr << "ERROR: Not enough data in the input file";
				return 9;
			}
			if ( !(life[r][c] == noOrg || life[r][c] == yesOrg) )
			{
				cout << life[r][c] << endl;
				cerr << "ERROR: Input data for initial board is incorrect" << endl;
				cerr << "Location (" << r << ", " << c << ") is not valid";
				return 10;
			}
			if ( c == colmnBorderCheck || r == MIN_RANGE || c == MIN_RANGE || r == rowBorderCheck )
			{
				if ( life[r][c] == yesOrg )
				{
					cerr << "ERROR: organisms are present in the border of the board, ";
					cerr << "please correct your input file";
					return 11;
				}
			}
		}
	}

	PrintGen(life, cout, rows, columns, numGens);
	// PrintGen(life, outputFile, rows, columns, numGens);

	cout << endl << endl << "ho" << endl << endl;

	NextGen(life, rows, columns);

	PrintGen(life, cout, rows, columns, numGens);

	inputFile.close();
	outputFile.close();

	return 0;

}

void PrintGen(char lifeBoard[][40], ostream& outStream, 
			  int numRowsInBoard, int numColsInBoard, int generationNum)
{
	cout << "LIFE initial game board" << endl;
	for (int r=0; r<numRowsInBoard; r++)
	{	
		for (int c=0; c<numColsInBoard; c++)
		{
			cout << lifeBoard[r][c] << " ";
		}
		cout << endl;
	}
	cout << endl << endl << endl;
}

void NextGen(char lifeBoard[][40], int numRowsInBoard, int numColsInBoard)
{
	int colsMinus=numColsInBoard-2;
	int rowsMinus=numRowsInBoard-2;
	int cPlus;
	int rPlus;
	int cMinus;
	int rMinus;
	int xNeighbours=0;

	const char x='X';
	const char DOT='.';
	const int THREE=3;
	const int TWO=2;

	int nextGenBoard[39][39]={{NULL},{NULL}};
	
	for (int r=1; r<rowsMinus; r++)
	{
		rMinus=r-1;
		rPlus=r+1;
		for (int c=1; c<colsMinus; c++)
		{
			cMinus=c-1;
			cPlus=c+1;
			
			if ( lifeBoard[rPlus][cPlus] == x )
			{
				xNeighbours++;
			}
			if ( lifeBoard[rPlus][c] == x )
			{
				xNeighbours++;
			}
			if ( lifeBoard[rPlus][cMinus] == x )
			{
				xNeighbours++;
			}
			if ( lifeBoard[r][cMinus] == x )
			{
				xNeighbours++;
			}
			if ( lifeBoard[r][cPlus] == x )
			{
				xNeighbours++;
			}
			if ( lifeBoard[rMinus][cMinus] == x )
			{
				xNeighbours++;
			}
			if ( lifeBoard[rMinus][c] == x )
			{
				xNeighbours++;
			}
			if ( lifeBoard[rMinus][cPlus] == x )
			{
				xNeighbours++;
			}

			if ( xNeighbours == THREE )
			{
				nextGenBoard[r][c]=x;
			}
			else
			{
				if ( lifeBoard[r][c] == x && xNeighbours == TWO )
				{
					nextGenBoard[r][c]=x;
				}
				else
				{
					nextGenBoard[r][c]=DOT;
				}
			}
			xNeighbours=0;
		}
	}

	for (int x=1; x<rowsMinus; x++)
	{
		for ( int y=0; y<colsMinus; y++)
		{
			nextGenBoard[x][y] = lifeBoard[x][y];
		}
	}

}