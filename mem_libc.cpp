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

#include "mem_libc.h"

extern size_t last_malloc_size;
extern ADDRINT last_free_addr;

VOID alloc(ADDRINT address, size_t size);
VOID dealloc(ADDRINT address);

VOID mallocBefore(ADDRINT size) {
#ifdef _DEBUG
    LOG("malloc(" + decstr(size) + ")\n");
#endif
    last_malloc_size = size;
}

VOID freeBefore(ADDRINT addr) {
#ifdef _DEBUG
    LOG("free(" + hexstr(addr) + ")\n");
#endif
    last_free_addr = addr;
}

VOID mallocAfter(ADDRINT address) {
#ifdef _DEBUG
    LOG("  = " + hexstr(address) + "\n");
#endif
    alloc(address, last_malloc_size);
}

// XXX Change ADDRINT to UINT32
VOID freeAfter(ADDRINT ret) {
#ifdef _DEBUG
    LOG("  = " + decstr(ret) + "\n");
#endif
    dealloc(last_free_addr);
}
