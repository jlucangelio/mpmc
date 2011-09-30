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

#ifndef __MEM_LIBC_H__
#define __MEM_LIBC_H__

#include "pin.H"

VOID mallocBefore(ADDRINT size);
VOID mallocAfter(ADDRINT address);

VOID freeBefore(ADDRINT addr);
VOID freeAfter(ADDRINT ret);

#endif // __MEM_LIBC_H__
