// SPDX-License-Identifier: GPL-2.0+
/*
 * PPC-specific information for the 'bd' command
 *
 * (C) Copyright 2003
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 */

#include <common.h>
#include <init.h>

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
		bd->bi_sramstart = CONFIG_SYS_SRAM_BASE; /* start of SRAM */
		bd->bi_sramsize = CONFIG_SYS_SRAM_SIZE;  /* size  of SRAM */
	}

#if defined(CONFIG_E500) || defined(CONFIG_MPC86xx)
	bd->bi_immr_base = CONFIG_SYS_IMMR;	/* base  of IMMR register     */
#endif

#if defined(CONFIG_MPC83xx)
	bd->bi_immrbar = CONFIG_SYS_IMMR;
#endif

	bd->bi_intfreq = gd->cpu_clk;	/* Internal Freq, in Hz */
	bd->bi_busfreq = gd->bus_clk;	/* Bus Freq,      in Hz */

#if defined(CONFIG_CPM2)
	bd->bi_cpmfreq = gd->arch.cpm_clk;
	bd->bi_brgfreq = gd->arch.brg_clk;
	bd->bi_sccfreq = gd->arch.scc_clk;
	bd->bi_vco = gd->arch.vco_out;
#endif /* CONFIG_CPM2 */

#if defined(CONFIG_EXTRA_CLOCK)
	bd->bi_inpfreq = gd->arch.inp_clk;	/* input Freq in Hz */
	bd->bi_vcofreq = gd->arch.vco_clk;	/* vco Freq in Hz */
	bd->bi_flbfreq = gd->arch.flb_clk;	/* flexbus Freq in Hz */
#endif

	return 0;
}

void __weak board_detail(void)
{
	/* Please define board_detail() for your PPC platform */
}

void arch_print_bdinfo(void)
{
	bd_t *bd = gd->bd;

#if defined(CONFIG_SYS_INIT_RAM_ADDR)
	bdinfo_print_num("sramstart", (ulong)bd->bi_sramstart);
	bdinfo_print_num("sramsize", (ulong)bd->bi_sramsize);
#endif
	bdinfo_print_mhz("busfreq", bd->bi_busfreq);
#if defined(CONFIG_MPC8xx) || defined(CONFIG_E500)
	bdinfo_print_num("immr_base", bd->bi_immr_base);
#endif
	bdinfo_print_num("bootflags", bd->bi_bootflags);
	bdinfo_print_mhz("intfreq", bd->bi_intfreq);
#ifdef CONFIG_ENABLE_36BIT_PHYS
	if (IS_ENABLED(CONFIG_PHYS_64BIT))
		puts("addressing  = 36-bit\n");
	else
		puts("addressing  = 32-bit\n");
#endif
	board_detail();
#if defined(CONFIG_CPM2)
	bdinfo_print_mhz("cpmfreq", bd->bi_cpmfreq);
	bdinfo_print_mhz("vco", bd->bi_vco);
	bdinfo_print_mhz("sccfreq", bd->bi_sccfreq);
	bdinfo_print_mhz("brgfreq", bd->bi_brgfreq);
#endif
}
