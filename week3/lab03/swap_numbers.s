# Tested by [Brandon Chikandiwa (z5495844) on 2/03/2023]

# Constants
ARRAY_LEN = 10

main:
	# Registers:
	#  - $t0: int i
	#  - $t1: temporary result
	#  - $t2: temporary result
	#  - $t6: i - 1
	#  - $t4: int x
	#  - $t5: int y


scan_loop__init:
	li	$t0, 0				# i = 0;
scan_loop__cond:
	bge	$t0, ARRAY_LEN, scan_loop__end	# while (i < ARRAY_LEN) {

scan_loop__body:
	li	$v0, 5				#   syscall 5: read_int
	syscall					#   
						#
	mul	$t1, $t0, 4			#   calculate &numbers[i] == numbers + 4 * i
	la	$t2, numbers			#
	add	$t2, $t2, $t1			#
	sw	$v0, ($t2)			#   scanf("%d", &numbers[i]);

	addi	$t0, $t0, 1			#   i++;
	j	scan_loop__cond			# }
scan_loop__end:

	li $t0, 1
	li $t6, 0
	
	blt $t0, ARRAY_LEN, loop_2
	
	
	
loop_2:

	mul	$t1, $t0, 4			
	la	$t2, numbers			
	add	$t2, $t2, $t1			
	lw	$t4, ($t2)
	
	mul	$t1, $t6, 4			
	la	$t2, numbers			
	add	$t2, $t2, $t1			
	lw	$t5, ($t2)
	
	blt $t4, $t5, process
	j loop_2_next

process: 
	
	sw 	$t4, ($t2)
	
	mul	$t1, $t0, 4
	la	$t2, numbers
	add	$t2, $t2, $t1
	sw 	$t5, ($t2)
	j loop_2_next
		
loop_2_next:
	add $t0, $t0, 1
	add $t6, $t6, 1
	blt $t0, ARRAY_LEN, loop_2
		
print_loop__init:
	li	$t0, 0				# i = 0
print_loop__cond:
	bge	$t0, ARRAY_LEN, print_loop__end	# while (i < ARRAY_LEN) {

print_loop__body:
	mul	$t1, $t0, 4			#   calculate &numbers[i] == numbers + 4 * i
	la	$t2, numbers			#
	add	$t2, $t2, $t1			#
	lw	$a0, ($t2)			#
	li	$v0, 1				#   syscall 1: print_int
	syscall					#   printf("%d", numbers[i]);

	li	$v0, 11				#   syscall 11: print_char
	li	$a0, '\n'
	syscall					#   printf("%c", '\n');

	addi	$t0, $t0, 1			#   i++
	b	print_loop__cond		# }
print_loop__end:
	li $v0, 10
	li $a0, 0
	syscall			# return 0;

	.data
	
prompt: .asciiz "----------------"
numbers:
	.word	0:ARRAY_LEN			# int numbers[ARRAY_LEN] = {0};
