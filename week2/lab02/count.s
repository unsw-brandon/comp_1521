################################################################################
# COMP1521 24T1 -- Assignment 1 -- Railroad Runners!
#
#
# !!! IMPORTANT !!!
# Before starting work on the assignment, make sure you set your tab-width to 8!
# It is also suggested to indent with tabs only.
# Instructions to configure your text editor can be found here:
#   https://cgi.cse.unsw.edu.au/~cs1521/24T1/resources/mips-editors.html
# !!! IMPORTANT !!!
#
#
# This program was written by YOUR-NAME-HERE (z5555555)
# on INSERT-DATE-HERE
#
# Version 1.0 (2024-02-27): Team COMP1521 <cs1521@cse.unsw.edu.au>
#
################################################################################

#![tabsize(8)]

# ------------------------------------------------------------------------------
#                                   Constants
# ------------------------------------------------------------------------------

# -------------------------------- C Constants ---------------------------------
TRUE = 1
FALSE = 0

JUMP_KEY = 'w'
LEFT_KEY = 'a'
CROUCH_KEY = 's'
RIGHT_KEY = 'd'
TICK_KEY = '\''
QUIT_KEY = 'q'

ACTION_DURATION = 3
CHUNK_DURATION = 10

SCROLL_SCORE_BONUS = 1
TRAIN_SCORE_BONUS = 1
BARRIER_SCORE_BONUS = 2
CASH_SCORE_BONUS = 3

MAP_HEIGHT = 20
MAP_WIDTH = 5
PLAYER_ROW = 1

PLAYER_RUNNING = 0
PLAYER_CROUCHING = 1
PLAYER_JUMPING = 2

STARTING_COLUMN = MAP_WIDTH / 2

TRAIN_CHAR = 't'
BARRIER_CHAR = 'b'
CASH_CHAR = 'c'
EMPTY_CHAR = ' '
WALL_CHAR = 'w'
RAIL_EDGE = '|'

SAFE_CHUNK_INDEX = 0
NUM_CHUNKS = 14

# --------------------- Useful Offset and Size Constants -----------------------

# struct BlockSpawner offsets
BLOCK_SPAWNER_NEXT_BLOCK_OFFSET = 0
BLOCK_SPAWNER_SAFE_COLUMN_OFFSET = 20
BLOCK_SPAWNER_SIZE = 24

# struct Player offsets
PLAYER_COLUMN_OFFSET = 0
PLAYER_STATE_OFFSET = 4
PLAYER_ACTION_TICKS_LEFT_OFFSET = 8
PLAYER_ON_TRAIN_OFFSET = 12
PLAYER_SCORE_OFFSET = 16
PLAYER_SIZE = 20

SIZEOF_PTR = 4


# ------------------------------------------------------------------------------
#                                 Data Segment
# ------------------------------------------------------------------------------
	.data

# !!! DO NOT ADD, REMOVE, OR MODIFY ANY OF THESE DEFINITIONS !!!

# ----------------------------- String Constants -------------------------------

print_welcome__msg_1:
	.asciiz "Welcome to Railroad Runners!\n"
print_welcome__msg_2_1:
	.asciiz "Use the following keys to control your character: ("
print_welcome__msg_2_2:
	.asciiz "):\n"
print_welcome__msg_3:
	.asciiz ": Move left\n"
print_welcome__msg_4:
	.asciiz ": Move right\n"
print_welcome__msg_5_1:
	.asciiz ": Crouch ("
print_welcome__msg_5_2:
	.asciiz ")\n"
print_welcome__msg_6_1:
	.asciiz ": Jump ("
print_welcome__msg_6_2:
	.asciiz ")\n"
print_welcome__msg_7_1:
	.asciiz "or press "
print_welcome__msg_7_2:
	.asciiz " to continue moving forward.\n"
print_welcome__msg_8_1:
	.asciiz "You must crouch under barriers ("
print_welcome__msg_8_2:
	.asciiz ")\n"
print_welcome__msg_9_1:
	.asciiz "and jump over trains ("
