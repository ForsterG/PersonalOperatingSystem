
#ifndef __GDT_HPP
#define __GDT_HPP

#include "types.hpp"

class GlobalDescriptorTable
{
    public:
        class SegmentDescriptor
        {
            private:
                uint16_t limit_lo;
                uint16_t base_lo;
                uint8_t base_hi;
                uint8_t type;
                uint8_t flags_limit_hi;
                uint8_t base_vhi;
            public:
                SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t type); //Constructor
                uint32_t Base();
                uint32_t Limit();

        }__attribute__((packed));

        SegmentDescriptor nullSegmentSelector;
        //SegmentDescriptor unusedSegmentSelector;
        SegmentDescriptor codeSegmentSelector;
        SegmentDescriptor dataSegmentSelector;

        GlobalDescriptorTable();
        ~GlobalDescriptorTable();

        uint32_t address();

        uint16_t CodeSegmentSelector();
        uint16_t DataSegmentSelector();
        void setGDT(uint16_t cs, uint16_t ds); // need to set it to global GDT.setGDT
};


#endif