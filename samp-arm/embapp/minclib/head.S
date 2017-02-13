/*
 *  head.S
 *
 *  Copyright (C) 2001-2002 Hayden Luo
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 *  32-bit startup code for s3c5410b board
 */

#include "board.h"

.section ".text"
.global   start
start:
 
	ldr	sp, =0x200000
	bl	app_main
	swi


