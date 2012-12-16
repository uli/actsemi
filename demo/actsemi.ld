ENTRY(_init_proc)

SECTIONS
{
	. = 0x51400000;
	/* . = 0x52000000; */
	.init : { *(.init) }
	.text :	{ *(.text) }
	.fini : { *(.fini) }
	. = ALIGN(4);
	.dlsym : { *(.dlsym) }
	.dlstr : { *(.dlstr) }
	. = ALIGN(0x20000);
	.ctors : { *(.ctors) }
	.dtors : { *(.dtors) }
	. = ALIGN(4);
	.data : { *(.data); *(.sdata); *(.rodata*) }
	. = ALIGN(4);
	.sbss : { KEEP(*(.sbss)); *(.scommon) }
	. = ALIGN(4);
	/* _bss_start = .; */
	.bss  : { KEEP(*(.bss))  }
	/* _bss_end = .; */
	end = .; _end = .; __end = .;
}
