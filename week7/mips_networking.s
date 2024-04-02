# Reads a 4-byte value and reverses the byte order, then prints it
.data
BYTE_MASK = 0xFF

########################################################################
# .TEXT <main>
.text
main:
	# Locals:
	#	- $t0: int network_bytes
	#	- $t1: int computer_bytes
	#	- Add your registers here!


	li	$v0, 5		# scanf("%d", &x);
	syscall
	#
	# Your code here!
	#
	
	move    $t0, $v0

	li		$t1, 0
	and $t2, $t0, BYTE_MASK
	sll $t2, $t2, 24

	sll $t3, BYTE_MASK, 8
	and $t3, $t0, $t3
	sll $t3, $t3, 8

	sll $t4, BYTE_MASK, 16
	and $t4, $t0, $t4
	srl $t4, $t4, 8

	sll $t5, BYTE_MASK, 24
	and $t5, $t0, $t5
	srl $t5, $t5, 24

	or 	$t1, 0, $t2;
	or $t1, $t1, $t3;
	or $t1, $t1, $t4;
	or $t1, $t1, $t5;
	move	$v0, $t1
	move	$a0, $v0	# printf("%d\n", x);
	li	$v0, 1
	syscall

	li	$a0, '\n'	# printf("%c", '\n');
	li	$v0, 11
	syscall

main__end:
	li	$v0, 0		# return 0;
	jr	$ra
