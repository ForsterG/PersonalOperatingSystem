#include "gdt.hpp"
#include "print.hpp"

GlobalDescriptorTable::GlobalDescriptorTable()
: nullSegmentSelector(0,0,0),
//unusedSegmentSelector(0,0,0),
codeSegmentSelector(0,64*1024*1024,0x9A),
dataSegmentSelector(0,64*1024*1024, 0x92)
{
    uint32_t i[2];
    
    i[1] = (uint32_t)this;
    i[0] = sizeof(GlobalDescriptorTable) <<16;

    //i[0]= 0x01234567 <<16;//lower two bytes, limit
    //i[1] = 0x0abcdef1;//upper four bytes, address
    /*pseudo-descriptor is 6 bytes; 
If the operand size is 16 bits, the high-order byte of the 6-byte pseudo-descriptor is not used. 
The lower
two bytes specify the 16-bit limit and the third, fourth, and fifth bytes specify the 24-bit base address.
The high-order byte of the GDTR is filled with zeros.
If the operand size is 32 bits, the lower two bytes specify the 16-bit limit and the upper four bytes
specify a 32-bit base address. 
*/
    printfHex32(i[0]);
     print(" ");
    printfHex32(*i);
    asm volatile("lgdt (%0)": :"p" (((uint8_t *) i )+2));//(((uint8_t *) i )+2)
     setGDT(CodeSegmentSelector(), DataSegmentSelector());
}



GlobalDescriptorTable::~GlobalDescriptorTable()
{

}

uint32_t GlobalDescriptorTable::address()
{  
    return (uint32_t )this;
}

uint16_t GlobalDescriptorTable::DataSegmentSelector()
{
    return (uint8_t*)&dataSegmentSelector - (uint8_t*)this;
}

uint16_t GlobalDescriptorTable::CodeSegmentSelector()
{
    return (uint8_t*)&codeSegmentSelector - (uint8_t*)this;
}

GlobalDescriptorTable::SegmentDescriptor::SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t flags)
{
    uint8_t* target = (uint8_t*)this;

    if(limit <= 65536)
    {
        target[6] = 0x40;

    }
    else
    {
        if ((limit & 0xFFF) != 0xFFF)
            limit = (limit >> 12)-1;
        else
            limit = limit >> 12;

        target[6] = 0xC0;
    }

    target[0] = limit & 0xFF;
    target[1] = (limit >> 8) & 0xFF;
    target[6] |= (limit >> 16) & 0xF;

    target[2] = base & 0xFF;
    target[3] = (base >> 8 ) & 0xFF; 
    target[4] = (base >> 16) & 0xFF; 
    target[7] = (base >> 24) & 0xFF; 
    
    target[5] = flags;

}

uint32_t GlobalDescriptorTable::SegmentDescriptor::Base()
{
    uint8_t* target = (uint8_t*)this;
    uint32_t result = target[7];
    result = (result << 8) + target[4];
    result = (result << 8) + target[3];
    result = (result << 8) + target[2];
    return result;
}

uint32_t GlobalDescriptorTable::SegmentDescriptor::Limit()
{
    uint8_t* target = (uint8_t*)this;
    uint32_t result = target[6] & 0xF;
    result = (result << 8) + target[1];
    result = (result << 8) + target[0];

    if((target[6] & 0xC0) == 0xC0)
        result = (result << 12) | 0xFFF;

    return result;

}
