/*
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

#include "utils.h"
#include "hwinit.h"
#include "di.h"
#include "timers.h"
#include "fs_utils.h"
#include "chainloader.h"
#include "lib/fatfs/ff.h"
#include "lib/log.h"
#include "lib/vsprintf.h"
#include "display/video_fb.h"
#include "btn.h"
#include "fuse.h"
#include "sdram.h"
#include "sdmmc/mmc.h"

extern void (*__program_exit_callback)(int rc);

static void *g_framebuffer;

static sdmmc_t emmc_sdmmc;

static void setup_display(void) {
    sdram_init();

    g_framebuffer = (void *) 0xC0000000;

    /* Zero-fill the framebuffer and register it as printk provider. */
    video_init(g_framebuffer);

    /* Initialize the display. */
    display_init();

    /* Set the framebuffer. */
    display_init_framebuffer(g_framebuffer);
}

static void exit_callback(int rc) {
    if (rc == 0)
        relocate_and_chainload();
    power_off();
}

static int load_payload(const char *path) {
    FILINFO info;
    size_t size;

    /* Check if the binary is present. */
    if (f_stat(path, &info) != FR_OK) {
        print(1, "Payload not found!\n");
        return -2;
    }

    size = (size_t)info.fsize;

    if (size > 0x1F000)
        return -3;

    /* Try to read the binary. */
    if (read_from_file((void *)0x40021000, size, path) != size) {
        print(SCREEN_LOG_LEVEL_WARNING, "Failed to read payload (%s)!\n", path);
        return -2;
    }

    g_chainloader_entry.src_address  = 0x40021000;
    g_chainloader_entry.size         = size;

    return 0;
}

static void draw_square(int off_x, int off_y, int x, int y, int multi, int color)
{
    int start_x = off_x + (x * multi);
    int start_y = off_y + (y * multi);
    uint32_t *fb = (uint32_t *) g_framebuffer;
#define fb_coord(x, y) (fb[(y) + (1280 - (x)) * (720 + 48)])
    
    for (int i = 0; i < multi; i++)
        for (int j = 0; j < multi; j++)
            if (start_y + j > 0 && start_y + j < 720)
                fb_coord(start_x + i, start_y + j) = color;
}

static void draw_table(const char *msg, int off_x, int off_y, int size)
{    
    int x = 0;
    int y = 0;
    
    for (int i = 0; i <    strlen(msg); i++)
    {
        if (msg[i] == '\n')
        {
            x = 0;
            ++y;
            continue;
        }
        
        if (msg[i] != '*')
        {
            int color = 0xFFFFFF;
            switch(msg[i])
            {
                case ' ': color = 0xBBBBBB; break;
                case 'L': color = 0x000000; break;
                case 'R': color = 0xFF0000; break;
                case 'G': color = 0x00FF00; break;
                case 'B': color = 0x0000FF; break;
                case 'W': color = 0xFFFFFF; break;
                case 'M': color = 0xFF00FF; break;
                case 'Y': color = 0xFFFF00; break;
                case 'C': color = 0x00FFFF; break;
                case 'O': color = 0xFF4500; break;
                case 'A': color = 0xD3D3D3; break;
            }
            draw_square(off_x, off_y, x, y, size, color);
        }
        
        ++x;
    }
}

const char *no_sd =
    "O   O OOOOO  OOOOO OOOO \n"
    "OO  O O   O  O     O   O\n"
    "O O O O   O  OOOOO O   O\n"
    "O  OO O   O      O O   O\n"
    "O   O OOOOO  OOOOO OOOO \n"
;

const char *big_bin =
    "OOOO  OOO OOOOO  OOOO  OOO O   O\n"
    "O   O  O  O      O   O  O  OO  O\n"
    "OOOO   O  O  OO  OOOO   O  O O O\n"
    "O   O  O  O   O  O   O  O  O  OO\n"
    "OOOO  OOO OOOOO  OOOO  OOO O   O\n"
;

const char *no_bin =
    "O   O OOOOO  OOOO  OOO O   O\n"
    "OO  O O   O  O   O  O  OO  O\n"
    "O O O O   O  OOOO   O  O O O\n"
    "O  OO O   O  O   O  O  O  OO\n"
    "O   O OOOOO  OOOO  OOO O   O\n"
;

