//********************************************************************************//
//*                                                                              *//
//* Simple Example to write data to SPI Flash on ESP32 and                       *//
//* direct access by constant data pointer...                                    *//
//*                                                                              *//
//* ...do everything at your own risk!                                           *//
//*                                                                              *//
//********************************************************************************//



#include "esp_spi_flash.h"

uint8_t flashdata[64]={
0x00, 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70,
0x01, 0x11, 0x21, 0x31, 0x41, 0x51, 0x61, 0x71,
0x02, 0x12, 0x22, 0x32, 0x42, 0x52, 0x62, 0x72,
0x03, 0x13, 0x23, 0x33, 0x43, 0x53, 0x63, 0x73,

0x04, 0x14, 0x24, 0x34, 0x44, 0x54, 0x64, 0x74,
0x05, 0x15, 0x25, 0x35, 0x45, 0x55, 0x65, 0x75,
0x06, 0x16, 0x26, 0x36, 0x46, 0x56, 0x66, 0x76,
0x07, 0x17, 0x27, 0x37, 0x47, 0x57, 0x67, 0x77,
};

//constant data pointer for direct access
const void *ptr1;

void setup() {
   Serial.begin(115200);
  
//SPI FLASH IS 0x00000000..0x003fffff
//But first 0x10000 is bootloader ... ect
// ... so We try address 0x00300000+

    spi_flash_erase_sector(0x300);
    spi_flash_write(0x00300000, flashdata, sizeof(flashdata));
    ///spi_flash_read(0x00300000, flashdata, sizeof(flashdata));

    spi_flash_mmap_handle_t handle1;
    printf("Mapping %x (+%x)\n", 0x00300000, sizeof(flashdata));
    ESP_ERROR_CHECK( spi_flash_mmap(0x00300000, sizeof(flashdata), SPI_FLASH_MMAP_DATA, &ptr1, &handle1) );
    printf("mmap_res: handle=%d ptr=%p\n", handle1, ptr1);

    for (uint16_t tmp=0;tmp<sizeof(flashdata);tmp++) Serial.println(((const uint8_t*)ptr1)[tmp],HEX);
    
}

void loop() {
}
