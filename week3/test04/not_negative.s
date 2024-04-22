# Tested by [Brandon Chikandiwa (z5495844) on 13/03/2023]

# Reads numbers until a non-negative number is entered

main:
	# Registers:
	#   - $t0: int x

	li $t1, 1
	li $t2, 0
	bgt $t1, $t2, loop_1

loop_1:	
	li	$v0, 4			# syscall 4: print_string
	la	$a0, prompt_str		#
	syscall				# printf("Enter a number: ");

	li	$v0, 5			# syscall 5: read_int
	syscall				#
	move	$t0, $v0

	blt $t0, 0, out_1
	j out_2

loop_1_cont:
	bgt $t1, $t2, loop_1
	j end


out_1:	
	li	$v0, 4			# syscall 4: print_string
	la	$a0, wrong_str		
	syscall				# printf("Enter a positive number: ");

	j loop_1_cont


out_2:
	li	$v0, 4			# syscall 4: print_string
	la	$a0, result_str		#
	syscall				# printf("You entered: ");

	li	$v0, 1			# syscall 1: print_int
	move	$a0, $t0		#
	syscall				# printf("%d", x);

	li	$v0, 11			# syscall 11: print_char
	li	$a0, '\n'		#
	syscall				# printf("%c", '\n');
	
	j end

end:
	li	$v0, 0
	jr	$ra			# return 0;

########################################################################
# .DATA
# Add any strings here that you want to use in your program.
	.data
prompt_str:
	.asciiz "Enter a number: "
result_str:
	.asciiz "You entered: "
wrong_str:
	.asciiz "Enter a positive number\n"