const char *rocket_1 =
    "      L      \n"
    "     LOL     \n"
    "    LRORL    \n"
    "    LLLLL    \n"
    "    LAAAL    \n"
    "    LACAL    \n"
    "    LAAAL    \n"
    "    LAAAL    \n"
    "    LAAAL    \n"
    "   LLAAALL   \n"
    "  LALAAALAL  \n"
    " LLLLAAALLLL \n"
    "    LAAAL    \n"
    "     LLL     \n"
    "    ROYOR    \n"
    "    ROYOR    \n"
    "    ROYOR    \n"
    "     RYR     \n"
    "      R      \n"
    "             \n"
;

const char *rocket_2 =
    "      L      \n"
    "     LOL     \n"
    "    LRORL    \n"
    "    LLLLL    \n"
    "    LAAAL    \n"
    "    LACAL    \n"
    "    LAAAL    \n"
    "    LAAAL    \n"
    "    LAAAL    \n"
    "   LLAAALL   \n"
    "  LALAAALAL  \n"
    " LLLLAAALLLL \n"
    "    LAAAL    \n"
    "     LLL     \n"
    "    ROYOR    \n"
    "    ROYOR    \n"
    "     RYR     \n"
    "      R      \n"
    "             \n"
    "             \n"
;

const char *rocket_3 =
    "      L      \n"
    "     LOL     \n"
    "    LRORL    \n"
    "    LLLLL    \n"
    "    LAAAL    \n"
    "    LACAL    \n"
    "    LAAAL    \n"
    "    LAAAL    \n"
    "    LAAAL    \n"
    "   LLAAALL   \n"
    "  LALAAALAL  \n"
    " LLLLAAALLLL \n"
    "    LAAAL    \n"
    "     LLL     \n"
    "    ROYOR    \n"
    "    ROYOR    \n"
    "    ROYOR    \n"
    "    ROYOR    \n"
    "     RYR     \n"
    "      R      \n"
    
;

const char *ball =
    "                \n"
    "      RRRR      \n"
    "    RROOOORR    \n"
    "   ROOOOOOOOR   \n"
    "  ROOOOOOOOOOR  \n"
    "  ROOOOYYOOOOR  \n"
    " ROOOOYYYYOOOOR \n"
    " ROOOYYLYYYOOOR \n"
    " ROOOYYYYYYOOOR \n"
    " ROOOOYYYYOOOOR \n"
    "  ROOOOYYOOOOR  \n"
    "  ROOOOOOOOOOR  \n"
    "   ROOOOOOOOR   \n"
    "    RROOOORR    \n"
    "      RRRR      \n"
    "                \n"
    "                \n"
    "                \n"
    "                \n"
;

const char *stage_cleared =
    "*****OOOOO*OOOOO***O****OOOO*OOOOO******\n"
    "*****O*******O****O*O**O*****O**********\n"
    "*****O*******O***O***O*O*****O**********\n"
    "*****OOOOO***O***O***O*O**OO*OOOO*******\n"
    "*********O***O***OOOOO*O***O*O**********\n"
    "*****OOOOO***O***O***O**OOOO*OOOOO******\n"
    "****************************************\n"
    "*OOOO*O*****OOOOO***O***OOOO*OOOOO*OOOO*\n"
    "O*****O*****O******O*O**O**O*O*****O***O\n"
    "O*****O*****O*****O***O*OOOO*O*****O***O\n"
    "O*****O*****OOOO**O***O*OO***OOOO**O***O\n"
    "O*****O*****O*****OOOOO*O*O**O*****O***O\n"
    "*OOOO*OOOOO*OOOOO*O***O*O**O*OOOOO*OOOO*\n"
;

const char *update_done =
    "O***O*OOOO**OOOO****O***OOOOO*OOOOO\n"
    "O***O*O***O*O***O**O*O****O***O****\n"
    "O***O*OOOO**O***O*O***O***O***O****\n"
    "O***O*O*****O***O*O***O***O***OOOO*\n"
    "O***O*O*****O***O*OOOOO***O***O****\n"
    "*OOO**O*****OOOO**O***O***O***OOOOO\n"
    "***********************************\n"
    "******OOOO***OOO**O***O*OOOOO******\n"
    "******O***O*O***O*OO**O*O**********\n"
    "******O***O*O***O*O*O*O*OOOO*******\n"
    "******O***O*O***O*O**OO*O**********\n"
    "******OOOO***OOO**O***O*OOOOO******\n"
;

