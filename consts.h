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

#ifndef __CONSTS_H__
#define __CONSTS_H__

#define INV_B 0xFF
#define INV_DB 0xFFFF
#define INV_QB 0xFFFFFFFF
#ifdef TARGET_IA32E
#define INV_W 0xFFFFFFFFFFFFFFFF
#else
#define INV_W 0xFFFFFFFF
#endif

#define UNINIT_B 0x01
#define UNINIT_DB 0x0101
#define UNINIT_QB 0x01010101
#ifdef TARGET_IA32E
#define UNINIT_W 0x1111111111111111
#else
#define UNINIT_W 0x11111111
#endif

#define INIT_B 0x02
#define INIT_DB 0x0202
#define INIT_QB 0x02020202
#ifdef TARGET_IA32E
#define INIT_W 0x0202020202020202
#else
#define INIT_W 0x02020202
#endif

#define MASK_48 0x0000FFFF00000000
#ifdef TARGET_IA32E
#define MASK_32 0x00000000FFFF0000
#define MASK_16 0x000000000000FFFF
#else
#define MASK_32 0xFFFF0000
#define MASK_16 0x0000FFFF
#endif

#ifdef TARGET_IA32E
#define PAGE_MASK 0xFFFFFFFFFFFF0000
#else
#define PAGE_MASK 0xFFFF0000
#endif

#endif // __CONST_H__
