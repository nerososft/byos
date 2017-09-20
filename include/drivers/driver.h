#ifndef __BYOS__DRIVERS_DRIVER_H
#define __BYOS__DRIVERS_DRIVER_H

#include <common/types.h>
#include <hardwarecommunication/port.h>
#include <hardwarecommunication/interrupts.h>

namespace byos{

    namespace drivers{

        class Driver
        {
            public:
                Driver();
                ~Driver();
            
                virtual void Activate();
                virtual int Reset();
                virtual void Deactive();
                
        };
        
        class DriverManager{
        private:
            Driver* drivers[265];
            int numDrivers;
        public:
            DriverManager();
            void AddDriver(Driver* driver);
            
            void ActivateAll();
            
            
        };
    }
}

#endif