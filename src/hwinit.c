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
 
#include "hwinit.h"
#include "apb_misc.h"
#include "car.h"
#include "gpio.h"
#include "i2c.h"
#include "mc.h"
#include "pinmux.h"
#include "pmc.h"
#include "sysctr0.h"
#include "sysreg.h"
#include "timers.h"
#include "max77620.h"

void config_oscillators()
{
    volatile tegra_car_t *car = car_get_regs();
    volatile tegra_pmc_t *pmc = pmc_get_regs();
    
    car->spare_reg0 = ((car->spare_reg0 & 0xFFFFFFF3) | 4);
    
    SYSCTR0_CNTFID0_0 = 19200000;
    TIMERUS_USEC_CFG_0 = 0x45F;
    
    car->osc_ctrl = 0x50000071;
    pmc->osc_edpd_over = ((pmc->osc_edpd_over & 0xFFFFFF81) | 0xE);
    pmc->osc_edpd_over = ((pmc->osc_edpd_over & 0xFFBFFFFF) | 0x400000);
    pmc->cntrl2 = ((pmc->cntrl2 & 0xFFFFEFFF) | 0x1000);
    pmc->scratch188 = ((pmc->scratch188 & 0xFCFFFFFF) | 0x2000000);
    car->clk_sys_rate = 0x10;
    car->pllmb_base &= 0xBFFFFFFF;
    pmc->tsc_mult = ((pmc->tsc_mult & 0xFFFF0000) | 0x249F);      /* 0x249F = 19200000 * (16 / 32.768 kHz) */
    car->sclk_brst_pol = 0x20004444;
    car->super_sclk_div = 0x80000000;
    car->clk_sys_rate = 2;
}

void config_gpios()
{
    volatile tegra_pinmux_t *pinmux = pinmux_get_regs();
    
    pinmux->pe6 = PINMUX_INPUT;
    pinmux->ph6 = PINMUX_INPUT;
    
    gpio_configure_mode(TEGRA_GPIO(E, 6), GPIO_MODE_GPIO);
    gpio_configure_mode(TEGRA_GPIO(H, 6), GPIO_MODE_GPIO);
    gpio_configure_direction(TEGRA_GPIO(E, 6), GPIO_DIRECTION_INPUT);
    gpio_configure_direction(TEGRA_GPIO(H, 6), GPIO_DIRECTION_INPUT);

    i2c_config(I2C_5);
    
    /* Configure volume up/down as inputs. */
    gpio_configure_mode(GPIO_BUTTON_VOL_UP, GPIO_MODE_GPIO);
    gpio_configure_mode(GPIO_BUTTON_VOL_DOWN, GPIO_MODE_GPIO);
    gpio_configure_direction(GPIO_BUTTON_VOL_UP, GPIO_DIRECTION_INPUT);
    gpio_configure_direction(GPIO_BUTTON_VOL_DOWN, GPIO_DIRECTION_INPUT);
}

void nx_hwinit()
{
    /* Initialize the memory controller. */
    mc_enable();

    /* Configure oscillators. */
    config_oscillators();

	APB_MISC_PP_PINMUX_GLOBAL_0 = 0;
    
    /* Configure GPIOs. */
    config_gpios();
    
    /* Reboot I2C5. */
    clkrst_reboot(CARDEVICE_I2C5);
    
    /* Initialize I2C5. */
    i2c_init(I2C_5);
}