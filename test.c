#include <stdio.h>

int giveMeCharStrings( char * str)
{
    printf("%p \n", &str);
    printf("%c", str[7]);
    return 0;
}
int main()
{
    char test[] ="This is atest";
    giveMeCharStrings(test);
    return 0;
}

