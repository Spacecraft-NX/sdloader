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
 
#ifndef FUSEE_CHAINLOADER_H
#define FUSEE_CHAINLOADER_H

#include <stddef.h>
#include <stdint.h>

#define CHAINLOADER_ARG_DATA_MAX_SIZE 0x6200
#define CHAINLOADER_MAX_ENTRIES       128

typedef struct chainloader_entry_t {
    uintptr_t src_address;
    size_t size;
} chainloader_entry_t;

extern chainloader_entry_t g_chainloader_entry;

void relocate_and_chainload(void);

#endif
