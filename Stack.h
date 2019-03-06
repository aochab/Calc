#ifndef STACK_H
#define STACK_H

typedef struct tagStack
{
	char	  cKey;
	tagStack* pNext;
} Stack;

Stack* InitStack();
void RemoveStack( Stack** pStack );
void push( char c, Stack** pStack );
char pop( Stack** pStack );
char top( Stack* pStack );
void del( Stack** pStack );
int isEmpty( Stack* pStack );

#endif