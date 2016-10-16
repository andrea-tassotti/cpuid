/*
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    Copyrights (c) 2016 Andrea Tassotti

*/

#include <stdint.h>
#include <stdio.h>

// Part from cpuid.c (Apple)
/*
 * Copyright (c) 2000-2006 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */
typedef enum { eax, ebx, ecx, edx } cpuid_register_t;
static inline void
cpuid(uint32_t *data)
{
	asm("cpuid"
		: "=a" (data[eax]),
		  "=b" (data[ebx]),
		  "=c" (data[ecx]),
		  "=d" (data[edx])
		: "a"  (data[eax]),
		  "b"  (data[ebx]),
		  "c"  (data[ecx]),
		  "d"  (data[edx]));
}
static inline void
do_cpuid(uint32_t selector, uint32_t *data)
{
	asm("cpuid"
		: "=a" (data[0]),
		  "=b" (data[1]),
		  "=c" (data[2]),
		  "=d" (data[3])
		: "a"(selector));
}
// End of part from cpuid.c



/*
 *	Main program
 */

int main(int argc, char * argv[])
{
	uint32_t	cpuid_reg[4];
	uint32_t	idx = 0, count;

	printf("Leaf no.  EAX      EBX      ECX      EDX\n");

// Basic
	do_cpuid(idx, cpuid_reg);
	printf("%08x  %08x %08x %08x %08x\n",
			idx, cpuid_reg[eax], cpuid_reg[ebx], cpuid_reg[ecx], cpuid_reg[edx]);

	count = cpuid_reg[eax];

	for(idx++;idx<=count;idx++)
	{
		do_cpuid(idx, cpuid_reg);
		printf("%08x  %08x %08x %08x %08x\n",
			idx, cpuid_reg[eax], cpuid_reg[ebx], cpuid_reg[ecx], cpuid_reg[edx]);
	}

// Extended
	idx = 0x80000000;
	do_cpuid(idx, cpuid_reg);
	printf("%08x  %08x %08x %08x %08x\n",
			idx, cpuid_reg[eax], cpuid_reg[ebx], cpuid_reg[ecx], cpuid_reg[edx]);

	count = cpuid_reg[eax];

	for(idx++;idx<=count;idx++)
	{
		do_cpuid(idx, cpuid_reg);
		printf("%08x  %08x %08x %08x %08x\n",
			idx, cpuid_reg[eax], cpuid_reg[ebx], cpuid_reg[ecx], cpuid_reg[edx]);
	}

}
