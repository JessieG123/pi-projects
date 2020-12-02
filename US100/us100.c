#include <stdio.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <bcm_host.h>
#include <time.h> //TODO: is this suppose to be here


#define BLOCK_SIZE 4096

#define GPIO_OFFSET 0x200000
//TODO: HOW TO ADD TIMER? 
#define TIMER_OFFSET 0x0000b000

volatile unsigned int *gpio;
void *gpioMap;
int fdGPIO;

// GPIO Pin 9, 10 from explorer hat schematic
#define TX_MISO  9
#define RX_MOSI  10

// TODO: Define the GPFSEL and GPSET and GPCLR registers here - look in peripheral manual starting at pp. 89
#define GPFSEL0 0
#define GPFSEL1 1
#define GPSET0 6 //TODO: Find out why. In Lights example it was 7 and 10 in the old manual
#define GPCLR0 8
#define GPLEV0 10
#define GPIO_PUP_PDN_CNTRL_REG0 57

//TODO: Change to US100 things
void initUs100() {
    unsigned peripheralBase = bcm_host_get_peripheral_address();
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
    r = gpio[GPFSEL0];
    r &= ~(0b111 << 27);
    r |= (0b001 << 27);
    gpio[GPFSEL0] = r;
    
    // Set RX_MOSI (Pin 10) to input (000)
    r = gpio[GPFSEL1];
    r &= ~(0b111);
    gpio[GPFSEL1] = r;

        
	//TODO: Update this to Pi 4 and US100 things
    // Disable the pull-up/pull-down control line for GPIO pin 23. We follow the
    // procedure outlined on page 101 of the BCM2837 ARM Peripherals manual. The
    // internal pull-up and pull-down resistor isn't needed for an output pin.

    // Disable pull-up/pull-down by setting bits 0:1
    // to 00 in the GPIO Pull-Up/Down Register 

    gpio[GPIO_PUP_PDN_CNTRL_REG0] &= ~(0b00 << (2 * TX_MISO)); //no resistor for pin 9 TX_MISO
    gpio[GPIO_PUP_PDN_CNTRL_REG0] &= ~(0b00 << (2 * RX_MOSI)); //no resistor for pin 10 RX_MOSI
        
    // gpio[GPPUD] = 0x0;
    // r = 150;
    // while (r--) {
    //   asm volatile("nop");
    // }
    // gpio[GPPUDCLK0] = (0x1 << LED4) | (0x1 << LED1);
    // r = 150;
    // while (r--) {
    //   asm volatile("nop");
    // }
    // gpio[GPPUDCLK0] = 0;
    
    //TODO: check if needed
    // clearing the output and input line
    gpio[GPCLR0] = 1 << TX_MISO;
    gpio[GPCLR0] = 1 << RX_MOSI;
}

void freeUs100() {
    munmap( gpioMap, BLOCK_SIZE );
    close( fdGPIO );
}

// TODO: IS this correct? 
//calculate distance/time things in python
void txHigh() {
    gpio[GPSET0] = 1 << TX_MISO;
}

void txLow() {
    gpio[GPCLR0] = 1 << TX_MISO;
}

void checkRxLevel() {
    if (gpio[GPLEV0] >> RX_MOSI == 1) {
        return 1;
    }
    else
    {
        if(gpio[GPLEV0] >> RX_MOSI == 0) {
            return 0;
        }
    }
}

 //Wait for Rx pin to go high
    //Record the time t1
    //Wait for Rx pin to go low
    //Record time t2
    //distance = 1/2(t2 - t1) * 340m/s