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

#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <intsafe.h>

int main(int argc, char *argv[]) {
    HANDLE hDefaultProcessHeap;
    int i, n, a;
    int *t;

    //
    // Get a handle to the default process heap.
    //
    hDefaultProcessHeap = GetProcessHeap();
    if (hDefaultProcessHeap == NULL) {
        printf("Failed to retrieve the default process heap with LastError %d.\n", GetLastError());
        return 1;
    }

    printf("handle 0x%x\n", hDefaultProcessHeap);

    n = atoi(argv[1]);

    for (i = 0; i < n; i++) {
        t = (int *)HeapAlloc(hDefaultProcessHeap, 0, sizeof(int));
        //printf("allocated %d\n", sizeof(int));
        a = *t;
    }

    return 0;
}
