#include <iostream>
#include <iomanip>

using namespace std;

// This program produces a table with 5 columns.
// The first column shows the values of the diameter,
// which increases each row by the inputed interval value.
// The remaining 4 columns will show the values of cone volumes
// with different heights (1.0 cm, 7.0 cm, 9.0 cm, 15.0 cm)
//
// The user will input the diameter
// (inside the inclusive range 0.0-60.0),
// and the number of rows that will be printed in the table
// (inside the inclusive range of 1-23).
// The user will then input the interval value
// (inside the inclusive range 0.1-5.0)
// of which the diameter will increase by for each row.
// if the user inputs a value that is out of range,
// they will get 3 more tries before the program terminates
// If the diameter increases past 120, the row of values will not be printed
// and will print a line of text explaining the diameter is too large
// for each row in which the diameter exceeds 120
// 
// Program Authors:
// Valeriya Svichkar
// Marychelle Bitoon
// Octover 24 2017


int main ()
{	
	const double MIN_DIA=0.0;
	const double MAX_DIA=60.0;
	const int MIN_ROWS=1;
	const int MAX_ROWS=23;
	const double MIN_IVAL=0.1;
	const double MAX_IVAL=5.0;
	const int MAX_TRIES=2;
	const double PI=3.14159265;
	const int MAX_D_ROWS=120;

	double d;
	int rows;
	double ival;
	int tries=0;
	int i=0;
	int f=0;
	double vol1;
	double vol7;
	double vol9;
	double vol15;

	do
	{
		if ( tries<=MAX_TRIES )
		{
			cout << "enter the diameter of the base of the cone for the first row" << endl;
			cout << fixed << setprecision(3) << MIN_DIA << " <= x <= " << MAX_DIA << " ";
			cin >> d;
		}
		if ( tries>MAX_TRIES )
		{
			cout << "Exceeded number of tries reading the initial diameter of the cone" << endl;
			cout << "Program is terminating";

			return 1;
		}
		tries++;
		if ( d<MIN_DIA || d>MAX_DIA && tries<=MAX_TRIES )
		{
			cout << " You entered " << d << endl << "TRY AGAIN PLEASE" << endl;
		}
	}
	while ( d<MIN_DIA || d>MAX_DIA );
	tries=0;
	do
	{
		if ( tries<=MAX_TRIES )
		{
			cout << "enter the number of rows in the table " << MIN_ROWS << " <= x <= " << MAX_ROWS << " ";
			cin >> rows;
		}
		if ( tries>MAX_TRIES )
		{
			cout << "Exceeded number of tries reading the number of rows" << endl;
			cout << "Program is terminating";

			return 2;
		}
		tries++;
		if ( rows<MIN_ROWS || rows>MAX_ROWS && tries<=MAX_TRIES )
		{
			cout << " You entered " << rows << endl << "TRY AGAIN PLEASE" << endl;
		}
	}
	while ( rows<MIN_ROWS || rows>MAX_ROWS );
	tries=0;
	do
	{
		if ( tries<=MAX_TRIES )
		{
			cout << "enter the length of the interval between entries in the table" << endl;
			cout << MIN_IVAL << " <= diamInterval <= " << MAX_IVAL << " ";
			cin >> ival;
		}
		if ( tries>MAX_TRIES )
		{
			cout << "Exceeded number of tries reading the interval" << endl;
			cout << "Program is terminating";

			return 3;
		}
		tries++;
		if ( ival<MIN_IVAL || ival>MAX_IVAL && tries<=MAX_TRIES )
		{
			cout << " You entered " << ival << endl << "TRY AGAIN PLEASE" << endl;
		}
	}
	while ( ival<MIN_IVAL || ival>MAX_IVAL );
	cout << endl << endl << setw(15) << "Diameter" << setw(15) << "Volume for";
	cout << setw(15) << "Volume for" << setw(15) << "Volume for" << setw(15) << "Volume for";
	cout << endl << setw(30) << "height 1cm" << setw(15) << "height 7cm" << setw(15);
	cout << "height 9cm" << setw(15) << "height 15cm" << endl;
	for (i=0; i<rows; i++)
	{
		if ( d<MAX_D_ROWS )
		{
		vol1=PI*d*d/12;
		vol7=PI*d*d*7/12;
		vol9=PI*d*d*9/12;
		vol15=PI*d*d*15/12;
		cout << setw(15) << d << setw(15) << vol1 << setw(15) << vol7;
		cout <<	setw(15) << vol9 << setw(15) << vol15 << endl;
		d+=ival;
		}
		else
		{			
			cout << "diameter of cone exceeded the maximum value allowed, line not printed" << endl;
		}
	}

	return 0;

}