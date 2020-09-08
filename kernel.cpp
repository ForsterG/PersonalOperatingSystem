#include "types.hpp"
#include "print.hpp"
#include "gdt.hpp"
//#include "interrupts.hpp"

int main()
{
    //print("Hello World --- http://OSDEV.org");
    //printfHex('H');
    //printf("Hello World - 2 --- http://OSDEV.org\n");
    //printf("Hello World - 3 --- http://OSDEV.org");

    //uint32_t * x = (uint32_t * ) 0x0; 

    GlobalDescriptorTable gdt;
    uint32_t base = gdt.codeSegmentSelector.Base();
    uint16_t dss = gdt.CodeSegmentSelector();
    uint32_t gdtbase = gdt.address();
    //gdt.setGDT();

    //uint8_t* asd = (uint8_t*)&gdt;
    //printfHex32(gdtbase);
    //uint32_t * gdtsize = &gdt;
    //uint32_t * g = &gdt;
    //GlobalDescriptorTable * asd = (GlobalDescriptorTable * )g;
    //printfHex32(gdt.codeSegmentSelector.Base());

    //InterruptManager interrupts(&gdt);

    //interrupts.Activate();s

    while(1);
}