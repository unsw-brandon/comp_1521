# Reads a line and prints whether it is a palindrome or not

LINE_LEN = 256

########################################################################
# .TEXT <main>
main:
	# Locals:
	#   - ...

	li	$v0, 4				# syscall 4: print_string
	la	$a0, line_prompt_str		#
	syscall					# printf("Enter a line of input: ");

	li	$v0, 8				# syscall 8: read_string
	la	$a0, line			#
	la	$a1, LINE_LEN			#
	syscall					# fgets(buffer, LINE_LEN, stdin)

	li $t0, 0 # i = 0
	lb $t1, line($t0) # line[i]

	bnez $t1, loop_1
	j main_cont

loop_1:	
	add $t0, 1
	lb $t1, line($t0)
	bnez $t1, loop_1
	j main_cont

main_cont:
	li $t2, 0 # j = 0
	move $t4, $t0 # k = i
	addi $t4, -2 # k -= 2

	blt $t2, $t4, loop_2
	j end_pal

loop_2:
	lb $t3, line($t2) # line[j]
	lb $t5, line($t4) # line[k]
	bne $t3, $t5, end_not_pal

	add $t2, 1
	add $t4, -1
	blt $t2, $t4, loop_2
	j end_pal

end_not_pal:
	li	$v0, 4				# syscall 4: print_string
	la	$a0, result_not_palindrome_str	#
	syscall					# printf("not palindrome\n");

	j end

end_pal:
	li	$v0, 4				# syscall 4: print_string
	la	$a0, result_palindrome_str	#
	syscall					# printf("palindrome\n");	

	j end

end:
	li	$v0, 0
	jr	$ra				# return 0;


########################################################################
# .DATA
	.data
# String literals
line_prompt_str:
	.asciiz	"Enter a line of input: "
result_not_palindrome_str:
	.asciiz	"not palindrome\n"
result_palindrome_str:
	.asciiz	"palindrome\n"

# Line of input stored here
line:
	.space	LINE_LEN

