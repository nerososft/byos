#ifndef __BYOS__DRIVERS__MOUSE_H
#define __BYOS__DRIVERS__MOUSE_H

 
#include <common/types.h>
#include <hardwarecommunication/interrupts.h>
#include <drivers/driver.h>
#include <hardwarecommunication/port.h>

namespace byos{
    namespace drivers{
    
        class MouseEventHandler{
              
        public:
            MouseEventHandler();
            
            virtual void OnActivate();
            virtual void OnMouseDown(byos::common::uint8_t button);
            virtual void OnMouseUp(byos::common::uint8_t button);
            virtual void OnMouseMove(int xoffset,int yoffset);
        };
    
        class MouseDriver : public byos::hardwarecommunication::InterruptHandler,public Driver
        {
            byos::hardwarecommunication::Port8Bit dataport;
            byos::hardwarecommunication::Port8Bit commandport;
            byos::common::uint8_t buffer[3];
            byos::common::uint8_t offset;
            byos::common::uint8_t buttons;
            
            MouseEventHandler* handler;
          
        public:
            MouseDriver(byos::hardwarecommunication::InterruptManager* manager,MouseEventHandler* handler);
            ~MouseDriver();
            virtual byos::common::uint32_t HandleInterrupt(byos::common::uint32_t esp);
            virtual void Activate();
        };
    }
}
#endif