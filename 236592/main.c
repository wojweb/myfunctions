#include"mylib.h"
#include<stdio.h>
int test(int n, ...);

int main(int argc, char **argv)
{
    char str[200];
    int i;
    int b;
    b = myscanf("%b", &i);
    if(b != -1)
        myprintf("wczytano: %d\n"
            "w zapisie szestastkowym: %x", i, i);

    // myscanf("%bvim ", &i);

    // myprintf("hejo , %d", 43);
    // i = myatoi(str, 2);
    // printf("%d", test(2, 5, 6, 7, 8));

    return 0;
}


