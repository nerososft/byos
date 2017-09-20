#include "types.h"
#include "gdt.h"
#include "interrupts.h"
#include "driver.h"
#include "keyboard.h"
#include "mouse.h"

void printf(char* str)
{
    static uint16_t* VideoMemory = (uint16_t*)0xb8000;

    static uint8_t x=0,y=0;

    for(int i = 0; str[i] != '\0'; ++i)
    {
        switch(str[i])
        {
            case '\n':
                x = 0;
                y++;
                break;
            default:
                VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | str[i];
                x++;
                break;
        }

        if(x >= 80)
        {
            x = 0;
            y++;
        }

        if(y >= 25)
        {
            for(y = 0; y < 25; y++)
                for(x = 0; x < 80; x++)
                    VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | ' ';
            x = 0;
            y = 0;
        }
    }
}


void printfHex(uint8_t key){
        char* foo = "00 ";
        char* hex = "0123456789ABCDEF";
        foo[0] = hex[(key >> 4) & 0xF];
        foo[1] = hex[ key & 0xF];
        printf(foo);
}

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors()
{
    for(constructor* i = &start_ctors; i != &end_ctors; i++)
        (*i)();
}



extern "C" void kernelMain(const void* multiboot_structure, uint32_t /*multiboot_magic*/)
{
    printf("BYOS Kernel Version: 0.0.1 \n");

    GlobalDescriptorTable gdt;
    InterruptManager interrupts(0x20, &gdt);
    
    
    printf("Initializing Hardware... \n");
    
    DriverManager driverManager;
        KeyboardDriver keyboard(&interrupts);
        driverManager.AddDriver(&keyboard);
        
        printf("Keyboard Driver Initialized. \n");
        
        MouseDriver mouse(&interrupts);
        driverManager.AddDriver(&mouse);
        
        printf("Mouse Driver Initialized. \n");
        
        driverManager.ActivateAll();
        
        printf("All Drivers Initialized. \n");
        
        
    interrupts.Activate();

    while(1);
}