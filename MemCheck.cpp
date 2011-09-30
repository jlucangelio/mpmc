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

#include "pin.H"
#include "MemCheck.h"

#include <iostream>
#include <stdio.h>

#ifdef TARGET_WINDOWS
#include "mem_win.h"
#else
#include "mem_posix.h"
#endif
#include "mem_libc.h"

#include "instrum.h"
#include "consts.h"
#include "shadow.h"

FILE *outfile;
PIN_LOCK fileLock;

extern errormap_t errors;

//~ #define NUM_BUF_PAGES 1024
//~ BUFFER_ID bufId1, bufId2;

/** Print out help message. */
INT32 Usage() {
    cerr << "This tool checks for reads to uninitialized memory." << endl << endl;
    return -1;
}

/* ===================================================================== */
/* Instrumentation routines                                              */
/* ===================================================================== */

VOID Image(IMG img, VOID *v) {
#ifdef TARGET_LINUX
    INSTR_FUN(img, malloc);
    //~ INSTR_FUN(img, free);
    //~ INSTR_FUN_6(img, mmap);
    //~ INSTR_FUN_2(img, munmap);
#else
    INSTR_FUN_2(img, LocalAlloc);
    INSTR_FUN_2(img, GlobalAlloc);
    INSTR_FUN_3(img, HeapAlloc);
    INSTR_FUN_3(img, RtlAllocateHeap);
    INSTR_FUN(img, LocalFree);
    INSTR_FUN(img, GlobalFree);
    INSTR_FUN_3(img, HeapFree);
    INSTR_FUN_3(img, RtlFreeHeap);
    //~ INSTR_FUN(img, RtlCreateHeap);
    //~ INSTR_FUN(img, RtlDestroyHeap);
#endif
}

VOID Trace(TRACE trace, VOID *v) {
    UINT32 refSize;

    for (BBL bbl = TRACE_BblHead(trace); BBL_Valid(bbl); bbl=BBL_Next(bbl)) {
        for (INS ins = BBL_InsHead(bbl); INS_Valid(ins); ins=INS_Next(ins)) {
            if (INS_IsMemoryRead(ins)) {
                refSize = INS_MemoryReadSize(ins);
#ifdef _DEBUG
                LOG("read: refSize " + decstr(refSize) + "\n");
#endif

                switch (refSize) {
                    case 1:
                        CHECK_READ(1, IARG_MEMORYREAD_EA);
                        break;
                    case 2:
                        CHECK_READ(2, IARG_MEMORYREAD_EA);
                        break;
                    case 4:
                        CHECK_READ(4, IARG_MEMORYREAD_EA);
                        break;
                    case 8:
                        CHECK_READ(8, IARG_MEMORYREAD_EA);
                        break;
                    case 16:
                        CHECK_READ(16, IARG_MEMORYREAD_EA);
                        break;
                    default:
                        cerr << "read: Unhandled refSize: " << refSize << endl;
                }
            }
            if (INS_HasMemoryRead2(ins)) {
                refSize = INS_MemoryReadSize(ins);
#ifdef _DEBUG
                LOG("read2: refSize " + decstr(refSize) + "\n");
#endif

                switch (refSize) {
                    case 1:
                        CHECK_READ(1, IARG_MEMORYREAD2_EA);
                        break;
                    case 2:
                        CHECK_READ(2, IARG_MEMORYREAD2_EA);
                        break;
                    case 4:
                        CHECK_READ(4, IARG_MEMORYREAD2_EA);
                        break;
                    case 8:
                        CHECK_READ(8, IARG_MEMORYREAD2_EA);
                        break;
                    default:
                        cerr << "read2: Unhandled refSize: " << refSize << endl;
                }
            }
            if (INS_IsMemoryWrite(ins)) {
                refSize = INS_MemoryWriteSize(ins);
#ifdef _DEBUG
                LOG("write: refSize " + decstr(refSize) + "\n");
#endif

                switch (refSize) {
                    case 1:
                        RECORD_WRITE(1);
                        break;
                    case 2:
                        RECORD_WRITE(2);
                        break;
                    case 4:
                        RECORD_WRITE(4);
                        break;
                    case 8:
                        RECORD_WRITE(8);
                        break;
                    default:
                        cerr << "write: Unhandled refSize: " << refSize << endl;
                }
            }
        }
    }
}

/*!
 * Print out analysis results.
 * This function is called when the application exits.
 * @param[in]   code            exit code of the application
 * @param[in]   v               value specified by the tool in the 
 *                              PIN_AddFiniFunction function call
 */
VOID Fini(INT32 code, VOID *v) {
    GetLock(&fileLock, 1);
    for (errormap_t::const_iterator it = errors.begin(); it != errors.end(); ++it) {
         fprintf(outfile, "A: 0x%lx, %d 0x%lx %lu\n", it->first, it->second.type, it->second.address, it->second.size);
    }
    fclose(outfile);
    ReleaseLock(&fileLock);
}

/*!
 * The main procedure of the tool.
 * This function is called when the application image is loaded but not yet started.
 * @param[in]   argc            total number of elements in the argv array
 * @param[in]   argv            array of command line arguments, 
 *                              including pin -t <toolname> -- ...
 */
int main(int argc, char *argv[]) {
    PIN_InitSymbols();

    // Initialize PIN library. Print help message if -h(elp) is specified
    // in the command line or the command line is invalid 
    if (PIN_Init(argc, argv)) {
        return Usage();
    }

    outfile = fopen("memcheck.out", "w");
    if (!outfile) {
        cerr << "Couldn't open 'memcheck.out'" << endl;
        return 1;
    }

    InitLock(&fileLock);

    IMG_AddInstrumentFunction(Image, 0);
#ifdef TARGET_LINUX
    TRACE_AddInstrumentFunction(Trace, 0);
#endif
    PIN_AddFiniFunction(Fini, 0);

    init_shadow();

    // Start the program, never returns
    PIN_StartProgram();

    return 0;
}
