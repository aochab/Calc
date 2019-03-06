#include "stdafx.h"
#include "dstack.h"
#include <stdlib.h>
#include <memory.h>

using namespace std;

DStack* dInitStack()
{
	return NULL;
}

//----------------------------------------------------------------
void dRemoveStack( DStack** pStack )
{
	while ( !disEmpty( *pStack ) )
		ddel( pStack );
	*pStack = NULL;
}

//----------------------------------------------------------------
//W³o¿enie liczby na stos
void dpush( double x, DStack** pStack )
{
	DStack* v = (DStack*)malloc( sizeof( DStack ) );
	if( v ) // if(v != NULL )
	{
		memset( v, 0, sizeof( DStack ) );
		v->fKey = x;	//(*v).fKey = x;
						//dowi¹zanie
		v->pNext = *pStack;
		*pStack = v;
	}
	else
		perror("ERROR push: stack overflow!");
}

//----------------------------------------------------------------
//Zwróc top stosu i usuñ go z niego
double dpop( DStack** pStack )
{

	if( !disEmpty( *pStack ) )
	{
		double x = dtop( *pStack );
		ddel( pStack );
		return x;
	}
	perror("ERROR pop: stack underflow!");
	return 0;
}

//----------------------------------------------------------------
//Wypisz top stosu
double dtop( DStack* pStack )
{
	if( !disEmpty( pStack ) )
		return pStack->fKey;

	return 0;
}

//----------------------------------------------------------------
//Usuniêcie liczby ze stosu
void ddel( DStack** pStack ) 
{
	if( !disEmpty(*pStack) )
	{
		DStack* p = *pStack;
		*pStack = p->pNext; // *pStack = (*pStack)->pNext;
		free( p ); // mnie gwarantuje NULL-a
	}
	else
		perror("ERROR del: stack underflow!");
}

//----------------------------------------------------------------
//Sprawdzenie czy stos jest pusty
int disEmpty( DStack* pStack )
{
	return !pStack;
}