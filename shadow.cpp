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

#include "shadow.h"

#ifdef TARGET_IA32E
byte **t1[NPOINTERS];
#else
byte *t2[NPOINTERS];
#endif

size_t last_malloc_size = 0;
ADDRINT last_free_addr = (ADDRINT)NULL;
std::tr1::unordered_map<ADDRINT, size_t> allocs;
size_t t1_indexcount = 0;

errormap_t errors;

void init_shadow() {
#ifdef TARGET_IA32E
    memset(t1, INV_B, POINTER_TABLE_SIZE); /* 64 K pointers */
#else
    memset(t2, INV_B, POINTER_TABLE_SIZE);
#endif
}

inline byte *TableWalk(ADDRINT address) {
#ifdef _DEBUG
    LOG("TW(" + hexstr(address) + ")\n");
#endif
#ifdef TARGET_IA32E
    byte **t2;
#endif
    byte *t3;
#ifdef TARGET_IA32E
    int l1_index, l2_index, l3_index;
#else
    int l2_index, l3_index;
#endif

#ifdef TARGET_IA32E
    l1_index = (address & MASK_48) >> 32;
    l2_index = (address & MASK_32) >> 16;
    l3_index = (address & MASK_16);
#else
    l2_index = (address & MASK_32) >> 16;
    l3_index = (address & MASK_16);
#endif

#ifdef TARGET_IA32E
    t2 = t1[l1_index];
    if ((unsigned long)t2 == INV_W) {
        t2 = (byte **)malloc(POINTER_TABLE_SIZE);
        memset(t2, INV_B, POINTER_TABLE_SIZE);
        t1[l1_index] = t2;
    }
#endif

    t3 = t2[l2_index];
    if ((unsigned long)t3 == INV_W) {
        t3 = (byte *)malloc(DATA_TABLE_SIZE);
        memset(t3, INV_B, DATA_TABLE_SIZE);
        t2[l2_index] = t3;
    }
#ifdef _DEBUG
    LOG("TW returns: " + hexstr(t3 + l3_index) + "\n");
#endif
    return (t3 + l3_index);
}

VOID alloc(ADDRINT address, size_t size) {
#ifdef _DEBUG
    LOG("alloc(" + hexstr(address) + ", " + decstr(size) + ")\n");
#endif
    int bsteps = 0;
    int wsteps = 0;
    byte *bentry;
    unsigned long *wentry;

    //~ // Set [addr, addr + size] as allocated
    if (size >= sizeof(long)) {
        wsteps = size / sizeof(long);
        wentry = (unsigned long *)TableWalk(address);

        for (int i = 0; i < wsteps; i++) {
            if (((unsigned long)(address + i * sizeof(long)) & PAGE_MASK) != ((unsigned long)address & PAGE_MASK)) {
                wentry = (unsigned long *)TableWalk(address + i * sizeof(long));
            }
            *wentry = UNINIT_W;
            wentry++;
        }
    }

    bsteps = size % sizeof(long);
    bentry = TableWalk(address + wsteps * sizeof(long));

    for (int i = 0; i < bsteps; i++) {
        *(bentry + i) = UNINIT_B;
    }

    allocs[address] = size;
}

VOID dealloc(ADDRINT address) {
#ifdef _DEBUG
    LOG("dealloc(" + hexstr(address) + ")\n");
#endif
    size_t size = allocs[address];

    int bsteps = 0;
    int wsteps = 0;
    byte *bentry;
    unsigned long *wentry;

    //~ // Set [addr, addr + size] as deallocated
    if (size >= sizeof(long)) {
        wsteps = size / sizeof(long);
        wentry = (unsigned long *)TableWalk(address);

        for (int i = 0; i < wsteps; i++) {
            if (((unsigned long)(address + i * sizeof(long)) & PAGE_MASK) != ((unsigned long)address & PAGE_MASK)) {
                wentry = (unsigned long *)TableWalk(address + i * sizeof(long));
            }
            *wentry = INV_W;
            wentry++;
        }
    }

    bsteps = size % sizeof(long);
    bentry = TableWalk(address + wsteps * sizeof(long));

    for (int i = 0; i < bsteps; i++) {
        *(bentry + i) = INV_B;
    }

    allocs.erase(address);
}

void check_read_1(ADDRINT address, ADDRINT ip) {
#ifdef _DEBUG
    LOG("check_read_1(" + hexstr(address) + ", " + hexstr(ip) + ")\n");
#endif
    byte *shadow = TableWalk(address);
    if (*shadow == UNINIT_B) {
        memerror_s me = {E_UNINIT, address, 1};
        errors[ip] = me;
    }
}

void check_read_2(ADDRINT address, ADDRINT ip) {
#ifdef _DEBUG
    LOG("check_read_2(" + hexstr(address) + ", " + hexstr(ip) + ")\n");
#endif
    unsigned short *shadow = (unsigned short *)TableWalk(address);
    if (*shadow == UNINIT_DB) {
        memerror_s me = {E_UNINIT, address, 2};
        errors[ip] = me;
    }
}

void check_read_4(ADDRINT address, ADDRINT ip) {
#ifdef _DEBUG
    LOG("check_read_4(" + hexstr(address) + ", " + hexstr(ip) + ")\n");
#endif
    unsigned int *shadow = (unsigned int *)TableWalk(address);
    if (*shadow == UNINIT_QB) {
        memerror_s me = {E_UNINIT, address, 4};
        errors[ip] = me;
    }
}

void check_read_8(ADDRINT address, ADDRINT ip) {
#ifdef _DEBUG
    LOG("check_read_8(" + hexstr(address) + ", " + hexstr(ip) + ")\n");
#endif
    unsigned long *shadow = (unsigned long *)TableWalk(address);
    if (*shadow == UNINIT_W) {
        memerror_s me = {E_UNINIT, address, 8};
        errors[ip] = me;
    }
}

void check_read_16(ADDRINT address, ADDRINT ip) {
#ifdef _DEBUG
    LOG("check_read_16(" + hexstr(address) + ", " + hexstr(ip) + ")\n");
#endif
    unsigned long *shadow = (unsigned long *)TableWalk(address);
    if (*shadow == UNINIT_W) {
        memerror_s me = {E_UNINIT, address, 8};
        errors[ip] = me;
    }
    if (*++shadow == UNINIT_W) {
        memerror_s me = {E_UNINIT, address, 8};
        errors[ip] = me;
    }
}

void record_write_1(ADDRINT address, ADDRINT ip) {
#ifdef _DEBUG
    LOG("record_write_1(" + hexstr(address) + ", " + hexstr(ip) + ")\n");
#endif
    *TableWalk(address) = INIT_B;
}
void record_write_2(ADDRINT address, ADDRINT ip) {
#ifdef _DEBUG
    LOG("record_write_2(" + hexstr(address) + ", " + hexstr(ip) + ")\n");
#endif
    *(unsigned short *)TableWalk(address) = INIT_DB;
}
void record_write_4(ADDRINT address, ADDRINT ip) {
#ifdef _DEBUG
    LOG("record_write_4(" + hexstr(address) + ", " + hexstr(ip) + ")\n");
#endif
    *(unsigned int *)TableWalk(address) = INIT_QB;
}
void record_write_8(ADDRINT address, ADDRINT ip) {
#ifdef _DEBUG
    LOG("record_write_8(" + hexstr(address) + ", " + hexstr(ip) + ")\n");
#endif
    *(unsigned long *)TableWalk(address) = INIT_W;
}
