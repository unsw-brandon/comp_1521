# Tested by [Brandon Chikandiwa (z5495844) on 25/02/2023]

.text
main:
    la      $a0,            prompt
    li      $v0,            4
    syscall 

    li      $v0,            5
    syscall 
    move    $t0,            $v0

    li      $v0,            4
    blt     $t0,            50,     fail
    blt     $t0,            65,     pass
    blt     $t0,            75,     credit
    blt     $t0,            85,     distinction
    j       h_distinction


fail:
    la      $a0,            fl
    syscall 
    j       end

pass:
    la      $a0,            ps
    syscall 
    j       end

credit:
    la      $a0,            cr
    syscall 
    j       end

distinction:
    la      $a0,            dn
    syscall 
    j       end

h_distinction:
    la      $a0,            hd
    syscall 
    j       end

end:
    la      $v0,            10
    li      $a0,            0
    syscall 

.data
prompt:
.asciiz "Enter a mark: "
fl:
.asciiz "FL\n"
ps:
.asciiz "PS\n"
cr:
.asciiz "CR\n"
dn:
.asciiz "DN\n"
hd:
.asciiz "HD\n"
