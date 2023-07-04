#include <stdio.h>

/*In C, a local variable like num is stored on the stack,
and its scope and lifetime is only within
the function where it is defined*/

int *fun()
{
	int num = 10;
	return (&num);//stack memory
}
//local variable
//The address returned by fun() then points to memory that is free to be overwritten.

int main(void)
{
	int *ptr = NULL;
	ptr = fun();
	printf("%d", *ptr);
	return 0;
}
 //correct version
#include <stdio.h>
#include <stdlib.h>//malloc

int *fun()
{
    int *num = malloc(sizeof(int));
    *num = 10;
    return num;
}

int main(void)
{
    int *ptr = NULL;
    ptr = fun();
    printf("%d", *ptr);
    free(ptr);
    return 0;
}
