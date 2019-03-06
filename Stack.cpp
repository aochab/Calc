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
//W³o¿enie operatora na stos
void push( char c, Stack** pStack )
{
	Stack* v = (Stack*)malloc( sizeof( Stack ) );
	if( v ) // if(v != NULL )
	{
		memset( v, 0, sizeof( Stack ) );
		v->cKey = c;	//(*v).cKey = c;
		//dowi¹zanie
		v->pNext = *pStack;
		*pStack = v;
	}
	else
		perror( "ERROR push: stack overflow!" );
}

//----------------------------------------------------------------
//Zwróc top stosu i usuñ go z niego
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
//Wypisz top stosu
char top( Stack* pStack )
{
	if( !isEmpty( pStack ) )
		return pStack->cKey;

	return 0;
}

//----------------------------------------------------------------
//Usuniêcie operatora ze stosu
void del( Stack** pStack ) {
	if( !isEmpty( *pStack ) )
	{
		Stack* p = *pStack;
		*pStack = p->pNext; // *pStack = (*pStack)->pNext;
		free( p ); // mnie gwarantuje NULL-a
	}
	else
		perror( "ERROR del: stack underflow!" );
}

//----------------------------------------------------------------
//Sprawdzenie czy stos jest pusty
int isEmpty( Stack* pStack ) {
	return !pStack;
}