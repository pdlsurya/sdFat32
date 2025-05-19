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
#include "nrf_drv_spi.h"
#include "app_util_platform.h"
#include "nrf_gpio.h"
#include "boards.h"
#include "nrf.h"
#include "nrf_delay.h"
#include "sd_platform.h"

// Define the SPI and CS pin (customize per board)
#define SD_CS_PIN NRF_GPIO_PIN_MAP(0, 2)
#define SD_MOSI_PIN NRF_GPIO_PIN_MAP(1, 13)
#define SD_MISO_PIN NRF_GPIO_PIN_MAP(1, 10)
#define SD_SCK_PIN NRF_GPIO_PIN_MAP(1, 15)

#define SPI_INSTANCE 1 /**< SPI instance index. */

static const nrf_drv_spi_t spi = NRF_DRV_SPI_INSTANCE(SPI_INSTANCE); /**< SPI instance. */

static volatile bool spi_xfer_done = false;

static void spi_event_handler(nrf_drv_spi_evt_t const *p_event, void *p_context)
{
    spi_xfer_done = true;
}

void sd_spi_init(void)
{
    nrf_drv_spi_config_t spi_config = NRF_DRV_SPI_DEFAULT_CONFIG;
    spi_config.ss_pin = (uint8_t)NRF_SPI_PIN_NOT_CONNECTED;
    spi_config.miso_pin = SD_MISO_PIN;
    spi_config.mosi_pin = SD_MOSI_PIN;
    spi_config.sck_pin = SD_SCK_PIN;
    APP_ERROR_CHECK(nrf_drv_spi_init(&spi, &spi_config, spi_event_handler, NULL));

    nrf_gpio_cfg_output(SD_CS_PIN);
}

uint8_t sd_spi_transfer(uint8_t tx_byte)
{
    uint8_t rx_byte;

    APP_ERROR_CHECK(nrf_drv_spi_transfer(&spi, &tx_byte, 1, &rx_byte, 1));
    while (!spi_xfer_done)
        ;
    spi_xfer_done = false;

    return rx_byte;
}

void sd_spi_transfer_block(const uint8_t *tx, uint8_t *rx, uint32_t len)
{
    APP_ERROR_CHECK(nrf_drv_spi_transfer(&spi, tx, len, rx, len));
    while (!spi_xfer_done)
        ;
    spi_xfer_done = false;
}

void sd_delay_ms(uint32_t ms)
{
    nrf_delay_ms(ms);
}

void sd_cs_select(void)
{
    nrf_gpio_pin_clear(SD_CS_PIN);
}

void sd_cs_deselect(void)
{
    nrf_gpio_pin_set(SD_CS_PIN);
}
