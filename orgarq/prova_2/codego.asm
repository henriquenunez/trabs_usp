
    .data

ins_str_call_1:	.asciiz	    "Insert first string: "
ins_str_call_2:	.asciiz	    "Insert second string: "
n_val_call:	.asciiz	    "Insert last index: "

res_call:	.asciiz	    "Result: "
newline:	.asciiz	    "\n"

str1:	.space 128 #128B arrays
str2:	.space 128

    .text

main:
    la $a0, ins_str_call_1
    jal print_string
    #First string insertion

    li $v0, 8 #Read string syscall
    la $a0, str1
    li $a1, 128
    syscall

    la $a0, ins_str_call_2
    jal print_string
    #Second string insertion

    li $v0, 8 #Read string syscall
    la $a0, str2
    li $a1, 128
    syscall

    la $a0, n_val_call
    jal print_string
    #N parameter insertion

    li $v0, 5
    syscall
    move $a0, $v0

    addi $sp, $sp, -8

    la $t0, str1
    sw $t0, 0($sp)

    la $t0, str2
    sw $t0, 4($sp)

    jal strncmp

    move $s0, $v0 #saving result

    addi $sp, $sp,  8

    la $a0, res_call
    jal print_string
    #Result:

    li $v0, 1
    move $a0, $s0
    syscall

    la $a0, newline
    jal print_string
    #\n

    li $v0, 10 #exit
    syscall

#I/O Utils

print_string:
    li $v0, 4
    syscall
    jr $ra


# Stack passed to strncmp:
#   - Adrress of str1 (8)
#   - Address of str2 (4)
# Registers:
# a0 last index to be checked
# return on v0

strncmp:
    addi $sp, $sp, -4
    sw $ra, 0($sp)

    lw $t0, 4($sp) #address of str1
    lw $t1, 8($sp) #address of str2

    xor $t2, $t2, $t2 #0 on $t2

    strncmploop:

	lb $t3, 0($t0)
	lb $t4, 0($t1)

	sub $t5, $t3, $t4 # str1[i] - str2[i]

	bne $t5, $0, endstrncmp

	addi $t0, $t0, 1 #plus one on t2
	addi $t1, $t1, 1 #plus one on t2
	addi $t2, $t2, 1 #plus one on t2

	blt $t2, $a0, strncmploop

    endstrncmp:
	lw $ra, 0($sp)
	move $v0, $t5

  	addi $sp, $sp, 4
	jr $ra
