# Tested by [Brandon Chikandiwa (z5495844) on 16/02/2023]

.data
prompt1: .asciiz "Enter first number: "
prompt2: .asciiz "Enter second number: "

answer1: .asciiz "The sum of all numbers between "
answer2: .asciiz " and "
answer3: .asciiz " (inclusive) is: "
new_line: .asciiz "\n"

.text
.globl main

main:

    li      $v0,    4
    la      $a0,    prompt1
    syscall 

    li      $v0,    5
    syscall 
    move    $t0,    $v0

    li      $v0,    4
    la      $a0,    prompt2
    syscall 

    li      $v0,    5
    syscall 
    move    $t1,    $v0

    sub     $t2,    $t1,        $t0                 # number2 - number1
    add     $t2,    $t2,        1                   # (number2 - number1) + 1
    add     $t3,    $t0,        $t1                 # number1 + number2
    mul     $t4,    $t2,        $t3                 # (number2 - number1 + 1) * (number1 + number2)
    div     $t5,    $t4,        2                   # ((number2 - number1 + 1) * (number1 + number2)) / 2

    li      $v0,    4
    la      $a0,    answer1
    syscall 

    li      $v0,    1
    move    $a0,    $t0
    syscall 

    li      $v0,    4
    la      $a0,    answer2
    syscall 

    li      $v0,    1
    move    $a0,    $t1
    syscall 

    li      $v0,    4
    la      $a0,    answer3
    syscall 

    li      $v0,    1
    move    $a0,    $t5
    syscall 
    
    li      $v0,    4
    la      $a0,    new_line
    syscall 

    li      $v0,    10
    li      $a0,    0
    syscall 


