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

#include "mem_posix.h"

extern FILE *outfile;

VOID mmapBefore(ADDRINT start, size_t length, int prot, int flags, int fd, off_t offset) {
#ifdef _DEBUG
    LOG("mmap\n");
    fprintf(outfile, "mmap(%p, %lu, %d, %d, %d, %lu) =\n", (void *)start, length, prot, flags, fd, offset);
#endif
}
VOID mmapAfter(ADDRINT ret) {
#ifdef _DEBUG
    fprintf(outfile, "  = %p\n", (void *)ret);
    LOG("mmap exit\n");
#endif
}
VOID munmapBefore(ADDRINT start, size_t length) {
#ifdef _DEBUG
    LOG("unmap\n");
    fprintf(outfile, "munmap(%p, %lu) =\n", (void *)start, length);
#endif
}
VOID munmapAfter(UINT32 ret) {
#ifdef _DEBUG
    fprintf(outfile, "  = %d\n", ret);
    LOG("unmap exit\n");
#endif
}
