
#define spi_select_port eth_spi_lower_cs
#define spi_select_none	eth_spi_raise_cs

#define spi_send	eth_spi_transmit_byte
#define spi_recv	eth_spi_receive_byte
