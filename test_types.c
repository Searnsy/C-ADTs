#include <stdlib.h>
#include <stdio.h>
#include "type.h"

extern int ORD;

int main(void){
	ORD = -1;
	int x = 75;
	int y = 50;
	STYPE* first = create((data_d)x, INT);
	STYPE* second = create((data_d)y, INT);
	printf("(%d cmp %d) = %d\n",first->data.i,second->data.i,compare(first,second));
	delete(first);
	delete(second);
	return 0;
}