print_welcome__msg_9_2:
	.asciiz ").\n"
print_welcome__msg_10_1:
	.asciiz "You should avoid walls ("
print_welcome__msg_10_2:
	.asciiz ") and collect cash ("
print_welcome__msg_10_3:
	.asciiz ").\n"
print_welcome__msg_11:
	.asciiz "On top of collecting cash, running on trains and going under barriers will get you extra points.\n"
print_welcome__msg_12_1:
	.asciiz "When you've had enough, press "
print_welcome__msg_12_2:
	.asciiz " to quit. Have fun!\n"

get_command__invalid_input_msg:
	.asciiz "Invalid input!\n"

main__game_over_msg:
	.asciiz "Game over, thanks for playing 😊!\n"

display_game__score_msg:
	.asciiz "Score: "

handle_collision__barrier_msg:
	.asciiz "💥 You ran into a barrier! 😵\n"
handle_collision__train_msg:
	.asciiz "💥 You ran into a train! 😵\n"
handle_collision__wall_msg:
	.asciiz "💥 You ran into a wall! 😵\n"

maybe_pick_new_chunk__column_msg_1:
	.asciiz "Column "
maybe_pick_new_chunk__column_msg_2:
	.asciiz ": "
maybe_pick_new_chunk__safe_msg:
	.asciiz "New safe column: "

get_seed__prompt_msg:
	.asciiz "Enter a non-zero number for the seed: "
get_seed__prompt_invalid_msg:
	.asciiz "Invalid seed!\n"
get_seed__set_msg:
	.asciiz "Seed set to "

TRAIN_SPRITE:
	.asciiz "🚆"
BARRIER_SPRITE:
	.asciiz "🚧"
CASH_SPRITE:
	.asciiz "💵"
EMPTY_SPRITE:
	.asciiz "  "
WALL_SPRITE:
	.asciiz "🧱"

PLAYER_RUNNING_SPRITE:
	.asciiz "🏃"
PLAYER_CROUCHING_SPRITE:
	.asciiz "🧎"
PLAYER_JUMPING_SPRITE:
	.asciiz "🤸"

# ------------------------------- Chunk Layouts --------------------------------

SAFE_CHUNK: # char[]
	.byte EMPTY_CHAR, EMPTY_CHAR, EMPTY_CHAR, EMPTY_CHAR, EMPTY_CHAR, EMPTY_CHAR, EMPTY_CHAR, EMPTY_CHAR, EMPTY_CHAR, EMPTY_CHAR, '\0',
CHUNK_1: # char[]
	.byte EMPTY_CHAR, CASH_CHAR, EMPTY_CHAR, WALL_CHAR, CASH_CHAR, CASH_CHAR, CASH_CHAR, BARRIER_CHAR, '\0',
CHUNK_2: # char[]
	.byte CASH_CHAR, EMPTY_CHAR, EMPTY_CHAR, EMPTY_CHAR, BARRIER_CHAR, EMPTY_CHAR, EMPTY_CHAR, EMPTY_CHAR, CASH_CHAR, '\0',
CHUNK_3: # char[]
	.byte EMPTY_CHAR, EMPTY_CHAR, EMPTY_CHAR, TRAIN_CHAR, TRAIN_CHAR, TRAIN_CHAR, TRAIN_CHAR, TRAIN_CHAR, TRAIN_CHAR, TRAIN_CHAR, '\0',
CHUNK_4: # char[]
	.byte EMPTY_CHAR, EMPTY_CHAR, EMPTY_CHAR, TRAIN_CHAR, TRAIN_CHAR, TRAIN_CHAR, TRAIN_CHAR, EMPTY_CHAR, CASH_CHAR, '\0',
CHUNK_5: # char[]
	.byte EMPTY_CHAR, EMPTY_CHAR, CASH_CHAR, TRAIN_CHAR, TRAIN_CHAR, TRAIN_CHAR, EMPTY_CHAR, TRAIN_CHAR, EMPTY_CHAR, EMPTY_CHAR, '\0',
