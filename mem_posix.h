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

#ifndef __MEM_POSIX_H__
#define __MEM_POSIX_H__

#include "pin.H"

/*  void *mmap(void *start, size_t length, int prot, int flags, int fd, off_t offset);
    int munmap(void *start, size_t length);
*/

VOID mmapBefore(ADDRINT start, size_t length, int prot, int flags, int fd, off_t offset);
VOID mmapAfter(ADDRINT ret);

VOID munmapBefore(ADDRINT start, size_t length);
VOID munmapAfter(UINT32 ret);

#endif // __MEM_POSIX_H__
