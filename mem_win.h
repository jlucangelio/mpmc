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

#ifndef __MEM_WIN_H__
#define __MEM_WIN_H__

#include <iostream>

namespace WINDOWS
{
#include<windows.h>

// NT internals
typedef PVOID PRTL_HEAP_PARAMETERS; // TODO: define this struct some day...
}

/**
 * HLOCAL WINAPI LocalAlloc(
 * __in  UINT uFlags,
 * __in  SIZE_T uBytes
 * );
 **/
VOID LocalAllocBefore(WINDOWS::DWORD dwFlags,
                      WINDOWS::DWORD dwBytes);
VOID LocalAllocAfter(WINDOWS::PVOID ret);

/**
 * HLOCAL WINAPI LocalFree(
 * __in  HLOCAL hMem
 * );
 **/
VOID LocalFreeBefore(WINDOWS::PVOID ret);
VOID LocalFreeAfter(WINDOWS::PVOID ret);


/**
 * HGLOBAL WINAPI GlobalAlloc(
 * __in  UINT uFlags,
 * __in  SIZE_T dwBytes
 * );
 **/
VOID GlobalAllocBefore(WINDOWS::DWORD uFlags, 
                       WINDOWS::DWORD SIZE_T);
VOID GlobalAllocAfter(WINDOWS::PVOID ret);

/**
 * HGLOBAL WINAPI GlobalFree(
 * __in  HGLOBAL hMem
 * );
 **/
VOID GlobalFreeBefore(WINDOWS::PVOID ret);
VOID GlobalFreeAfter(WINDOWS::PVOID ret);


/**
 *  PVOID HeapAlloc( 
 *   IN PVOID  HeapHandle,
 *   IN ULONG  Flags,
 *   IN SIZE_T  Size
 *   );
 **/
VOID HeapAllocBefore(WINDOWS::HANDLE hHeap,
                           WINDOWS::DWORD dwFlags,
                           WINDOWS::DWORD dwBytes);
VOID HeapAllocAfter(WINDOWS::PVOID HeapBase);

/**
 * BOOLEAN HeapFree( 
 *   IN PVOID  HeapHandle,
 *   IN ULONG  Flags,
 *   IN PVOID  HeapBase
 *   ); 
 **/
VOID HeapFreeBefore(WINDOWS::PVOID HeapHandle,
                       WINDOWS::DWORD Flags,
                       WINDOWS::PVOID HeapBase);
VOID HeapFreeAfter(WINDOWS::BOOLEAN RtlFreeHeapStatus);


/**
 *  PVOID RtlAllocateHeap( 
 *   IN PVOID  HeapHandle,
 *   IN ULONG  Flags,
 *   IN SIZE_T  Size
 *   );
 **/
VOID RtlAllocateHeapBefore(WINDOWS::HANDLE hHeap,
                           WINDOWS::DWORD dwFlags,
                           WINDOWS::DWORD dwBytes);
VOID RtlAllocateHeapAfter(WINDOWS::PVOID HeapBase);

/**
 * BOOLEAN RtlFreeHeap( 
 *   IN PVOID  HeapHandle,
 *   IN ULONG  Flags,
 *   IN PVOID  HeapBase
 *   ); 
 **/
VOID RtlFreeHeapBefore(WINDOWS::PVOID HeapHandle,
                       WINDOWS::DWORD Flags,
                       WINDOWS::PVOID HeapBase);
VOID RtlFreeHeapAfter(WINDOWS::BOOLEAN RtlFreeHeapStatus);

/**
 * PVOID RtlReAllocateHeap(
 *   IN PVOID                HeapHandle,
 *   IN ULONG                Flags,
 *   IN PVOID                HeapBase,
 *   IN ULONG                Size 
 *   );
 **/
VOID RtlReAllocateHeapBefore(WINDOWS::PVOID HeapHandle,
                             WINDOWS::DWORD Flags,
                             WINDOWS::PVOID HeapBase,
                             WINDOWS::DWORD Size);
VOID RtlReAllocateHeapAfter(WINDOWS::PVOID HeapHandle);


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
VOID RtlCreateHeapBefore(WINDOWS::IN ULONG  Flags,
                         WINDOWS::PVOID  HeapBase,
                         WINDOWS::SIZE_T  ReserveSize,
                         WINDOWS::SIZE_T  CommitSize,
                         WINDOWS::PVOID  Lock,
                         WINDOWS::PRTL_HEAP_PARAMETERS  Parameters);
VOID RtlCreateHeapAfter(WINDOWS::PVOID HeapHandle);

/**
 * PVOID
 * RtlDestroyHeap( 
 *   IN PVOID  HeapHandle
 *   );
 **/
VOID RtlDestroyHeapBefore(WINDOWS::PVOID  HeapHandle);
VOID RtlDestroyHeapAfter(WINDOWS::PVOID  HeapHandle); // ...


#endif // __MEM_WIN_H__
