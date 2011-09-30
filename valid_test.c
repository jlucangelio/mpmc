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

#include <stdlib.h>

int main(int argc, char **argv) {
	int i, a;
	int *t;
	for (i = 0; i < atoi(argv[1]); i++) {
		t = (int *)malloc(sizeof(int));
		*t = 0;
		a = *t;
		free(t);
	}
	return 0;
}
