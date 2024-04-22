# Tested by [Brandon Chikandiwa (z5495844) on 21/02/2023]

.data
	out: 
		.asciiz "Well, this was a MIPStake!\n"

.text
	.globl main

main:
	la $a0, out
	li $v0, 4
	syscall

	li $v0, 10
	li $a0, 0
	syscall
	
