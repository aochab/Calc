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

double GetNum(); // wczytanie liczby rzeczywistej
char GetOper(); //wczytanie operatora
void SkipSpaces();
int isOper( char c );
int isDigit( char c );
void readBraces( Stack** pStack ); // wczytanie nawiasów otwieraj¹cych 
int prior( char cOper ); // sprawdza priorytet operacji
double Eval( char oper, double arg1, double arg2 ); // obliczenia
double Calc();  


int main( int argc, char* argv[] )
{
	printf( "Prosze podac wyrazenie \n" );
	printf( "Wynik: %.02lf \n", Calc() );
	_getch();
	return 0;
}

//----------------------------------------------------------------
double GetNum()
{
	char b;
	char c;
	double res = 0; //rezultat
	int minus = 0; //zmienna znaku liczby

	SkipSpaces();
	if( ( c = getchar() ) == '-' ) //sprawdŸ czy znak liczby jest ujemny
	{
		SkipSpaces();
		if( !isDigit( b = getchar() ) )
		{
			ungetc( b, stdin );
			ungetc( c, stdin );
			return res;
		}
		ungetc( b, stdin );
		minus = 1;				//jeœli tak, info zapisujemy w zmiennej
		SkipSpaces();
	}
	else ungetc( c, stdin );

	while( isDigit( c = getchar() ) ) //wczytanie znaku i sprawdzenie zy jest znakiem cyfry
		res = res * 10 + ( c - '0' );
	if( c == DOT )
		{
			//wczytanie czesci ulamkowej
			double coef = 0.1;
			while( isDigit( c = getchar() ) )
			{
				res += ( c - '0' )*coef;
				coef *= 0.1;
			}
		}
		ungetc( c, stdin );

	if( minus ) //zmiana znaku liczby, jeœli jest ujemna
		res = -res;  //!!!Tak mi zmieni³

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
	ungetc( c, stdin ); //odsy³a spacje z powrotem do strumienia wejsciowego
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
	return ( c >= '0' ) && ( c <= '9' ); //zwraca 1 gdy c jest znakiem cyfry lub 0 w przeciwnym przypadku
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
		if( arg2 >= 1e-14 ) //wystarczaj¹co ma³a liczba, ¿eby by³o blisko 0
			return arg1 / arg2;
		perror("ERROR: division by 0!!!"); 
		break;
	 case '^': return pow( arg1, arg2 ); //gdy arg2 jest ca³kowity, nie mo¿na u¿ywaæ pow!
	}
	return 0;
}

//----------------------------------------------------------------
double Calc()
{

	char c; //zmienna operacji
	double x;//zmmienna liczbowa

	Stack* pStack = InitStack(); //inicjowanie stosu operacji
	DStack* dpStack = dInitStack(); //inicjowanie stosu liczb

	readBraces( &pStack ); //sprawdŸ spacje
	dpush( GetNum(), &dpStack ); //wczytanie liczby i wrzucenie na stos*/

	while( isOper( c = GetOper() ) )
	{
		while( c == ')' )//sprawdzamy czy pojedyncza liczba jest otoczona nawiasami
		{
			if( top( pStack ) == '(' )
				 del( &pStack );
			c = GetOper();
		}

		while( prior( c ) <= prior( top( pStack ) ) ) //porównanie priorytetu operatorów
		{
			x = dpop( &dpStack ); //pobranie arg2
			dpush( Eval( pop( &pStack ), dpop( &dpStack ), x ), &dpStack ); //W³o¿enie na stos liczb obliczonej wartoœci
		}
		push( c, &pStack ); //W³o¿enie operatora na stos operatorów

		readBraces( &pStack ); //SprawdŸ czy spacja otwieraj¹ca
		dpush( GetNum(), &dpStack ); //ponowne wczytanie liczby i w³o¿enie na stos

		while( ( c = GetOper() ) == ')' ) 
		{
			while( ( c = pop( &pStack ) ) != '(' ) //wykonujemy dzia³ania, a¿ do zamkniêcia poszczególnych nawiasów
			{
				x = dpop( &dpStack ); //pobranie arg2
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

	double end = dtop( dpStack ); // zapisuje do zmiennej przed usuniêciem wczyszczeniem stosów

	RemoveStack( &pStack );
	dRemoveStack( &dpStack );

	return end;
	
}

