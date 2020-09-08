#include "typesCustom.h"
#include "print.h"
#include "ports.h"
//bug on boot1 jumps directly to 2000h which is main now but this should be flexible. Entry point should be read from ELF file

int main()
{
    clrscr();

    print("TEST");
    int x = 265;

    while(1)
    {

    }
    return 0;
}