const char *update_failed =
    "O***O*OOOO**OOOO****O***OOOOO*OOOOO\n"
    "O***O*O***O*O***O**O*O****O***O****\n"
    "O***O*OOOO**O***O*O***O***O***O****\n"
    "O***O*O*****O***O*O***O***O***OOOO*\n"
    "O***O*O*****O***O*OOOOO***O***O****\n"
    "*OOO**O*****OOOO**O***O***O***OOOOO\n"
    "***********************************\n"
    "**OOOOO***O***O*O*****OOOOO*OOOO***\n"
    "**O******O*O****O*****O*****O***O**\n"
    "**OOOO**O***O*O*O*****O*****O***O**\n"
    "**O*****O***O*O*O*****OOOO**O***O**\n"
    "**O*****OOOOO*O*O*****O*****O***O**\n"
    "**O*****O***O*O*OOOOO*OOOOO*OOOO***\n"
;

static bool is_stage_cleared()
{
    uint32_t *fb = (uint32_t *) g_framebuffer;
#define fb_coord(x, y) (fb[(y) + (1280 - (x)) * (720 + 48)])
    
    for (int x = 10; x < 1270; x++)
        for (int y = 10; y < 340; y++)
            if ((fb_coord(x, y) & 0xFFFFFF) != 0xBBBBBB)
                return false;
    
    return true;
}

static void modchip_send(sdmmc_t *sdmmc, uint8_t *buf)
{
    sdmmc_command_t cmd = {};
    sdmmc_request_t req = {};

    cmd.opcode = MMC_GO_IDLE_STATE;
    cmd.arg = 0xAA5458BA;
    cmd.flags = SDMMC_RSP_R1;
    
    req.data = buf;
    req.blksz = 512;
    req.num_blocks = 1;
    req.is_read = false;
    req.is_multi_block = false;
    req.is_auto_cmd12 = false;
    
    sdmmc_send_cmd(sdmmc, &cmd, &req, 0);
}

static void modchip_recv(sdmmc_t *sdmmc, uint8_t *buf)
{
    sdmmc_command_t cmd = {};
    sdmmc_request_t req = {};

    cmd.opcode = MMC_GO_IDLE_STATE;
    cmd.arg = 0xAA5458BB;
    cmd.flags = SDMMC_RSP_R1;

    req.data = buf;
    req.blksz = 512;
    req.num_blocks = 1;
    req.is_read = true;
    req.is_multi_block = false;
    req.is_auto_cmd12 = false;
    
    sdmmc_send_cmd(sdmmc, &cmd, &req, 0);
}

enum DFU_ERRORS
{
    ERROR_SUCCESS = 0x70000000,
    ERROR_INVALID_PACKAGE_LENGTH = 0x40000000,
    ERROR_INVALID_OFFSET,
    ERROR_INVALID_LENGTH,
    ERROR_ERASE_FAILED,
    ERROR_FLASH_FAILED,
    ERROR_FAILED_TO_UPDATE_OB,
    
    ERROR_UNIMPLEMENTED = 0x50000000
};

enum COMMANDS
{
    PING = 0xA0F0,
    SET_OFFSET,
    READ_FLASH,
    READ_OB,
    SET_OB,
};

