#include "stdafx.h"
#include "Stack.h"
#include <stdlib.h>
#include <memory.h>

using namespace std;

Stack* InitStack() 
{
	return NULL;
}

//----------------------------------------------------------------
void RemoveStack( Stack** pStack )
{
	while( !isEmpty( *pStack ) )
		del( pStack );
	*pStack = NULL;
}

//----------------------------------------------------------------
//Put operator on the stack
void push( char c, Stack** pStack )
{
	Stack* v = (Stack*)malloc( sizeof( Stack ) );
	if( v ) // if(v != NULL )
	{
		memset( v, 0, sizeof( Stack ) );
		v->cKey = c;	//(*v).cKey = c;
		//dowišzanie
		v->pNext = *pStack;
		*pStack = v;
	}
	else
		perror( "ERROR push: stack overflow!" );
}

//----------------------------------------------------------------
//Return top of the stack and delete
char pop( Stack** pStack )
{

	if( !isEmpty( *pStack ) )
	 {
	  char c = top( *pStack );
	  del( pStack );
 	  return c;
	 }
	perror( "ERROR pop: stack underflow!" );
	return 0;
}

//----------------------------------------------------------------
//Return value of the top
char top( Stack* pStack )
{
	if( !isEmpty( pStack ) )
		return pStack->cKey;

	return 0;
}

//----------------------------------------------------------------
void del( Stack** pStack ) {
	if( !isEmpty( *pStack ) )
	{
		Stack* p = *pStack;
		*pStack = p->pNext; 
		free( p ); 
	}
	else
		perror( "ERROR del: stack underflow!" );
}

//----------------------------------------------------------------
int isEmpty( Stack* pStack ) {
	return !pStack;
}