CHUNK_6: # char[]
	.byte EMPTY_CHAR, EMPTY_CHAR, CASH_CHAR, BARRIER_CHAR, EMPTY_CHAR, EMPTY_CHAR, CASH_CHAR, CASH_CHAR, EMPTY_CHAR, BARRIER_CHAR, '\0'
CHUNK_7: # char[]
	.byte EMPTY_CHAR, EMPTY_CHAR, EMPTY_CHAR, WALL_CHAR, WALL_CHAR, WALL_CHAR, WALL_CHAR, WALL_CHAR, WALL_CHAR, WALL_CHAR, '\0',
CHUNK_8: # char[]
	.byte CASH_CHAR, EMPTY_CHAR, CASH_CHAR, EMPTY_CHAR, CASH_CHAR, EMPTY_CHAR, CASH_CHAR, EMPTY_CHAR, CASH_CHAR, EMPTY_CHAR, '\0',
CHUNK_9: # char[]
	.byte CASH_CHAR, EMPTY_CHAR, EMPTY_CHAR, WALL_CHAR, TRAIN_CHAR, TRAIN_CHAR, TRAIN_CHAR, TRAIN_CHAR, TRAIN_CHAR, '\0',
CHUNK_10: # char[]
	.byte CASH_CHAR, CASH_CHAR, CASH_CHAR, CASH_CHAR, CASH_CHAR, CASH_CHAR, CASH_CHAR, CASH_CHAR, CASH_CHAR, CASH_CHAR, '\0',
CHUNK_11: # char[]
	.byte EMPTY_CHAR, EMPTY_CHAR, CASH_CHAR, WALL_CHAR, TRAIN_CHAR, TRAIN_CHAR, TRAIN_CHAR, TRAIN_CHAR, '\0',
CHUNK_12: # char[]
	.byte EMPTY_CHAR, EMPTY_CHAR, CASH_CHAR, '\0',
CHUNK_13: # char[]
	.byte EMPTY_CHAR, EMPTY_CHAR, EMPTY_CHAR, WALL_CHAR, WALL_CHAR, '\0',

CHUNKS:	# char*[]
	.word SAFE_CHUNK, CHUNK_1, CHUNK_2, CHUNK_3, CHUNK_4, CHUNK_5, CHUNK_6, CHUNK_7, CHUNK_8, CHUNK_9, CHUNK_10, CHUNK_11, CHUNK_12, CHUNK_13

# ----------------------------- Global Variables -------------------------------

g_block_spawner: # struct BlockSpawner
	# char *next_block[MAP_WIDTH], offset 0
	.word 0, 0, 0, 0, 0
	# int safe_column, offset 20
	.word STARTING_COLUMN

g_map: # char[MAP_HEIGHT][MAP_WIDTH]
	.space MAP_HEIGHT * MAP_WIDTH

g_player: # struct Player
	# int column, offset 0
	.word STARTING_COLUMN
	# int state, offset 4
	.word PLAYER_RUNNING
	# int action_ticks_left, offset 8
	.word 0
	# int on_train, offset 12
	.word FALSE
	# int score, offset 16
	.word 0

g_rng_state: # unsigned
	.word 1

# !!! Reminder to not not add to or modify any of the above !!!
# !!! strings or any other part of the data segment.        !!!

# ------------------------------------------------------------------------------
#                                 Text Segment
# ------------------------------------------------------------------------------
	.text

############################################################
####                                                    ####
####   Your journey begins here, intrepid adventurer!   ####
####                                                    ####
############################################################

################################################################################
#
# Implement the following functions,
# and check these boxes as you finish implementing each function.
#
#  SUBSET 0
#  - [ ] print_welcome
#  SUBSET 1
#  - [ ] get_command
#  - [ ] main
#  - [ ] init_map
#  SUBSET 2
#  - [ ] run_game
#  - [ ] display_game
#  - [ ] maybe_print_player
#  - [ ] handle_command
#  SUBSET 3
#  - [ ] handle_collision
#  - [ ] maybe_pick_new_chunk
#  - [ ] do_tick
#  PROVIDED
#  - [X] get_seed
#  - [X] rng
#  - [X] read_char
################################################################################

