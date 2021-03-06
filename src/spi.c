#include <bcm2835.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {

    int val = 0xfe;
    if (argc == 2) 
      val = strtol(argv[1], NULL, 0);
    
    if (!bcm2835_init()) {
      printf("bcm2835_init failed. Are you running as root??\n");
      return 1;
    }

    if (!bcm2835_spi_begin()) {
      printf("bcm2835_spi_begin failed. Are you running as root??\n");
      return 1;
    }
    
    bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);      
    bcm2835_spi_setDataMode(BCM2835_SPI_MODE1);              
    bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_256);
    bcm2835_spi_chipSelect(BCM2835_SPI_CS0);                     
    bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);   
    
    // Send a byte to the slave and simultaneously read a byte back from the slave
    uint8_t send_data = val;
    uint8_t read_data = bcm2835_spi_transfer(send_data);
    printf("Sent to SPI: 0x%02X. Read back from SPI: 0x%02X.\n", send_data, read_data);
    
    bcm2835_spi_end();
    bcm2835_close();
    return 0;
}

