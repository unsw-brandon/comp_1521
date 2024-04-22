# Tested by [Brandon Chikandiwa (z5495844) on 26/02/2023]

.text
main:				

	la	$a0, prompt	# printf("Enter a number: ");
	li	$v0, 4
	syscall

	li	$v0, 5		# scanf("%d", number);
	syscall
	
	move $t0, $v0		# initialise $t0 as number input
	li $t1, 1		# initialise $t1 as 1
	
	bgt 0, $t0, end
	j start
	
start:	
	div $t1, 11
	mfhi $t2
	
	div $t1, 7
	mfhi $t3
	
	move $t4, $t1
	add $t1, $t1, 1
	
	beq $t2, 0, out
	beq $t3, 0, out
	
	j loop
	
loop:
	blt $t1, $t0, start
	j end

out:	
	
	move	$a0, $t4	# printf("%d", i);
	li	$v0, 1
	syscall

	li	$a0, '\n'	# printf("%c", '\n');
	li	$v0, 11
	syscall
	
	blt $t1, $t0, loop
	j end

end:
	li $v0, 10
	li $a0, 0
	syscall

.data
prompt:
	.asciiz "Enter a number: "
