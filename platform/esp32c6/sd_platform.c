/*
 * MIT License
 *
 * Copyright (c) 2025 Surya Poudel
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "sd_platform.h"
#include "spi_drv.h"
#include "gpio_drv.h"
#include "delay.h"

// Define the SPI and CS pin (customize per board)
#define SD_CS_PIN 20
#define SD_SCK_PIN 19
#define SD_MOSI_PIN 18
#define SD_MISO_PIN 14

static spi_device_handle_t dev;

void sd_spi_init(void)
{
    spi_pins_t spi_pins = {.mosi = SD_MOSI_PIN, .miso = SD_MISO_PIN, .sck = SD_SCK_PIN};
    spi_init(spi_pins);

    dev.cs_pin = SD_CS_PIN;
    dev.id = 3;
    dev.speed_hz = 16000000;
    dev.mode = 0;
    spi_device_config(&dev);
}

uint8_t sd_spi_transfer(uint8_t tx_byte)
{
    return spi_transfer_byte(&dev, tx_byte);
}

void sd_spi_transfer_block( uint8_t *tx, uint8_t *rx, uint32_t len)
{
    spi_transceive(&dev, tx, rx, len);
}

void sd_delay_ms(uint32_t ms)
{
   delay_ms(ms);
}

void sd_cs_select(void)
{
    gpio_write(SD_CS_PIN, 0);
}

void sd_cs_deselect(void)
{
    gpio_write(SD_CS_PIN, 1);
}
