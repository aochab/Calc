#ifndef DSTACK_H
#define DSTACK_H

typedef struct tagDStack
{
	double	  fKey;
	tagDStack* pNext;
} DStack;

DStack* dInitStack();
void dRemoveStack( DStack** pStack );
void dpush( double c, DStack** pStack );
double dpop( DStack** pStack );
double dtop( DStack* pStack );
void ddel( DStack** pStack );
int disEmpty( DStack* pStack );

#endif