#include "stdafx.h"
#include "Stack.h"
#include "dstack.h"
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <conio.h>

#define DOT '.'
#define MINUS -1
using namespace std;

typedef int unsigned tab[11];

double GetNum(); 	// read number
char GetOper(); 	// read operator
void SkipSpaces();
int isOper( char c );
int isDigit( char c );
void readBraces( Stack** pStack ); 
int prior( char cOper ); 	// check priority
double Eval( char oper, double arg1, double arg2 ); //Calculations
double Calc();  


int main( int argc, char* argv[] )
{
	printf( "Enter the equation \n" );
	printf( "Result: %.02lf \n", Calc() );
	_getch();
	return 0;
}

//----------------------------------------------------------------
double GetNum()
{
	char b;
	char c;
	double res = 0; //result
	int minus = 0; //1 when the variable is less than 0
	
	SkipSpaces();
	if( ( c = getchar() ) == '-' ) // check minus
	{
		SkipSpaces();
		if( !isDigit( b = getchar() ) )
		{
			ungetc( b, stdin );
			ungetc( c, stdin );
			return res;
		}
		ungetc( b, stdin );
		minus = 1; //if variable is less than 0			
		SkipSpaces();
	}
	else ungetc( c, stdin );

	while( isDigit( c = getchar() ) ) //read char and check if it's a digit
		res = res * 10 + ( c - '0' );
	if( c == DOT )
		{
			//reading the fractional part
			double coef = 0.1;
			while( isDigit( c = getchar() ) )
			{
				res += ( c - '0' )*coef;
				coef *= 0.1;
			}
		}
		ungetc( c, stdin );

	if( minus ) 
		res = -res;  

	return res;
}

//----------------------------------------------------------------
char GetOper()
{
	SkipSpaces();
	return getchar();
}

//----------------------------------------------------------------
void SkipSpaces()
{
	char c;
	while( ( c = getchar() ) == ' ' );
	ungetc( c, stdin ); //return space on stdin
}

//----------------------------------------------------------------
int isOper( char c )
{
	switch( c )
	{
	 case '(': 
	 case ')':
	 case '+':
	 case '-':
	 case '*':
	 case '/':
	 case '^': return 1;
	}
	return 0;
}

//----------------------------------------------------------------
int isDigit( char c )
{
	return ( c >= '0' ) && ( c <= '9' ); 
}

//----------------------------------------------------------------
void readBraces( Stack** pStack )
{
	char c;
	while( ( c = GetOper() ) == '(' )
		push( c, pStack );
	ungetc( c, stdin );
}

//----------------------------------------------------------------
int prior( char cOper )
{
	switch(cOper)
	{ 
	 case '(' : return 1;
	 case '+' : 
	 case '-' : return 2;
	 case '*' :
	 case '/' : return 3;
	 case '^' : return 4;
	}
	return 0;
}

//----------------------------------------------------------------
double Eval( char oper, double arg1, double arg2 )
{
	switch (oper)
	{
 	 case '+' : return arg1 + arg2;
	 case '-' : return arg1 - arg2;
	 case '*' : return arg1 * arg2;
	 case '/' : 
		if( arg2 >= 1e-14 ) 
			return arg1 / arg2;
		perror("ERROR: division by 0!!!"); 
		break;
	 case '^': return pow( arg1, arg2 ); 
	}
	return 0;
}

//----------------------------------------------------------------
double Calc()
{

	char c; //operation
	double x;//number

	Stack* pStack = InitStack(); //init stack of operations
	DStack* dpStack = dInitStack(); //init stack of numbers

	readBraces( &pStack ); //read the braces when they are
	dpush( GetNum(), &dpStack ); //wczytanie liczby i wrzucenie na stos*/

	while( isOper( c = GetOper() ) )
	{
		while( c == ')' )//check braces
		{
			if( top( pStack ) == '(' )
				 del( &pStack );
			c = GetOper();
		}

		while( prior( c ) <= prior( top( pStack ) ) ) //compare the priority of operators
		{
			x = dpop( &dpStack ); //pobranie arg2
			dpush( Eval( pop( &pStack ), dpop( &dpStack ), x ), &dpStack ); //put the calculated number on the stack
		}
		push( c, &pStack ); //put operator on stack

		readBraces( &pStack ); 
		dpush( GetNum(), &dpStack ); //get number and put on the stack

		while( ( c = GetOper() ) == ')' ) 
		{
			while( ( c = pop( &pStack ) ) != '(' ) //Count as long as there are brackets
			{
				x = dpop( &dpStack ); 
				dpush( Eval( c, dpop( &dpStack ), x ), &dpStack );
			}       
		}
		ungetc( c, stdin );
	}

	while( !isEmpty( pStack ) )
	{
		x = dpop( &dpStack );
		dpush( Eval( pop( &pStack ), dpop( &dpStack ), x ), &dpStack );
	}

	double end = dtop( dpStack ); //Save result

	RemoveStack( &pStack );
	dRemoveStack( &dpStack );

	return end;
	
}

