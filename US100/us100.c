#include <stdio.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <bcm_host.h>
#include <time.h>


#define BLOCK_SIZE 4096

//TODO: Double check it's the correct offset
#define GPIO_OFFSET 0x200000

volatile unsigned int *gpio;
void *gpioMap;
int fdGPIO;

// GPIO Pin 9, 10 from explorer hat schematic
#define TX_MISO  9
#define RX_MOSI  10

// TODO: Define the GPFSEL and GPSET and GPCLR registers here - look in peripheral manual starting at pp. 89
#define GPFSEL0 0
#define GPFSEL1 1
#define GPSET0 x //TODO: Find out why. In Lights example it was 7 and 10. 
#define GPCLR0 x
#define GPPUD 37
#define GPPUDCLK0 38
#define GPLEV0 13

//TODO: Change to US100 things
void initUs100() {
    unsigned peripheralBase = bcm_host_get_peripheral_address();
    // TODO print out peripheralBase and peripheralBase + OFFSET to confirm
    fprintf( stderr, "%08x %08x\n", peripheralBase, peripheralBase + GPIO_OFFSET);
    fdGPIO = open("/dev/mem", O_RDWR|O_SYNC);
    gpioMap = (unsigned int *)mmap(
        NULL,
        BLOCK_SIZE,
        PROT_READ|PROT_WRITE,
        MAP_SHARED,
        fdGPIO,
        peripheralBase + GPIO_OFFSET
    );
    
    if ( gpioMap == MAP_FAILED ) {
        fprintf( stderr, "The memory map initialization failed.\n");
        perror( "mmap" );
        return;
    }
    
    gpio = (volatile unsigned int *) gpioMap;

    register unsigned int r;
    
    // Set TX_MISO (Pin 9) to output (001)
    /// set register r by accessing gpio[]
    r = gpio[GPFSEL0];
    // Clear the 3 bits for this pin to 0 using &=
    r &= ~(0b111 << 27);
    /// Set the 3 bits to output using |=
    r |= (0b001 << 27);
    /// Set gpio[] = r
    gpio[GPFSEL0] = r;
    
    // Set RX_MOSI (Pin 10) to input (000)
    // set register r by accessing gpio[]
    r = gpio[GPFSEL1];
    // Clear the 3 bits for this pin to 0 using &= this also sets the 3 bits to 000 for input. 
    r &= ~(0b111);
    // Set gpio[] = r
    gpio[GPFSEL1] = r;

        
	//TODO: Update this to Pi 4 things
    // Disable the pull-up/pull-down control line for GPIO pin 23. We follow the
    // procedure outlined on page 101 of the BCM2837 ARM Peripherals manual. The
    // internal pull-up and pull-down resistor isn't needed for an output pin.

    // Disable pull-up/pull-down by setting bits 0:1
    // to 00 in the GPIO Pull-Up/Down Register 
    gpio[GPPUD] = 0x0;
    r = 150;
    while (r--) {
      asm volatile("nop");
    }
    gpio[GPPUDCLK0] = (0x1 << LED4) | (0x1 << LED1);
    r = 150;
    while (r--) {
      asm volatile("nop");
    }
    gpio[GPPUDCLK0] = 0;
    
    // clearing the output line
    gpio[GPCLR0] = 1 << LED4;
    gpio[GPCLR0] = 1 << LED1;
}

void freeUs100() {
    munmap( gpioMap, BLOCK_SIZE );
    close( fdGPIO );
}

// TODO Implement functions here
//FIXME: change this to something so that you can calculate distance in python instead
void calculateDistance() {
    
}
