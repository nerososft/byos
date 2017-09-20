#ifndef __BYOS__GDT_H
#define __BYOS__GDT_H

#include <common/types.h>


namespace byos{

    
    
    class GlobalDescriptorTable
    {
        public:

            class SegmentDescriptor
            {
                private:
                    byos::common::uint16_t limit_lo;
                    byos::common::uint16_t base_lo;
                    byos::common::uint8_t base_hi;
                    byos::common::uint8_t type;
                    byos::common::uint8_t limit_hi;
                    byos::common::uint8_t base_vhi;

                public:
                    SegmentDescriptor(byos::common::uint32_t base, byos::common::uint32_t limit, byos::common::uint8_t type);
                    byos::common::uint32_t Base();
                    byos::common::uint32_t Limit();
            } __attribute__((packed));

        private:
            SegmentDescriptor nullSegmentSelector;
            SegmentDescriptor unusedSegmentSelector;
            SegmentDescriptor codeSegmentSelector;
            SegmentDescriptor dataSegmentSelector;

        public:

            GlobalDescriptorTable();
            ~GlobalDescriptorTable();

            byos::common::uint16_t CodeSegmentSelector();
            byos::common::uint16_t DataSegmentSelector();
    };
}
#endif