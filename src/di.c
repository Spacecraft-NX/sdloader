/*
 * Copyright (c) 2018 naehrwert
 * Copyright (c) 2018 CTCaer
 * Copyright (c) 2018-2020 Atmosphère-NX
 * Copyright (c) 2020 Spacecraft-NX
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
#include <string.h>

#include "di.h"
#include "timers.h"
#include "i2c.h"
#include "pmc.h"
#include "max77620.h"
#include "gpio.h"
#include "pinmux.h"
#include "car.h"
#include "apb_misc.h"
#include "utils.h"

#include "di.inl"

static uint32_t _display_ver = 0;

static void exec_cfg(uint32_t *base, const cfg_op_t *ops, uint32_t num_ops)
{
    for (uint32_t i = 0; i < num_ops; i++)
    {
        if (ops[i].is_delay)
        {
            if (ops[i].is_delay == 1)
                udelay(1000 * ops[i].off);
        }
        else
        {
            base[ops[i].off] = ops[i].val;
        }
    }
}

static void _display_dsi_wait(uint32_t timeout, uint32_t off, uint32_t mask)
{
    uint32_t end = get_time_us() + timeout;
    while ((get_time_us() < end) && (MAKE_DSI_REG(off) & mask)) {
        /* Wait. */
    }
    udelay(5);
}

