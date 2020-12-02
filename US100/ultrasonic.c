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

// GPIO Pin 9, 10 from explorer hat schematic
#define TX_MISO  9
#define RX_MOSI  10

#define GPFSEL0 0
#define GPFSEL1 1
#define GPSET0 6 //TODO: Find out why. In Lights example it was 7 and 10 in the old manual
#define GPCLR0 8
#define GPLEV0 10
#define GPIO_PUP_PDN_CNTRL_REG0 57

volatile unsigned int *gpio;
void *gpioMap;
int fdGPIO;

//memory map initalization
void initUltrasonic() {
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
    
    fprintf(stderr, "Memory map initialization successful. \n");
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

        
	//disable pull-up pull-down
    gpio[GPIO_PUP_PDN_CNTRL_REG0] &= ~(0b00 << (2 * TX_MISO)); //no resistor for pin 9 TX_MISO
    gpio[GPIO_PUP_PDN_CNTRL_REG0] &= ~(0b00 << (2 * RX_MOSI)); //no resistor for pin 10 RX_MOSI
    
    //TODO: check if needed
    // clearing the output and input line
    gpio[GPCLR0] = 1 << TX_MISO;
    gpio[GPCLR0] = 1 << RX_MOSI;
}

void freeUltrasonic() {
    munmap( gpioMap, BLOCK_SIZE );
    close( fdGPIO );
}

//calculate distance and time things in python
void txHigh() {
    gpio[GPSET0] = 1 << TX_MISO;
}

void txLow() {
    gpio[GPCLR0] = 1 << TX_MISO;
}

int checkRxLevel() {
    if (gpio[GPLEV0] >> RX_MOSI == 1) {
        return 1;
    }
    else
    {
        if(gpio[GPLEV0] >> RX_MOSI == 0) {
            return 0;
        }
    }
	
	return -2;
}

void clearTxRx() {
    gpio[GPCLR0] = 1 << TX_MISO;
    gpio[GPCLR0] = 1 << RX_MOSI;
}