################################################################################
# .TEXT <print_welcome>
print_welcome:
	# Subset:   0
	#
	# Args:     None
	#
	# Returns:  None
	#
	# Frame:    [...]
	# Uses:     [...]
	# Clobbers: [...]
	#
	# Locals:
	#   - ...
	#
	# Structure:
	#   print_welcome
	#   -> [prologue]
	#     -> body
	#   -> [epilogue]

print_welcome__prologue:
print_welcome__body:
	la $a0, print_welcome__msg_1
	li $v0, 1
	syscall
	
	la $a0, print_welcome__msg_2_1
	syscall
	
	la $a0, print_welcome__msg_2_2
	syscall
	
	la $a0, print_welcome__msg_10_3
	syscall
	
	la $a0, print_welcome__msg_4
	syscall
	
	la $a0, print_welcome__msg_5_1
	syscall
	
	la $a0, print_welcome__msg_5_2
	syscall
	
	la $a0, print_welcome__msg_6_1
	syscall
	
	la $a0, print_welcome__msg_6_2
	syscall
	
	la $a0, print_welcome__msg_7_1
	syscall
	
	la $a0, print_welcome__msg_7_2
	syscall
	
	la $a0, print_welcome__msg_8_1
	syscall
	
	la $a0, print_welcome__msg_8_2
	syscall
	
	la $a0, print_welcome__msg_9_1
	syscall
	
	la $a0, print_welcome__msg_9_2
	syscall
	
	la $a0, print_welcome__msg_10_1
	syscall
	
	la $a0, print_welcome__msg_10_2
	syscall
	
	la $a0, print_welcome__msg_10_3
	syscall
	
	la $a0, print_welcome__msg_11
	syscall
	
	la $a0, print_welcome__msg_12_1
	syscall
	
	la $a0, print_welcome__msg_12_2
	syscall

print_welcome__epilogue:
	jr	$ra


################################################################################
# .TEXT <get_command>
	.text
get_command:
	# Subset:   1
	#
	# Args:     None
	#
	# Returns:  $v0: char
	#
	# Frame:    [...]
	# Uses:     [...]
	# Clobbers: [...]
	#
	# Locals:
	#   - ...
	#
	# Structure:
	#   get_command
	#   -> [prologue]
	#     -> body
	#   -> [epilogue]

get_command__prologue:
get_command__body:
get_command__epilogue:
	jr	$ra


################################################################################
# .TEXT <main>
	.text
main:
	# Subset:   1
	#
	# Args:     None
	#
	# Returns:  $v0: int
	#
	# Frame:    [...]
	# Uses:     [...]
	# Clobbers: [...]
	#
	# Locals:
	#   - ...
	#
	# Structure:
	#   main
	#   -> [prologue]
	#     -> body
	#   -> [epilogue]

main__prologue:
main__body:
main__epilogue:
	jr	$ra


################################################################################
# .TEXT <init_map>
	.text
init_map:
	# Subset:   1
	#
	# Args:
	#   - $a0: char map[MAP_HEIGHT][MAP_WIDTH]
	#
	# Returns:  None
	#
	# Frame:    [...]
	# Uses:     [...]
	# Clobbers: [...]
	#
	# Locals:
	#   - ...
	#
	# Structure:
	#   init_map
	#   -> [prologue]
	#     -> body
	#   -> [epilogue]

init_map__prologue:
init_map__body:
init_map__epilogue:
	jr	$ra


################################################################################
# .TEXT <run_game>
	.text
run_game:
	# Subset:   2
	#
	# Args:
	#   - $a0: char map[MAP_HEIGHT][MAP_WIDTH]
	#   - $a1: struct Player *player
	#   - $a2: struct BlockSpawner *block_spawner
	#   - $a3: char input
	#
	# Returns:  $v0: int
	#
	# Frame:    [...]
	# Uses:     [...]
	# Clobbers: [...]
	#
	# Locals:
	#   - ...
	#
	# Structure:
	#   run_game
	#   -> [prologue]
	#     -> body
	#   -> [epilogue]

