#include <list.h>

#include <stdio.h>

int main(void)
{
    ubyte *text1 = (ubyte *)"First test string";
    ubyte *text2 = (ubyte *)"Second test string";
    List *l;

    printf("Test program for the List structure\n");

    printf("Creating a list...");
    l = list_init();
    printf("OK\n");

    printf("Adding items to a list...");
    list_append(l, text1);
    list_append(l, text2);
    printf("OK\n");
}