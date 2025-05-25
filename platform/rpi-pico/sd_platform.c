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
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "sd_platform.h"

// Define the SPI and CS pin (customize per board)
#define SD_CS_PIN 17
#define SD_SCK_PIN 18
#define SD_MOSI_PIN 19
#define SD_MISO_PIN 16

static spi_inst_t *spi = spi0;

void sd_spi_init(void)
{

    spi_init(spi, 16000000);
    spi_set_format(spi, 8, SPI_CPOL_0, SPI_CPHA_0, SPI_MSB_FIRST);

    gpio_set_function(SD_SCK_PIN, GPIO_FUNC_SPI);
    gpio_set_function(SD_MOSI_PIN, GPIO_FUNC_SPI);
    gpio_set_function(SD_MISO_PIN, GPIO_FUNC_SPI);

    gpio_init(SD_CS_PIN);
    gpio_set_dir(SD_CS_PIN, GPIO_OUT);
}

uint8_t sd_spi_transfer(uint8_t tx_byte)
{
    uint8_t rx_byte;
    spi_set_baudrate(spi, 16000000); // If SPI bus is shared with other high speed devices, reassign the baudrate for sd operation
    spi_write_read_blocking(spi, &tx_byte, &rx_byte, 1);
    return rx_byte;
}

void sd_spi_transfer_block(const uint8_t *tx, uint8_t *rx, uint32_t len)
{
    spi_set_baudrate(spi, 16000000); // If SPI bus is shared with other high speed devices, reassign the baudrate for sd operation
    spi_write_read_blocking(spi, tx, rx, len);
}

void sd_delay_ms(uint32_t ms)
{
    sleep_ms(ms);
}

void sd_cs_select(void)
{
    gpio_put(SD_CS_PIN, 0);
}

void sd_cs_deselect(void)
{
    gpio_put(SD_CS_PIN, 1);
}
