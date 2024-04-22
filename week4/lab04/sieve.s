# Sieve of Eratosthenes
# https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
# Tested by [Brandon Chikandiwa (z5495844) on 10/03/2023]

# Constants
ARRAY_LEN = 1000

main:

	li	$v0, 0
	li	$t0, 2

loop_2_cond:
	bge	$t0, ARRAY_LEN, loop_2_end
	b loop_2_body

loop_2_body:
	lb	$t3, prime($t0)
	beq	$t3, 0, loop_2_increment

	move $a0, $t0
	li	$v0, 1
	syscall

	li	$a0, '\n'
	li	$v0, 11
	syscall

loop_1_init:
	li	$t1, 2
	mul	$t1, $t1, $t0
	j loop_1_cond

loop_1_cond:
	bge	$t1, ARRAY_LEN, loop_1_end
	j loop_1_body

loop_1_body:
	li	$t2, 0
	sb	$t2, prime($t1)
	j loop_1_increment

loop_1_increment:
	add $t1, $t1, $t0
	j loop_1_cond

loop_1_end:
	j loop_2_increment

loop_2_increment:
	addi $t0, $t0, 1
	j loop_2_cond

loop_2_end:
	j end


end:
	jr	$ra			# return 0;

	.data
prime:
	.byte	1:ARRAY_LEN		# uint8_t prime[ARRAY_LEN] = {1, 1, ...};