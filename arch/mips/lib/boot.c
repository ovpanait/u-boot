// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2020 Stefan Roese <sr@denx.de>
 */

#include <common.h>
#include <command.h>
#include <cpu_func.h>

DECLARE_GLOBAL_DATA_PTR;

int arch_setup_bdinfo(void)
{
	bd_t *bd = gd->bd;

	/*
	 * Save local variables to board info struct
	 */
	bd->bi_memstart = CONFIG_SYS_SDRAM_BASE;	/* start of memory */
	bd->bi_memsize = gd->ram_size;			/* size in bytes */

	if (IS_ENABLED(CONFIG_SYS_HAS_SRAM)) {
		bd->bi_sramstart = CONFIG_SYS_SRAM_BASE;	/* start of SRAM */
		bd->bi_sramsize = CONFIG_SYS_SRAM_SIZE;		/* size  of SRAM */
	}

	return 0;
}

unsigned long do_go_exec(ulong (*entry)(int, char * const []),
			 int argc, char * const argv[])
{
	/*
	 * Flush cache before jumping to application. Let's flush the
	 * whole SDRAM area, since we don't know the size of the image
	 * that was loaded.
	 */
	flush_cache(gd->bd->bi_memstart, gd->ram_top - gd->bd->bi_memstart);

	return entry(argc, argv);
}
