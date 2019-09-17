#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void exibir(int* p){

	for(int x = 0;x< 6;x++, p++)
		printf("%d\n", *p);
}
int main(int argc, char const *argv[])
{
	int v[] = {1,2,3,4,5,6};
	exibir(v);
	return 0;
}
