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

#ifndef __INSTR_H__
#define __INSTR_H__

#ifdef TARGET_LINUX

#define INSTR_FUN(img, name)                                                \
do {                                                                        \
    RTN __##name##Rtn = RTN_FindByName(img, #name);                         \
    if (RTN_Valid(__##name##Rtn)) {                                         \
        RTN_Open(__##name##Rtn);                                            \
        RTN_InsertCall(__##name##Rtn, IPOINT_BEFORE, (AFUNPTR)name##Before, \
                       IARG_FUNCARG_ENTRYPOINT_VALUE, 0, IARG_END);         \
        RTN_InsertCall(__##name##Rtn, IPOINT_AFTER, (AFUNPTR)name##After,   \
                       IARG_FUNCRET_EXITPOINT_VALUE, IARG_END);             \
        RTN_Close(__##name##Rtn);                                           \
    }                                                                       \
} while(0)

#define INSTR_FUN_2(img, name)                                              \
do {                                                                        \
    RTN __##name##Rtn = RTN_FindByName(img, #name);                         \
    if (RTN_Valid(__##name##Rtn)) {                                         \
        RTN_Open(__##name##Rtn);                                            \
        RTN_InsertCall(__##name##Rtn, IPOINT_BEFORE, (AFUNPTR)name##Before, \
                       IARG_FUNCARG_ENTRYPOINT_VALUE, 0,                    \
                       IARG_FUNCARG_ENTRYPOINT_VALUE, 1, IARG_END);         \
        RTN_InsertCall(__##name##Rtn, IPOINT_AFTER, (AFUNPTR)name##After,   \
                       IARG_FUNCRET_EXITPOINT_VALUE, IARG_END);             \
        RTN_Close(__##name##Rtn);                                           \
    }                                                                       \
} while(0)

#define INSTR_FUN_6(img, name)                                              \
do {                                                                        \
    RTN __##name##Rtn = RTN_FindByName(img, #name);                         \
    if (RTN_Valid(__##name##Rtn)) {                                         \
        RTN_Open(__##name##Rtn);                                            \
        RTN_InsertCall(__##name##Rtn, IPOINT_BEFORE, (AFUNPTR)name##Before, \
                       IARG_FUNCARG_ENTRYPOINT_VALUE, 0,                    \
                       IARG_FUNCARG_ENTRYPOINT_VALUE, 1,                    \
                       IARG_FUNCARG_ENTRYPOINT_VALUE, 2,                    \
                       IARG_FUNCARG_ENTRYPOINT_VALUE, 3,                    \
                       IARG_FUNCARG_ENTRYPOINT_VALUE, 4,                    \
                       IARG_FUNCARG_ENTRYPOINT_VALUE, 5, IARG_END);         \
        RTN_InsertCall(__##name##Rtn, IPOINT_AFTER, (AFUNPTR)name##After,   \
                       IARG_FUNCRET_EXITPOINT_VALUE, IARG_END);             \
        RTN_Close(__##name##Rtn);                                           \
    }                                                                       \
} while(0)

#else

#define INSTR_FUN(img, name)                                                                        \
do {                                                                                                \
    for (SYM __sym = IMG_RegsymHead(img); SYM_Valid(__sym); __sym = SYM_Next(__sym)) {              \
        string __undFuncName = PIN_UndecorateSymbolName(SYM_Name(__sym), UNDECORATION_NAME_ONLY);   \
        if (__undFuncName == #name) {                                                               \
            RTN __##name##Rtn = RTN_FindByAddress(IMG_LowAddress(img) + SYM_Value(__sym));          \
            if (RTN_Valid(__##name##Rtn)) {                                                         \
                RTN_Open(__##name##Rtn);                                                            \
                RTN_InsertCall(__##name##Rtn, IPOINT_BEFORE, (AFUNPTR)name##Before,                 \
                               IARG_FUNCARG_ENTRYPOINT_VALUE, 0, IARG_END);                         \
                RTN_InsertCall(__##name##Rtn, IPOINT_AFTER, (AFUNPTR)name##After,                   \
                               IARG_FUNCRET_EXITPOINT_VALUE,                                        \
                               IARG_END);                                                           \
                RTN_Close(__##name##Rtn);                                                           \
            }                                                                                       \
        }                                                                                           \
    }                                                                                               \
} while(0)

#define INSTR_FUN_2(img, name)                                                                      \
do {                                                                                                \
    for (SYM __sym = IMG_RegsymHead(img); SYM_Valid(__sym); __sym = SYM_Next(__sym)) {              \
        string __undFuncName = PIN_UndecorateSymbolName(SYM_Name(__sym), UNDECORATION_NAME_ONLY);   \
        if (__undFuncName == #name) {                                                               \
            RTN __##name##Rtn = RTN_FindByAddress(IMG_LowAddress(img) + SYM_Value(__sym));          \
            if (RTN_Valid(__##name##Rtn)) {                                                         \
                RTN_Open(__##name##Rtn);                                                            \
                RTN_InsertCall(__##name##Rtn, IPOINT_BEFORE, (AFUNPTR)name##Before,                 \
                               IARG_FUNCARG_ENTRYPOINT_VALUE, 0,                                    \
                               IARG_FUNCARG_ENTRYPOINT_VALUE, 1,                                    \
                               IARG_END);                                                           \
                RTN_InsertCall(__##name##Rtn, IPOINT_AFTER, (AFUNPTR)name##After,                   \
                               IARG_FUNCRET_EXITPOINT_VALUE,                                        \
                               IARG_END);                                                           \
                RTN_Close(__##name##Rtn);                                                           \
            }                                                                                       \
        }                                                                                           \
    }                                                                                               \
} while(0)

#define INSTR_FUN_3(img, name)                                                                      \
do {                                                                                                \
    for (SYM __sym = IMG_RegsymHead(img); SYM_Valid(__sym); __sym = SYM_Next(__sym)) {              \
        string __undFuncName = PIN_UndecorateSymbolName(SYM_Name(__sym), UNDECORATION_NAME_ONLY);   \
        if (__undFuncName == #name) {                                                               \
            RTN __##name##Rtn = RTN_FindByAddress(IMG_LowAddress(img) + SYM_Value(__sym));          \
            if (RTN_Valid(__##name##Rtn)) {                                                         \
                RTN_Open(__##name##Rtn);                                                            \
                RTN_InsertCall(__##name##Rtn, IPOINT_BEFORE, (AFUNPTR)name##Before,                 \
                               IARG_FUNCARG_ENTRYPOINT_VALUE, 0,                                    \
                               IARG_FUNCARG_ENTRYPOINT_VALUE, 1,                                    \
                               IARG_FUNCARG_ENTRYPOINT_VALUE, 2,                                    \
                               IARG_END);                                                           \
                RTN_InsertCall(__##name##Rtn, IPOINT_AFTER, (AFUNPTR)name##After,                   \
                               IARG_FUNCRET_EXITPOINT_VALUE,                                        \
                               IARG_END);                                                           \
                RTN_Close(__##name##Rtn);                                                           \
            }                                                                                       \
        }                                                                                           \
    }                                                                                               \
} while(0)
#endif

#define CHECK_READ(nbytes, ea) \
INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)check_read_##nbytes,    \
                    ea,                                             \
                    IARG_INST_PTR,                                  \
                    IARG_END)

#define RECORD_WRITE(nbytes) \
INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)record_write_##nbytes,    \
                    IARG_MEMORYWRITE_EA,                              \
                    IARG_INST_PTR,                                    \
                    IARG_END)

#endif // __INSTR_H__
