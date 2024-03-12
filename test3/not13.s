main:
	li	$v0, 5		# scanf("%d", &x);
	syscall			#
	move	$t0, $v0

	li	$v0, 5		# scanf("%d", &y);
	syscall			#
	move	$t1, $v0
	
	move $t2, $t0
	addi $t2, $t2, 1
	
	blt $t2, $t1, loop
	j end

loop: 
	bne $t2, 13, out

loop_cont:
	addi $t2, $t2, 1
	blt $t2, $t1, loop
	j end

out:
	move	$a0, $t2		# printf("%d\n", i);
	li	$v0, 1
	syscall	

	li	$a0, '\n'	# printf("%c", '\n');
	li	$v0, 11
	syscall	
	
	j loop_cont

end:
	li	$v0, 0         # return 0
	jr	$ra
