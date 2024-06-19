#include "project.h"

int main()
{
    char *test, *test1, *test2, *test3, *test4, *test5, *test6, *test7;

	/*----malloc----*/
	printf("----------MALLOC----------\n");
	//Tiny
    test  = malloc(100);
    test1 = malloc(500);
    test2 = malloc(10);
    //Small
	// 1024 bytes alloc par le programme (?)
    test3 = malloc(1500);
	test4 = malloc(1900);
    test5 = malloc(1090);
	//Large
	test6 = malloc(100000);
	test7 = malloc(200000);

	show_alloc_mem();

	/*----free----*/
	printf("----------FREE----------\n");
	free(test2);
	free(test4);
	free(test6);

	show_alloc_mem();

	/*----realloc----*/
	printf("----------REALLOC----------\n");

	test1 = realloc(test1, 110);
	test3 = realloc(test3, 1501);
	test6 = realloc(test7, 200001);

	show_alloc_mem();

    return 0;
}