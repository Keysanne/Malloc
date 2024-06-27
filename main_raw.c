#include "project.h"

int main()
{
    char *test, *test1, *test2, *test3, *test4, *test5, *test6, *test7;
	show_alloc_mem();

	/*----malloc----*/
	write(1, "----------MALLOC----------\n", 27);
	//Tiny
    test  = malloc(100);
    test1 = malloc(500);
    test2 = malloc(10);
    //Small
    test3 = malloc(1500);
	test4 = malloc(1900);
    test5 = malloc(1090);
	//Large
	test6 = malloc(100000);
	test7 = malloc(200000);
	show_alloc_mem();

	/*----free----*/
	write(1, "----------FREE----------\n", 25);
	free(test2);
	free(test4);
	free(test6);
	show_alloc_mem();

	/*----realloc----*/
	write(1, "----------REALLOC----------\n", 28);

	test1 = realloc(test1, 110);
	test3 = realloc(test3, 1501);
	test7 = realloc(test7, 200001);
	show_alloc_mem();

	write(1, "----------END----------\n", 24);
	free(test);
	free(test1);
	free(test3);
	free(test7);
	free(test5);
	show_alloc_mem();

	write(1, "----------AGAIN----------\n", 26);
    test  = malloc(100);
	show_alloc_mem();

    return 0;
}