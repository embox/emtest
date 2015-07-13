
SECTIONS {
	.rodata.array_spread : {
		*(SORT(.array_spread.*.rodata))
	}
}
INSERT AFTER .rodata;

