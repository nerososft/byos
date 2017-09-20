#ifndef __BYOS__DRIVERS__KEYBOARD_H
#define __BYOS__DRIVERS__KEYBOARD_H

#include <common/types.h>
#include <hardwarecommunication/interrupts.h>
#include <drivers/driver.h>
#include <hardwarecommunication/port.h>

namespace byos{
    namespace drivers{

        class KeyboardEventHandler{
        public:
            KeyboardEventHandler();
            
            virtual void OnKeyDown(char);
            virtual void OnKeyUp(char);
        };
        
        class KeyboardDriver : public byos::hardwarecommunication::InterruptHandler ,public Driver
        {
            byos::hardwarecommunication::Port8Bit dataport;
            byos::hardwarecommunication::Port8Bit commandport;
            
            KeyboardEventHandler* handler;
        public:
            KeyboardDriver(byos::hardwarecommunication::InterruptManager* manager,KeyboardEventHandler* handler);
            ~KeyboardDriver();
            virtual byos::common::uint32_t HandleInterrupt(byos::common::uint32_t esp);
            virtual void Activate();
        };
    }
}

#endif