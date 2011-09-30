/* Copyright 2011 Jorge Lucangeli Obes
 *
 * This file is part of mpmc.
 *
 * mpmc is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * mpmc is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with mpmc. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __SHADOW_H__
#define __SHADOW_H__

#include <stdlib.h>
#include <string.h>

#include "pin.H"
#include "MemCheck.h"
#include "consts.h"

#define NPOINTERS (1 << 16)
#define POINTER_TABLE_SIZE (NPOINTERS * sizeof(byte *))
#define DATA_TABLE_SIZE (NPOINTERS * sizeof(byte))

#ifdef TARGET_LINUX
#include <tr1/unordered_map>
#else
#include <unordered_map>
#endif

enum MEM_ERROR {E_UNINIT = 0, E_INV};
typedef struct memerror {
    MEM_ERROR type;
    ADDRINT address;
    size_t size;
} memerror_s;
typedef std::tr1::unordered_map<ADDRINT, memerror_s> errormap_t;

void init_shadow();

void check_read_1(ADDRINT address, ADDRINT ip);
void check_read_2(ADDRINT address, ADDRINT ip);
void check_read_4(ADDRINT address, ADDRINT ip);
void check_read_8(ADDRINT address, ADDRINT ip);
void check_read_16(ADDRINT address, ADDRINT ip);

void record_write_1(ADDRINT address, ADDRINT ip);
void record_write_2(ADDRINT address, ADDRINT ip);
void record_write_4(ADDRINT address, ADDRINT ip);
void record_write_8(ADDRINT address, ADDRINT ip);

#endif // __SHADOW_H__
