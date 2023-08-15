#include <kernel.h>
#include <kdata.h>
#include <printf.h>
#include <timer.h>
#include <stdbool.h>
#include <stdlib.h>
#include <blkdev.h>
#include "dev/devsd.h"
#include "picosdk.h"
#include "globals.h"
#include "config.h"
#include <hardware/spi.h>

#ifdef CONFIG_SD
#ifdef CONFIG_RC2040

/* RC2040 board */
/* Pico SPI GPIO connected to SD SPI1 */
#define Pico_SD_SCK 14
#define Pico_SD_TX  15
#define Pico_SD_RX  12
#define Pico_SD_CS  13

//Pico spi0 or spi1 must match GPIO pins used above.
#define Pico_SD_SPI_MOD spi1

#else

/* Pico SPI GPIO connected to SD SPIO - David Given's Arrangement */
#define Pico_SD_SCK 2
#define Pico_SD_TX  3
#define Pico_SD_RX  4
#define Pico_SD_CS  5

//Pico spi0 or spi1 must match GPIO pins used above.
#define Pico_SD_SPI_MOD spi0

#endif
#endif

#ifdef CONFIG_NET_W5500

#define Pico_ETH_SPI_SCK 18
#define Pico_ETH_SPI_TX  19
#define Pico_ETH_SPI_RX  16
#define Pico_ETH_SPI_CS  17

//Pico spi0 or spi1 must match GPIO pins used above.
#define Pico_ETH_SPI_MOD spi0

#endif

#ifdef CONFIG_SD
void sd_rawinit(void)
{
    //initilase GPIO ports
    gpio_init(Pico_SD_SCK );
    gpio_init(Pico_SD_TX);
    gpio_init(Pico_SD_RX);
    gpio_init(Pico_SD_CS);

    //set GPIO post function
    gpio_set_function(Pico_SD_SCK, GPIO_FUNC_SPI); // SCK
    gpio_set_function(Pico_SD_TX, GPIO_FUNC_SPI);  // TX
    gpio_set_function(Pico_SD_RX, GPIO_FUNC_SPI);  // RX
    gpio_set_function(Pico_SD_CS, GPIO_FUNC_SIO);  // CS
    gpio_set_dir(Pico_SD_CS, true);

    //initalise SPI module
    spi_init(Pico_SD_SPI_MOD, 250000);
    spi_set_format(Pico_SD_SPI_MOD, 8, 0, 0, SPI_MSB_FIRST);
}

void sd_spi_clock(bool go_fast)
{
    spi_set_baudrate(Pico_SD_SPI_MOD, 250000);
}

void sd_spi_raise_cs(void)
{
    gpio_put(Pico_SD_CS, true);
}

void sd_spi_lower_cs(void)
{
    gpio_put(Pico_SD_CS, false);
}

void sd_spi_transmit_byte(uint_fast8_t b)
{
    spi_write_blocking(Pico_SD_SPI_MOD, (uint8_t*) &b, 1);
}

uint_fast8_t sd_spi_receive_byte(void)
{
    uint8_t b;
    spi_read_blocking(Pico_SD_SPI_MOD, 0xff, (uint8_t*) &b, 1);
    return b;
}

bool sd_spi_receive_sector(void)
{
    spi_read_blocking(Pico_SD_SPI_MOD, 0xff, (uint8_t*) blk_op.addr, 512);
        return 0;
}

bool sd_spi_transmit_sector(void)
{
    spi_write_blocking(Pico_SD_SPI_MOD,  (uint8_t*) blk_op.addr, 512);
        return 0;
}
#endif

#ifdef CONFIG_NET_W5500

void eth_spi_rawinit(void)
{
    //initilase GPIO ports
    gpio_init(Pico_ETH_SPI_SCK);
    gpio_init(Pico_ETH_SPI_TX);
    gpio_init(Pico_ETH_SPI_RX);
    gpio_init(Pico_ETH_SPI_CS);

    //set GPIO post function
    gpio_set_function(Pico_ETH_SPI_SCK, GPIO_FUNC_SPI); // SCK
    gpio_set_function(Pico_ETH_SPI_TX, GPIO_FUNC_SPI);  // TX
    gpio_set_function(Pico_ETH_SPI_RX, GPIO_FUNC_SPI);  // RX
    gpio_set_function(Pico_ETH_SPI_CS, GPIO_FUNC_SIO);  // CS
    gpio_set_dir(Pico_ETH_SPI_CS, true);
    gpio_put(Pico_ETH_SPI_CS, true);

    //initalise SPI module
    kprintf("spi_init clk = %d\r\n", spi_init(Pico_ETH_SPI_MOD, 5000 * 1000));
}

void eth_spi_clock(bool go_fast)
{
    spi_set_baudrate(Pico_ETH_SPI_MOD, 5000 * 1000);
}

void eth_spi_raise_cs(void)
{
    gpio_put(Pico_ETH_SPI_CS, true);
}

void eth_spi_lower_cs(void)
{
    gpio_put(Pico_ETH_SPI_CS, false);
}

void eth_spi_transmit_byte(uint_fast8_t b)
{
    spi_write_blocking(Pico_ETH_SPI_MOD, (uint8_t*) &b, 1);
}

uint_fast8_t eth_spi_receive_byte(void)
{
    uint8_t b;
    spi_read_blocking(Pico_ETH_SPI_MOD, 0xff, (uint8_t*) &b, 1);
    return b;
}

#endif