void display_init()
{
    volatile tegra_car_t *car = car_get_regs();
    volatile tegra_pmc_t *pmc = pmc_get_regs();
    volatile tegra_pinmux_t *pinmux = pinmux_get_regs();
    int mariko = is_mariko();
    
    /* Power on. */
    if (mariko)
    {
        uint8_t val = 0x3A;
        i2c_send(I2C_5, MAX77620_PWR_I2C_ADDR, MAX77620_REG_SD2, &val, 1);
        val = 0x71;
        i2c_send(I2C_5, MAX77620_PWR_I2C_ADDR, MAX77620_REG_SD2_CFG, &val, 1);
        val = 0xD0;
        i2c_send(I2C_5, MAX77620_PWR_I2C_ADDR, MAX77620_REG_LDO0_CFG, &val, 1);
    }
    else
    {
        uint8_t val = 0xD0;
        i2c_send(I2C_5, MAX77620_PWR_I2C_ADDR, MAX77620_REG_LDO0_CFG, &val, 1);
        val = 0x09;
        i2c_send(I2C_5, MAX77620_PWR_I2C_ADDR, MAX77620_REG_GPIO7, &val, 1);
    }
    
    /* Enable MIPI CAL, DSI, DISP1, HOST1X, UART_FST_MIPI_CAL, DSIA LP clocks. */
    car->rst_dev_h_clr = 0x1010000;
    car->clk_enb_h_set = 0x1010000;
    car->rst_dev_l_clr = 0x18000000;
    car->clk_enb_l_set = 0x18000000;
    car->clk_enb_x_set = 0x20000;
    car->clk_source_uart_fst_mipi_cal = 0xA;
    car->clk_enb_w_set = 0x80000;
    car->clk_source_dsia_lp = 0xA;

    /* DPD idle. */
    pmc->io_dpd_req = 0x40000000;
    pmc->io_dpd2_req = 0x40000000;

    /* Configure pins. */
    pinmux->nfc_en &= ~PINMUX_TRISTATE;
    pinmux->nfc_int &= ~PINMUX_TRISTATE;
    pinmux->lcd_bl_pwm &= ~PINMUX_TRISTATE;
    pinmux->lcd_bl_en &= ~PINMUX_TRISTATE;
    pinmux->lcd_rst &= ~PINMUX_TRISTATE;
    
    /* Configure Backlight +-5V GPIOs. */
    gpio_configure_mode(GPIO_LCD_BL_P5V, GPIO_MODE_GPIO);
    gpio_configure_mode(GPIO_LCD_BL_N5V, GPIO_MODE_GPIO);
    gpio_configure_direction(GPIO_LCD_BL_P5V, GPIO_DIRECTION_OUTPUT);
    gpio_configure_direction(GPIO_LCD_BL_N5V, GPIO_DIRECTION_OUTPUT);
        
    /* Enable Backlight +5V. */
    gpio_write(GPIO_LCD_BL_P5V, GPIO_LEVEL_HIGH); 

    udelay(10000);

    /* Enable Backlight -5V. */
    gpio_write(GPIO_LCD_BL_N5V, GPIO_LEVEL_HIGH); 

    udelay(10000);

    /* Configure Backlight PWM, EN and RST GPIOs. */
    gpio_configure_mode(GPIO_LCD_BL_PWM, GPIO_MODE_GPIO);
    gpio_configure_mode(GPIO_LCD_BL_EN, GPIO_MODE_GPIO);
    gpio_configure_mode(GPIO_LCD_BL_RST, GPIO_MODE_GPIO);    
    gpio_configure_direction(GPIO_LCD_BL_PWM, GPIO_DIRECTION_OUTPUT);
    gpio_configure_direction(GPIO_LCD_BL_EN, GPIO_DIRECTION_OUTPUT);
    gpio_configure_direction(GPIO_LCD_BL_RST, GPIO_DIRECTION_OUTPUT);
    
    /* Enable Backlight EN. */
    gpio_write(GPIO_LCD_BL_EN, GPIO_LEVEL_HIGH);

    /* Configure display interface and display. */
    MAKE_MIPI_CAL_REG(0x60) = 0;
    if (mariko)
    {
        MAKE_MIPI_CAL_REG(0x58) = 0;
        APB_MISC_GP_DSI_PAD_CONTROL_0 = 0;
    }

    exec_cfg((uint32_t *)CAR_BASE, mariko ? _car_init_mariko : _car_init_erista, 4);
    exec_cfg((uint32_t *)DI_BASE, _di_init, 94);

    exec_cfg((uint32_t *)DSI_BASE, _dsi_init_p1, 8);
    if (mariko)
        exec_cfg((uint32_t *)DSI_BASE, _dsi_init_p2_mariko, 1);
    exec_cfg((uint32_t *)DSI_BASE, _dsi_init_p3, 14);
    if (mariko)
        exec_cfg((uint32_t *)DSI_BASE, _dsi_init_p4_mariko, 7);
    exec_cfg((uint32_t *)DSI_BASE, _dsi_init_p5, 10);
    exec_cfg((uint32_t *)DSI_BASE, mariko ? _dsi_phy_timing_0_mariko : _dsi_phy_timing_0_erista, 1);
    exec_cfg((uint32_t *)DSI_BASE, _dsi_init_p7, 12);
    exec_cfg((uint32_t *)DSI_BASE, mariko ? _dsi_phy_timing_0_mariko : _dsi_phy_timing_0_erista, 1);
    exec_cfg((uint32_t *)DSI_BASE, _dsi_init_p9, 14);

    udelay(10000);
    
    /* Enable Backlight RST. */
    gpio_write(GPIO_LCD_BL_RST, GPIO_LEVEL_HIGH);

    udelay(60000);

    MAKE_DSI_REG(DSI_BTA_TIMING) = 0x50204;
    MAKE_DSI_REG(DSI_WR_DATA) = 0x337;
    MAKE_DSI_REG(DSI_TRIGGER) = DSI_TRIGGER_HOST;
    _display_dsi_wait(250000, DSI_TRIGGER, (DSI_TRIGGER_HOST | DSI_TRIGGER_VIDEO));

    MAKE_DSI_REG(DSI_WR_DATA) = 0x406;
    MAKE_DSI_REG(DSI_TRIGGER) = DSI_TRIGGER_HOST;
    _display_dsi_wait(250000, DSI_TRIGGER, (DSI_TRIGGER_HOST | DSI_TRIGGER_VIDEO));

    MAKE_DSI_REG(DSI_HOST_CONTROL) = (DSI_HOST_CONTROL_TX_TRIG_HOST | DSI_HOST_CONTROL_IMM_BTA | DSI_HOST_CONTROL_CS | DSI_HOST_CONTROL_ECC);
    _display_dsi_wait(150000, DSI_HOST_CONTROL, DSI_HOST_CONTROL_IMM_BTA);

    udelay(5000);

    MAKE_DSI_REG(DSI_RD_DATA);
    MAKE_DSI_REG(DSI_RD_DATA);
    uint32_t id_raw = MAKE_DSI_REG(DSI_RD_DATA);
    uint8_t id_low = id_raw;
    uint32_t id_high = (id_raw << 8) >> 24;

    if (id_low == 0x10)
        id_high = 0;

    _display_ver = (id_high << 8) | id_low;
    switch (_display_ver)
    {
        case 0x10: // JDI
            exec_cfg((uint32_t *)DSI_BASE, _dsi_jdi_init, 48);
            break;
        case 0xF20: // Innolux
            exec_cfg((uint32_t *)DSI_BASE, _dsi_innolux_v1_init, 14);
            break;
        case 0xF30: // AUO
            exec_cfg((uint32_t *)DSI_BASE, _dsi_auo_v1_init, 14);
            break;
        case 0x1020: // Innolux 
        case 0x1030: // AUO
            exec_cfg((uint32_t *)DSI_BASE, _dsi_v2_init, 5);
            break;
    }

    udelay(20000);

    exec_cfg((uint32_t *)CAR_BASE, mariko ? _car_init2_mariko : _car_init2_erista, 3);

    exec_cfg((uint32_t *)DSI_BASE, _dsi_init2_p1, 1);
    exec_cfg((uint32_t *)DSI_BASE, mariko ? _dsi_phy_timing_0_mariko : _dsi_phy_timing_0_erista, 1);
    exec_cfg((uint32_t *)DSI_BASE, _dsi_init2_p3, 19);
    
    MAKE_DI_REG(DC_DISP_DISP_CLOCK_CONTROL) = 4;
    exec_cfg((uint32_t *)DSI_BASE, _dsi_init3, 10);

    udelay(10000);

    exec_cfg((uint32_t *)MIPI_CAL_BASE, _mipi_init, 4);
    exec_cfg((uint32_t *)MIPI_CAL_BASE, mariko ? _mipi_init2_mariko : _mipi_init2_erista, 2);

    if (mariko)
        exec_cfg((uint32_t *)DSI_BASE, _dsi_init4_mariko, 7);
    else
        exec_cfg((uint32_t *)DSI_BASE, _dsi_init4_erista, 4);

    if (mariko)
        exec_cfg((uint32_t *)MIPI_CAL_BASE, _mipi_init3_p1_mariko, 4);
    else
        exec_cfg((uint32_t *)MIPI_CAL_BASE, _mipi_init3_p1_erista, 4);
    exec_cfg((uint32_t *)MIPI_CAL_BASE, _mipi_init3_p2, 12);

    exec_cfg((uint32_t *)MIPI_CAL_BASE, mariko ? _mipi_init2_mariko : _mipi_init2_erista, 2);

    if (mariko)
        exec_cfg((uint32_t *)DSI_BASE, _dsi_init4_mariko, 7);
    else
        exec_cfg((uint32_t *)DSI_BASE, _dsi_init4_erista, 4);

    if (mariko)
        exec_cfg((uint32_t *)MIPI_CAL_BASE, _mipi_init3_p1_mariko, 4);
    else
        exec_cfg((uint32_t *)MIPI_CAL_BASE, _mipi_init3_p1_erista, 4);
    exec_cfg((uint32_t *)MIPI_CAL_BASE, _mipi_init3_p2, 12);

    udelay(10000);

    exec_cfg((uint32_t *)DI_BASE, _di_init2, 113);
}

