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
//Insert number on the stack
void dpush( double x, DStack** pStack )
{
	DStack* v = (DStack*)malloc( sizeof( DStack ) );
	if( v ) // if(v != NULL )
	{
		memset( v, 0, sizeof( DStack ) );
		v->fKey = x;			
		v->pNext = *pStack;
		*pStack = v;
	}
	else
		perror("ERROR push: stack overflow!");
}

//----------------------------------------------------------------
//Return top and delete
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
//return top
double dtop( DStack* pStack )
{
	if( !disEmpty( pStack ) )
		return pStack->fKey;

	return 0;
}

//----------------------------------------------------------------
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
int disEmpty( DStack* pStack )
{
	return !pStack;
}
