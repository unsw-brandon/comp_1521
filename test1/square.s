main:
	li	$v0, 5		# scanf("%d", &x);
	syscall			#
	move	$t0, $v0
	
	move $t1, $zero
	
	blt $t1, $t0, loop_1
	
loop_1:
	move $t2, $zero
	
	blt $t2, $t0, loop_2
	
loop_1_cont:
	addi $t1, $t1, 1
	
	li	$a0, '\n'	# printf("%c", '\n');
	li	$v0, 11
	syscall	
	
	blt $t1, $t0, loop_1
	j end
	
loop_2:
	li	$a0, '*'	# printf("%c", '*');
	li	$v0, 11
	syscall	
	
	addi $t2, $t2, 1
	
	blt $t2, $t0, loop_2
	j loop_1_cont

end:	
	li	$v0, 0		# return 0
	jr	$ra
