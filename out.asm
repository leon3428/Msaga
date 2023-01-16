program_start 	lui sp, %hi(262144)
	addi sp,sp %lo(262144)
	sw fp, -4(sp)
	addi fp, sp, -4
	addi sp, sp, -8
	jal ra, function_0
	addi sp, fp, 8
	lw fp, 4(fp)
	addi x6, a0, 0
	HALT

function_0 sw ra, 0(fp)
	lw t0, 0(sp)
	slli t0, t0, 2
	addi t1, x0, 0
	add t1, t1, t0
	lw t0, 0(t1)
	sw t0, 0(sp)
	lw t0, 0(sp)
	slli t0, t0, 2
	addi t1, x0, 0
	add t1, t1, t0
	lw t0, 0(t1)
	sw t0, 0(sp)
	lw a0, 0(sp)
	addi sp, sp, 4
	jalr x0, 0(ra)