void display_backlight(bool enable)
{
    /* Enable Backlight PWM. */
    gpio_write(GPIO_LCD_BL_PWM, enable ? GPIO_LEVEL_HIGH : GPIO_LEVEL_LOW);
}

void display_end()
{
    volatile tegra_car_t *car = car_get_regs();
    volatile tegra_pinmux_t *pinmux = pinmux_get_regs();
    
    /* Disable Backlight. */
    display_backlight(false);
    
    MAKE_DSI_REG(DSI_VIDEO_MODE_CONTROL) = 1;
    MAKE_DSI_REG(DSI_WR_DATA) = 0x2805;

    MAKE_DI_REG(DC_CMD_STATE_ACCESS) = (READ_MUX | WRITE_MUX);
    MAKE_DSI_REG(DSI_VIDEO_MODE_CONTROL) = 0;

    exec_cfg((uint32_t *)DI_BASE, _di_deinit, 17);

    udelay(40000);

    if (is_mariko())
    {
        exec_cfg((uint32_t *)CAR_BASE, _car_init_mariko, 4);
        exec_cfg((uint32_t *)DSI_BASE, _dsi_deinit_mariko, 16);
    }
    else
    {
        exec_cfg((uint32_t *)CAR_BASE, _car_init_erista, 4);
        exec_cfg((uint32_t *)DSI_BASE, _dsi_deinit_erista, 16);
    }

    udelay(10000);

    
    switch (_display_ver)
    {
        case 0x10: // JDI
            exec_cfg((uint32_t *)DSI_BASE, _dsi_jdi_deinit, 22);
            break;
        case 0xF30: // AUO
            exec_cfg((uint32_t *)DSI_BASE, _dsi_auo_v1_deinit, 38);
            break;
        case 0x1020: // Innolux
            exec_cfg((uint32_t *)DSI_BASE, _dsi_innolux_v2_deinit, 10);
            break;
        case 0x1030: // AUO
            exec_cfg((uint32_t *)DSI_BASE, _dsi_auo_v2_deinit, 1);
            break;
    }

    MAKE_DSI_REG(DSI_WR_DATA) = 0x1005;
    MAKE_DSI_REG(DSI_TRIGGER) = DSI_TRIGGER_HOST;

    udelay(50000);
    
    /* Disable Backlight RST. */
    gpio_write(GPIO_LCD_BL_RST, GPIO_LEVEL_LOW); 

    udelay(10000);
    
    /* Disable Backlight -5V. */
    gpio_write(GPIO_LCD_BL_N5V, GPIO_LEVEL_LOW); 

    udelay(10000);

    /* Disable Backlight +5V. */
    gpio_write(GPIO_LCD_BL_P5V, GPIO_LEVEL_LOW); 

    udelay(10000);

    /* Disable clocks. */
    car->rst_dev_h_set = 0x1010000;
    car->clk_enb_h_clr = 0x1010000;
    car->rst_dev_l_set = 0x18000000;
    car->clk_enb_l_clr = 0x18000000;

    MAKE_DSI_REG(DSI_PAD_CONTROL) = (DSI_PAD_CONTROL_VS1_PULLDN_CLK | DSI_PAD_CONTROL_VS1_PULLDN(0xF) | DSI_PAD_CONTROL_VS1_PDIO_CLK | DSI_PAD_CONTROL_VS1_PDIO(0xF));
    MAKE_DSI_REG(DSI_POWER_CONTROL) = 0;
    
    /* Backlight PWM. */
    gpio_configure_mode(GPIO_LCD_BL_PWM, GPIO_MODE_SFIO);
    
    pinmux->lcd_bl_pwm = ((pinmux->lcd_bl_pwm & ~PINMUX_TRISTATE) | PINMUX_TRISTATE);
    pinmux->lcd_bl_pwm = (((pinmux->lcd_bl_pwm >> 2) << 2) | 1);
}