int main(void) {
    log_set_log_level(SCREEN_LOG_LEVEL_NONE);

    int ret = 0;
    uint8_t modchip_buf[512];

    nx_hwinit();
    fuse_init();
    sdmmc_init(&emmc_sdmmc, SDMMC_4, SDMMC_VOLTAGE_1V8, SDMMC_BUS_WIDTH_1BIT, SDMMC_SPEED_MMC_IDENT);

    if (!mount_sd())
        ret = -1;

    /* Set Boot to OFW flag if VOL_DOWN is pressed. */
    uint32_t btn = btn_read();
    if (btn & BTN_VOL_DOWN)
        ret = -6;
    
    if (ret == 0)
    {
        modchip_buf[0] = 0x44;
        modchip_send(&emmc_sdmmc, modchip_buf);
        do
        {
            mdelay(10);
            modchip_recv(&emmc_sdmmc, modchip_buf);
        }
        while (modchip_buf[0] != (uint8_t) ~0x44);
    }

    FIL f;
    FILINFO info;
    uint32_t new_version = 0;    
    UINT br = 0;
    if (ret != 0 || f_open(&f, "firmware.bin", FA_READ) != FR_OK || f_lseek(&f, 0x150) != FR_OK || f_read(&f, &new_version, 4, &br) != FR_OK || (new_version <= *(uint32_t *) &modchip_buf[1] && f_stat(".force_update", &info) != FR_OK))
    {
        modchip_buf[0] = 0x55;
        modchip_send(&emmc_sdmmc, modchip_buf);
        if (ret == 0)
            ret = load_payload("payload.bin");

        if (ret != 0)
        {
            setup_display();

            memset(g_framebuffer, 0xBB, (720 + 48) * 1280 * 4);

            if (ret == -1)
                draw_table(no_sd, 50, 50, 50);
            else if (ret == -2)
                draw_table(no_bin, 52, 52, 42);
            else if (ret == -3)
                draw_table(big_bin, 48, 48, 37);
            else if (ret == -6)
            {
                /* Boot to OFW */
                /* Some delay is required for modchip to enter sleep mode. */
                sdmmc_finish(&emmc_sdmmc);
                unmount_sd();
                /* Bypass fuse programming in package1. */
                panic(0x21);
            }

            display_backlight(true);
            
            const char * rockets[] = { rocket_1, rocket_2, rocket_3 };
            
            int idx = 0;
            int rocket_x = 558;
            int ball_x = 605;
            int ball_y = -100;
            while (!is_stage_cleared())
            {
                uint32_t btn = btn_read();
                
                if (ball_y <= -100 && btn & BTN_POWER)
                {
                    ball_x = rocket_x + 47;
                    ball_y = 340;
                }
                else if (ball_y > -100)
                {
                    draw_table(ball, ball_x, ball_y, 5);
                    ball_y -= 20;
                }
                
                if (btn & BTN_VOL_DOWN)
                    rocket_x -= 10;
                
                if (btn & BTN_VOL_UP)
                    rocket_x += 10;
                
                if (rocket_x < -100)
                    rocket_x = -100;
                
                if (rocket_x > 1180)
                    rocket_x = 1180;
                
                draw_table(rockets[++idx % 3], rocket_x, 420, 15);
                
                mdelay(45);
            }

            draw_table(stage_cleared, 50, 150, 30);
            
            mdelay(3000);

            display_backlight(false);

            display_end();
        }
    }
    else
    {
        modchip_buf[0] = 0xAA;
        modchip_send(&emmc_sdmmc, modchip_buf);
        setup_display();

        memset(g_framebuffer, 0xBB, (720 + 48) * 1280 * 4);

        display_backlight(true);
        
        modchip_buf[0] = 2;
        *(uint16_t *) &modchip_buf[1] = PING;
        modchip_send(&emmc_sdmmc, modchip_buf);
        do
        {
            mdelay(10);
            modchip_recv(&emmc_sdmmc, modchip_buf);
        }
        while (modchip_buf[0] != (uint8_t) ~2);
        if (*(uint32_t *) &modchip_buf[1] == ERROR_SUCCESS)
        {
            modchip_buf[0] = 6;
            *(uint16_t *) &modchip_buf[1] = SET_OFFSET;
            *(uint32_t *) &modchip_buf[3] = 0x3000;
            modchip_send(&emmc_sdmmc, modchip_buf);
            do
            {
                mdelay(10);
                modchip_recv(&emmc_sdmmc, modchip_buf);
            }
            while (modchip_buf[0] != (uint8_t) ~6);
            char last_progress = 0;
            if (*(uint32_t *) &modchip_buf[1] == ERROR_SUCCESS)
            {
                if (f_lseek(&f, 0) == FR_OK)
                {
                    uint32_t file_size = f_size(&f);
                    for (int i = 0; i < file_size; i += 64)
                    {
                        modchip_buf[0] = 64;
                        f_sync(&f);
                        if (f_read(&f, &modchip_buf[1], 64, &br) != FR_OK)
                        {
                            ret = -3;
                            break;
                        }
                        
                        modchip_send(&emmc_sdmmc, modchip_buf);
                        do
                        {
                            mdelay(10);
                            modchip_recv(&emmc_sdmmc, modchip_buf);
                        }
                        while (modchip_buf[0] != (uint8_t) ~64);
                        
                        if (*(uint32_t *) &modchip_buf[1] != ERROR_SUCCESS)
                        {
                            ret = -4;
                            break;
                        }
                        
                        char new_progress = (i * 100) / file_size;
                        if (new_progress > 100)
                            new_progress = 100;
                        if (new_progress != last_progress)
                        {
                            last_progress = new_progress;
                            draw_square(40, 354, last_progress, 0, 12, 0xFF0000);
                        }
                    }
                }
                else
                    ret = -5;
                f_close(&f);
            }
            else
                ret = -2;
        }
        else
            ret = -1;

        if (ret == 0)
            draw_table(update_done, 115, 150, 30);
        else
            draw_table(update_failed, 115, 150, 30);
        
        mdelay(3000);

        display_backlight(false);

        display_end();

        ret = -1;
    }
    
    sdmmc_finish(&emmc_sdmmc);
    unmount_sd();

    __program_exit_callback = exit_callback;
    return ret;
}