# Tested by [Brandon Chikandiwa (z5495844) on 26/02/2023]

main:				# int main(void)
	la	$a0, prompt1	# printf("Enter the starting number: ");
	li	$v0, 4
	syscall

	li	$v0, 5		
	syscall
	move $t0, $v0		# load start into $t0
	
	la	$a0, prompt2	
	li	$v0, 4
	syscall

	li	$v0, 5		
	syscall
	move $t1, $v0		# load stop into $t1
	
	la	$a0, prompt3	
	li	$v0, 4
	syscall

	li	$v0, 5		
	syscall
	move $t2, $v0		# load step into $t2
	
	j start

start:
	blt $t1, $t0, step_1
	bgt $t1, $t0, step_2
	j end 
	
step_1:
	blt $t2, 0, loop_1
	j end

step_2:
	bgt $t2, 0, loop_2
	j end

loop_1:
	move	$a0, $t0	
	li	$v0, 1
	syscall
	
	li	$a0, '\n'	
	li	$v0, 11
	syscall
	
	add $t0, $t0, $t2
	
	bge $t0, $t1, loop_1
	j end
	
loop_2:
	move	$a0, $t0	
	li	$v0, 1
	syscall
	
	li	$a0, '\n'	
	li	$v0, 11
	syscall
	
	add $t0, $t0, $t2
	
	ble $t0, $t1, loop_2
	j end
	
end:
	li $v0, 10
	li $a0, 0
	syscall

	.data
prompt1:
	.asciiz "Enter the starting number: "
prompt2:
	.asciiz "Enter the stopping number: "
prompt3:
	.asciiz "Enter the step size: "