void display_color_screen(uint32_t color)
{
    exec_cfg((uint32_t *)DI_BASE, _di_one_color, 8);

    /* Configure display to show single color. */
    MAKE_DI_REG(DC_WIN_AD_WIN_OPTIONS) = 0;
    MAKE_DI_REG(DC_WIN_BD_WIN_OPTIONS) = 0;
    MAKE_DI_REG(DC_WIN_CD_WIN_OPTIONS) = 0;
    MAKE_DI_REG(DC_DISP_BLEND_BACKGROUND_COLOR) = color;
    MAKE_DI_REG(DC_CMD_STATE_CONTROL) = ((MAKE_DI_REG(DC_CMD_STATE_CONTROL) & 0xFFFFFFFE) | GENERAL_ACT_REQ);

    udelay(35000);

    display_backlight(true);
}

uint32_t *display_init_framebuffer(void *address)
{
    static cfg_op_t conf[sizeof(_di_framebuffer)/sizeof(cfg_op_t)] = {0};
    if (conf[0].val == 0) {
        for (uint32_t i = 0; i < sizeof(_di_framebuffer)/sizeof(cfg_op_t); i++) {
            conf[i] = _di_framebuffer[i];
        }
    }

    uint32_t *lfb_addr = (uint32_t *)address;
    conf[19].val = (uint32_t)address;
    
    /* This configures the framebuffer @ address with a resolution of 1280x720 (line stride 768). */
    exec_cfg((uint32_t *)DI_BASE, conf, 32);

    udelay(35000);

    return lfb_addr;
}
