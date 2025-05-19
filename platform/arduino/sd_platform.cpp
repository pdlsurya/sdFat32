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
#include <stdarg.h>
#include <Arduino.h>
#include <SPI.h>
#include "sd_platform.h"

#define EXTERNC extern "C"

// Define the SPI and CS pin (customize per board)
#define SD_CS_PIN 5

EXTERNC void serial_printf(const char *format, ...)
{
    char buffer[256];
    va_list args;
    va_start(args, format);
    vsprintf(buffer, format, args);
    va_end(args);
    Serial.print(buffer);
}

EXTERNC void sd_spi_init(void)
{
    SPI.begin();
    pinMode(SD_CS_PIN, OUTPUT);
    digitalWrite(SD_CS_PIN, HIGH);
}

EXTERNC uint8_t sd_spi_transfer(uint8_t data)
{
    return SPI.transfer(data);
}

EXTERNC void sd_spi_transfer_block(const uint8_t *tx, uint8_t *rx, uint32_t len)
{
    for (uint32_t i = 0; i < len; ++i)
    {
        uint8_t dout = tx ? tx[i] : 0xFF;
        uint8_t din = SPI.transfer(dout);
        if (rx)
        {
            rx[i] = din;
        }
    }
}

EXTERNC void sd_delay_ms(uint32_t ms)
{
    delay(ms);
}

EXTERNC void sd_cs_select(void)
{
    digitalWrite(SD_CS_PIN, LOW);
}

EXTERNC void sd_cs_deselect(void)
{
    digitalWrite(SD_CS_PIN, HIGH);
}