run_game__prologue:
run_game__body:
run_game__epilogue:
	jr	$ra


################################################################################
# .TEXT <display_game>
	.text
display_game:
	# Subset:   2
	#
	# Args:
	#   - $a0: char map[MAP_HEIGHT][MAP_WIDTH]
	#   - $a1: struct Player *player
	#
	# Returns:  None
	#
	# Frame:    [...]
	# Uses:     [...]
	# Clobbers: [...]
	#
	# Locals:
	#   - ...
	#
	# Structure:
	#   display_game
	#   -> [prologue]
	#     -> body
	#   -> [epilogue]

display_game__prologue:
display_game__body:
display_game__epilogue:
	jr	$ra


################################################################################
# .TEXT <maybe_print_player>
	.text
maybe_print_player:
	# Subset:   2
	#
	# Args:
	#   - $a0: struct Player *player
	#   - $a1: int row
	#   - $a2: int column
	#
	# Returns:  $v0: int
	#
	# Frame:    [...]
	# Uses:     [...]
	# Clobbers: [...]
	#
	# Locals:
	#   - ...
	#
	# Structure:
	#   maybe_print_player
	#   -> [prologue]
	#     -> body
	#   -> [epilogue]

maybe_print_player__prologue:
maybe_print_player__body:
maybe_print_player__epilogue:
	jr	$ra


################################################################################
# .TEXT <handle_command>
	.text
handle_command:
	# Subset:   2
	#
	# Args:
	#   - $a0: char map[MAP_HEIGHT][MAP_WIDTH]
	#   - $a1: struct Player *player
	#   - $a2: struct BlockSpawner *block_spawner
	#   - $a3: char input
	#
	# Returns:  None
	#
	# Frame:    [...]
	# Uses:     [...]
	# Clobbers: [...]
	#
	# Locals:
	#   - ...
	#
	# Structure:
	#   handle_command
	#   -> [prologue]
	#     -> body
	#   -> [epilogue]

handle_command__prologue:
handle_command__body:
handle_command__epilogue:
	jr	$ra


################################################################################
# .TEXT <handle_collision>
	.text
handle_collision:
	# Subset:   3
	#
	# Args:
	#   - $a0: char map[MAP_HEIGHT][MAP_WIDTH]
	#   - $a1: struct Player *player
	#
	# Returns:  $v0: int
	#
	# Frame:    [...]
	# Uses:     [...]
	# Clobbers: [...]
	#
	# Locals:
	#   - ...
	#
	# Structure:
	#   handle_collision
	#   -> [prologue]
	#     -> body
	#   -> [epilogue]

handle_collision__prologue:
handle_collision__body:
handle_collision__epilogue:
	jr	$ra


################################################################################
# .TEXT <maybe_pick_new_chunk>
	.text
maybe_pick_new_chunk:
	# Subset:   3
	#
	# Args:
	#   - $a0: struct BlockSpawner *block_spawner
	#
	# Returns:  None
	#
	# Frame:    [...]
	# Uses:     [...]
	# Clobbers: [...]
	#
	# Locals:
	#   - ...
	#
	# Structure:
	#   maybe_pick_new_chunk
	#   -> [prologue]
	#     -> body
	#   -> [epilogue]

maybe_pick_new_chunk__prologue:
maybe_pick_new_chunk__body:
maybe_pick_new_chunk__epilogue:
	jr	$ra


################################################################################
# .TEXT <do_tick>
	.text
do_tick:
	# Subset:   3
	#
	# Args:
	#   - $a0: char map[MAP_HEIGHT][MAP_WIDTH]
	#   - $a1: struct Player *player
	#   - $a2: struct BlockSpawner *block_spawner
	#
	# Returns:  None
	#
	# Frame:    [...]
	# Uses:     [...]
	# Clobbers: [...]
	#
	# Locals:
	#   - ...
	#
	# Structure:
	#   do_tick
	#   -> [prologue]
	#     -> body
	#   -> [epilogue]

