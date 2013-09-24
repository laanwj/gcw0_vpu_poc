/*
 * User space API to jz_vpu driver.
 *
 * Copyright (C) 2006  Ingenic Semiconductor Inc.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 */

#ifndef __JZ_VPU_H
#define __JZ_VPU_H

#define TCSM_TOCTL_SET_MMAP		(0x99 + 0x1)
#define TCSM_TOCTL_WAIT_COMPLETE	(0x99 + 0x2)
#define TCSM_TOCTL_PREPARE_DIR		(0x99 + 0x10)
#define TCSM_TOCTL_PREPARE_BLOCK	(0x99 + 0x11)
#define TCSM_TOCTL_FLUSH_WORK		(0x99 + 0x12)

#endif

