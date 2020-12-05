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
 
#include "chainloader.h"

chainloader_entry_t g_chainloader_entry;

#pragma GCC optimize (3)

static void *xmemmove(void *dst, const void *src, size_t len)
{
    const uint8_t *src8 = (const uint8_t *)src;
    uint8_t *dst8 = (uint8_t *)dst;

    if (dst8 < src8) {
        for (size_t i = 0; i < len; i++) {
            dst8[i] = src8[i];
        }
    } else if (dst8 > src8) {
        for (size_t i = len; len > 0; len--)
            dst8[i - 1] = src8[i - 1];
    }

    return dst;
}

void relocate_and_chainload_main(void) {
    xmemmove((void *) 0x40010000, (const void *) g_chainloader_entry.src_address, g_chainloader_entry.size);

    ((void (*)()) 0x40010000)();
}
