p_start
	MOVE 40000, R7
	SUB SP, 4, R6
	CALL func0
	POP R6
	MOVE R5, R6
	HALT

funcmul
	LOAD r1, (r6+4)
	LOAD r0, (r6+8)
	CMP r0, 0
	JP_P mulpoz1
	XOR r2, 1, r2
mulpoz1
	CMP r1, 0
	JP_P mulpoz2
	XOR r2, 1, r2
mulpoz2
	ASHR R0, 31, R5
	ADD R0, R5, R0
	XOR R0, R5, R0
	ASHR R1, 31, R5
	ADD R1, R5, R1
	XOR R1, R5, R1
	MOVE 0, r5
	CMP r1, 0
	JP_Z loopmulend
loopmul
	ADD r5, r0, r5
	SUB r1, 1, r1
	CMP r1, 0
	JP_NZ loopmul
loopmulend
	CMP r2, 0
	JP_Z mulend
	MOVE -1, R0
	XOR r5, r0, r5
	ADD r5, 1, r5
mulend
	RET
funcdiv
	LOAD r1, (r6+4)
	LOAD r0, (r6+8)
	CMP r0, 0
	JP_P divpoz1
	XOR r2, 1, r2
divpoz1
	CMP r1, 0
	JP_P divpoz2
	XOR r2, 1, r2
divpoz2
	ASHR R0, 31, R5
	ADD R0, R5, R0
	XOR R0, R5, R0
	ASHR R1, 31, R5
	ADD R1, R5, R1
	XOR R1, R5, R1
	MOVE 0, r5
	CMP r1, 0
	JP_Z loopdivend
loopdiv
	SUB r0, r1, r0
	CMP r0, 0
	JP_N loopdivend
	ADD r5, 1, r5
	JP loopdiv
loopdivend
	CMP r2, 0
	JP_Z divend
	MOVE -1, R0
	XOR r5, r0, r5
	ADD r5, 1, r5
divend
	RET
funcmod
	LOAD r1, (r6+4)
	LOAD r0, (r6+8)
loopmod
	SUB r0, r1, r0
	CMP r0, 0
	JP_NN loopmod
	ADD r0, r1, r0
modend
	MOVE r0, r5
	RET
func0 	SUB SP, 04, SP
	MOVE 0a, R0
	PUSH R0
	POP R0
	STORE R0, (R6-04)
	MOVE 0a, R0
	PUSH R0
	MOVE 02, R0
	PUSH R0
	POP R0
	POP R1
	ADD R0, R1, R0
	PUSH R0
	POP R0
	MOVE 09, R0
	PUSH R0
	LOAD R0, (SP)
	STORE R0, (R6-04)
	POP R0
	LOAD R0, (R6-04)
	PUSH R0
	POP R5
	ADD SP, 04, SP
	RET
