  # labwork.S
  # Written 2015-2017 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1.
  # The macros PUSH and POP are in the public domain.
  # Please add your own code at the end of the file.

  #
  # Please keep the two macros PUSH and POP unchanged
  #
.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm
  #
  # Please add your own code below this line
  #

.global 
 hexasc: 
	andi $a0, $a0, 0xf 
	
	li $t0, 9
	
	ble $a0, $t0, asc 
	
	addi $v0, $a0, 0x37 
	
	jr $ra
	
asc:
	addi $v0, $a0, 0x30 
	
	jr $ra
	
.global delay
delay:
	li $t3, 0 # int i
	li $t4, 4000 #Constant 4711, can be changed	
	nop

loop:
	ble $a0,$0, ending
	nop
	sub $a0,$a0,1
	li $t3, 0
	
forloop:
	ble $t4, $t3, loop
	nop
	addi $t3, $t3, 1
	j forloop
	nop
ending:
	jr $ra
	nop

.global time2string
time2string:
	
	PUSH $s0
	PUSH $s1
	PUSH $ra
	
	move $s0, $a0 
	move $s1, $a1 


	andi $t1, $s1, 0xf000 #take the first digit
	srl  $a0, $t1, 0x0c # shift it 12 steps
	jal hexasc
	nop
	sb $v0, 0($s0)	

	
	andi $t1, $s1,0x0f00
	srl  $a0, $t1, 0x8 #shift 8 steps
	jal hexasc
	nop
	sb $v0, 1($s0)

	li $t1, 0x3A
	sb $t1, 2($s0)

	
	andi $t1, $s1, 0x00f0 
	srl $a0, $t1, 0x4
	jal hexasc
	nop
	sb $v0, 3($s0)

	
	andi $t1, $s1, 0x000f 
	srl $a0, $t1, 0x0
	jal hexasc
	nop
	sb $v0, 4($s0) 


	li $t1, 0x00 
	sb $t1, 5($s0)
	
	POP $ra
	POP $s1
	POP $s0 
	
	jr $ra
	nop

