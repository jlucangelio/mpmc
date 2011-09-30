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

#include "mem_win.h"

extern FILE *outfile;

VOID LocalAllocBefore(WINDOWS::DWORD dwFlags,
                      WINDOWS::DWORD dwBytes) {
    fprintf(outfile, "LocalAlloc(%x, %d)\n", dwFlags, dwBytes);
}

VOID LocalAllocAfter(WINDOWS::PVOID ret) {
    fprintf(outfile, "  LocalAlloc returns %x\n", ret);
}

VOID GlobalAllocBefore(WINDOWS::DWORD dwFlags,
                      WINDOWS::DWORD dwBytes) {
    fprintf(outfile, "GlobalAlloc(%x, %d)\n", dwFlags, dwBytes);
}

VOID GlobalAllocAfter(WINDOWS::PVOID ret) {
    fprintf(outfile, "  GlobalAlloc returns %x\n", ret);
}

VOID HeapAllocBefore(WINDOWS::HANDLE hHeap,
                     WINDOWS::DWORD dwFlags,
                     WINDOWS::DWORD dwBytes) {
    fprintf(outfile, "HeapAlloc(%x, %x, %d)\n", hHeap, dwFlags, dwBytes);
}

VOID HeapAllocAfter(WINDOWS::PVOID ret) {
    fprintf(outfile, "  HeapAlloc returns %x\n", ret);
}

/**
 *  PVOID
 *  RtlAllocateHeap( 
 *   IN PVOID  HeapHandle,
 *   IN ULONG  Flags,
 *   IN SIZE_T  Size
 *   );
 **/
VOID RtlAllocateHeapBefore(WINDOWS::HANDLE hHeap,
                           WINDOWS::DWORD dwFlags,
                           WINDOWS::DWORD dwBytes) {
    fprintf(outfile, "RtlAllocateHeap(%x, %x, %d)\n", hHeap, dwFlags, dwBytes);
}

VOID RtlAllocateHeapAfter(WINDOWS::PVOID ret) {
    fprintf(outfile, "  RtlAllocateHeap returns %x\n", ret);
}

/**
 * HLOCAL WINAPI LocalFree(
 * __in  HLOCAL hMem
 * );
 **/
VOID LocalFreeBefore(WINDOWS::PVOID hMem) {
    fprintf(outfile, "LocalFree(%x)\n", hMem);
}

VOID LocalFreeAfter(WINDOWS::PVOID ret) {
    fprintf(outfile, "  LocalFree returns %x\n", ret);
}

/**
 * HGLOBAL WINAPI GlobalFree(
 * __in  HGLOBAL hMem
 * );
 **/
VOID GlobalFreeBefore(WINDOWS::PVOID hMem) {
    fprintf(outfile, "GlobalFree(%x)\n", hMem);
}

VOID GlobalFreeAfter(WINDOWS::PVOID ret) {
    fprintf(outfile, "  GlobalFree returns %x\n", ret);
}

/**
 * BOOLEAN HeapFree( 
 *   IN PVOID  HeapHandle,
 *   IN ULONG  Flags,
 *   IN PVOID  HeapBase
 *   ); 
 **/
VOID HeapFreeBefore(WINDOWS::PVOID HeapHandle,
                       WINDOWS::DWORD Flags,
                       WINDOWS::PVOID HeapBase) {
    fprintf(outfile, "HeapFree(%x, %x, %x)\n", HeapHandle, Flags, HeapBase);
}

VOID HeapFreeAfter(WINDOWS::BOOLEAN HeapFreeStatus) {
    fprintf(outfile, "  HeapFree returns %d\n", HeapFreeStatus);
}

/**
 * BOOLEAN
 * RtlFreeHeap( 
 *   IN PVOID  HeapHandle,
 *   IN ULONG  Flags,
 *   IN PVOID  HeapBase
 *   ); 
 **/
VOID RtlFreeHeapBefore(WINDOWS::PVOID HeapHandle,
                       WINDOWS::DWORD Flags,
                       WINDOWS::PVOID HeapBase) {
    fprintf(outfile, "RtlFreeHeap(%x, %x, %x)\n", HeapHandle, Flags, HeapBase);
}

VOID RtlFreeHeapAfter(WINDOWS::BOOLEAN RtlFreeHeapStatus) {
    fprintf(outfile, "  RtlFreeHeap returns %x\n", RtlFreeHeapStatus);
}

/**
 * PVOID
 * RtlCreateHeap( 
 *   IN ULONG  Flags,
 *   IN PVOID  HeapBase  OPTIONAL,
 *   IN SIZE_T  ReserveSize  OPTIONAL,
 *   IN SIZE_T  CommitSize  OPTIONAL,
 *   IN PVOID  Lock  OPTIONAL,
 *   IN PRTL_HEAP_PARAMETERS  Parameters  OPTIONAL
 *   );
 **/
//VOID RtlCreateHeapBefore(ADDRINT size);
//VOID RtlCreateHeapAfter(ADDRINT size);

/**
 * PVOID
 * RtlDestroyHeap( 
 *   IN PVOID  HeapHandle
 *   );
 **/
//VOID RtlDestroyHeapBefore(ADDRINT size);
//VOID RtlDestroyHeapAfter(ADDRINT size);