do_tick__prologue:
do_tick__body:
do_tick__epilogue:
	jr	$ra

################################################################################
################################################################################
###                   PROVIDED FUNCTIONS — DO NOT CHANGE                     ###
################################################################################
################################################################################

################################################################################
# .TEXT <get_seed>
get_seed:
	# Args:     None
	#
	# Returns:  None
	#
	# Frame:    []
	# Uses:     [$v0, $a0]
	# Clobbers: [$v0, $a0]
	#
	# Locals:
	#   - $v0: seed
	#
	# Structure:
	#   get_seed
	#   -> [prologue]
	#     -> body
	#       -> invalid_seed
	#       -> seed_ok
	#   -> [epilogue]

get_seed__prologue:
get_seed__body:
	li	$v0, 4				# syscall 4: print_string
	la	$a0, get_seed__prompt_msg
	syscall					# printf("Enter a non-zero number for the seed: ")

	li	$v0, 5				# syscall 5: read_int
	syscall					# scanf("%d", &seed);
	sw	$v0, g_rng_state		# g_rng_state = seed;

	bnez	$v0, get_seed__seed_ok		# if (seed == 0) {
get_seed__invalid_seed:
	li	$v0, 4				#   syscall 4: print_string
	la	$a0, get_seed__prompt_invalid_msg
	syscall					#   printf("Invalid seed!\n");

	li	$v0, 10				#   syscall 10: exit
	li	$a0, 1
	syscall					#   exit(1);

get_seed__seed_ok:				# }
	li	$v0, 4				# sycall 4: print_string
	la	$a0, get_seed__set_msg
	syscall					# printf("Seed set to ");

	li	$v0, 1				# syscall 1: print_int
	lw	$a0, g_rng_state
	syscall					# printf("%d", g_rng_state);

	li	$v0, 11				# syscall 11: print_char
	la	$a0, '\n'
	syscall					# putchar('\n');

get_seed__epilogue:
	jr	$ra				# return;


################################################################################
# .TEXT <rng>
rng:
	# Args:     None
	#
	# Returns:  $v0: unsigned
	#
	# Frame:    []
	# Uses:     [$v0, $a0, $t0, $t1, $t2]
	# Clobbers: [$v0, $a0, $t0, $t1, $t2]
	#
	# Locals:
	#   - $t0 = copy of g_rng_state
	#   - $t1 = bit
	#   - $t2 = temporary register for bit operations
	#
	# Structure:
	#   rng
	#   -> [prologue]
	#     -> body
	#   -> [epilogue]

rng__prologue:
rng__body:
	lw	$t0, g_rng_state

	srl	$t1, $t0, 31		# g_rng_state >> 31
	srl	$t2, $t0, 30		# g_rng_state >> 30
	xor	$t1, $t2		# bit = (g_rng_state >> 31) ^ (g_rng_state >> 30)

	srl	$t2, $t0, 28		# g_rng_state >> 28
	xor	$t1, $t2		# bit ^= (g_rng_state >> 28)

	srl	$t2, $t0, 0		# g_rng_state >> 0
	xor	$t1, $t2		# bit ^= (g_rng_state >> 0)

	sll	$t1, 31			# bit << 31
	srl	$t0, 1			# g_rng_state >> 1
	or	$t0, $t1		# g_rng_state = (g_rng_state >> 1) | (bit << 31)

	sw	$t0, g_rng_state	# store g_rng_state

	move	$v0, $t0		# return g_rng_state

rng__epilogue:
	jr	$ra


################################################################################
# .TEXT <read_char>
read_char:
	# Args:     None
	#
	# Returns:  $v0: unsigned
	#
	# Frame:    []
	# Uses:     [$v0]
	# Clobbers: [$v0]
	#
	# Locals:   None
	#
	# Structure:
	#   read_char
	#   -> [prologue]
	#     -> body
	#   -> [epilogue]

read_char__prologue:
read_char__body:
	li	$v0, 12			# syscall 12: read_char
	syscall				# return getchar();

read_char__epilogue:
	jr	$ra
