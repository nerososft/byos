#ifndef __DEVICE_H
#define __DEVICE_H

    #include "types.h"
    #include "port.h"
    #include "interrupts.h"

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

#endif