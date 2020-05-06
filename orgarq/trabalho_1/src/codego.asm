#Henrique Hiram Libutti Núñez #11275300 #2020.1 #henrique.nunez@usp.br

# REGISTER CONVENTION FOR THIS PROGRAM:
# s0 is reserved for saving operation. i.e. sum
# s1 is reserved for saving numeric type option. i.e. float

# v0 is the register for the return value (int)
# f0 is the register for the return value (float)

# v1 is the register that points to the corresponding result string

# s6 stores v0 return before other procedure calls
# f6 stores f0 return before other procedure calls

# a0 is the register for "A" int parameter
# a1 is the register for "B" int parameter (when needed)
# f12 is the register for "A" float parameter
# f14 is the register for "B" float parameter (when needed)

# s7 register stores an address to return in case of error (will re-do main loop)

################################################################################
################################################################################
################################################################################
# Static data section
    .data

asw_sum:    .asciiz	"A + B:"
asw_sub:    .asciiz	"A - B:"
asw_mul:    .asciiz	"A * B:"
asw_div:    .asciiz	"A / B:"
asw_div_rem:.asciiz	"Division remainder:"
asw_pow:    .asciiz	"A ^ B:"
asw_sqrt:   .asciiz	"SQRT(A):"
asw_imc:    .asciiz	"IMC:"
asw_fac:    .asciiz	"A!:"
asw_fib:    .asciiz	"Fibonacci sequence until "
asw_tab_pt1:.asciiz	"Table of "
asw_tab_pt2:.asciiz	" * "
asw_tab_pt3:.asciiz	" = "

menu:	    .asciiz	"Available options:\n1-Sum\n2-Sub\n3-Mul\n4-Div\n5-IMC\n6-Pow\n7-Fac\n8-Sqrt\n9-Tab\n10-Fib\n0-Exit\n"
welcome_msg:.asciiz	"Welcome to this very calculator. SuCh MaThS\n"
inv_option: .asciiz	"Ivalid option.\n"
ask_num_t:  .asciiz	"Now, insert desired numeric type:\n1-Integer\n2-Floating point\n"
ask_a_b:    .asciiz	"Now, insert A and B values, separated by newline\n"
ask_a:	    .asciiz	"Now, insert A\n"

newline:    .asciiz	"\n"
colon:	    .asciiz	":"

neg_err_msg:	.asciiz	"ERROR: Negative input is invalid here!\n"
zdv_err_msg:	.asciiz	"ERROR: Zero division =>> big problem!\n"
neg_exp_err_msg:.asciiz "ERROR: Cannot expoentiate to power < 0 with int result!\n"
num_t_err_msg:	.asciiz "ERROR: This numeric type mustn't be used in this operation!"
zle_err_msg:	.asciiz "ERROR: input <= 0 is wrong for this operation!\n"

zero_epsilon_pos:   .float  0.00001
zero_epsilon_neg:   .float -0.1
zero_pt_5_const:    .float 0.5 #constant for sqrt method

################################################################################
################################################################################
################################################################################
# Actual code beyond this point

    .text

################################################################################
#CODE ENTRY POINT
main:
    #First things first, print Welcome message and menu
    la	$a0, welcome_msg
    jal	print_string

    #If error is encountered, return to address on register s7
    la $s7, options

#Shows available options, reads and stores those
options:

    la $a0, menu
    jal	print_string
    jal read_option
    move $s0, $v0 #Saves desired operation

    ble $s0, $0, exit #Tests if 0 or less was inserted (exit)

### Special cases that don't require numeric type option.

    #imc: only float
    li $t0, 5
    beq $s0, $t0, set_float_num_type

    #fib: only integers
    li $t0, 7
    beq $s0, $t0, set_int_num_type

    #sqrt: only floating point
    li $t0, 8
    beq $s0, $t0, set_float_num_type

    #fac: only integers
    li $t0, 9
    beq $s0, $t0, set_int_num_type

    j numeric_type

    #sets numeric type, then bypasses numeric type input
    set_int_num_type:
	li $s1, 1
        j preset_num_type

    set_float_num_type:
        li $s1, 2
	j preset_num_type


numeric_type:

    la $a0, ask_num_t #Asks numeric type, int or float
    jal print_string
    jal read_option
    move $s1, $v0

preset_num_type:

    li $t0, 6
    bgt, $s0, $t0, one_parameter_flow #Branches depending on number of parameters needed

#TWO PARAMETERS (A and B)

two_parameter_flow:

    la $a0, ask_a_b #prompts the user to insert a and b
    jal print_string

    li $t0, 1				#Reads input correspondingly
    bne $s1, $t0, float_two_param_input #By branching read

int_two_param_input:

    jal read_a_b_int #Reading integers and saving results to a0 and a1
    move $a0, $v0
    move $a1, $v1
    j two_param_ops

float_two_param_input:

    jal read_a_b_float #Reading floats and saving to f12 and f14
    mov.s $f12, $f0
    mov.s $f14, $f2

two_param_ops:

    la $ra, end_of_operation #stores return address

    li $t0, 1
    beq $s0, $t0, sum #Tests if 1 was inserted (sum)

    li $t0, 2
    beq $s0, $t0, sub #Tests if 2 was inserted (sub)

    li $t0, 3
    beq $s0, $t0, mul #Tests if 3 was inserted (mul)

    li $t0, 5
    beq $s0, $t0, imc #Tests if 5 was inserted (imc)

    li $t0, 6
    beq $s0, $t0, pow #Tests if 6 was inserted (pow)

    la $ra, options #stores return address because div knows how to print

    li $t0, 4
    beq $s0, $t0, div #Tests if 4 was inserted (div)


#ONE PARAMETER ONLY (A)

one_parameter_flow:

    la $a0, ask_a #prompts the user to insert a and b
    jal print_string

    li $t0, 1				#Reads input correspondingly
    bne $s1, $t0, float_one_param_input #By branching read

    jal read_a_int #Reading integers and saving results to a0 and a1
    move $a0, $v0
    j one_param_ops

float_one_param_input:

    jal read_a_float #Reading floats and saving to f12 and f14
    mov.s $f12, $f0

one_param_ops:

    la $ra, end_of_operation #Procedures return to print result

    li $t0, 8
    beq $s0, $t0, sqrt #Tests if 1 was inserted (sqrt)

    li $t0, 7
    beq $s0, $t0, fac #Tests if 1 was inserted (fac)

    #since these procedures already print the result, just prompt menu again
    la $ra, options

    li $t0, 9
    beq $s0, $t0, tab #Tests if 1 was inserted (tab)

    li $t0, 10
    beq $s0, $t0, fib #Tests if 1 was inserted (fib)

    #Invalid option
    la $a0, inv_option
    jal print_string
    j options

end_of_operation:
    jal print_results
    j options

#Exit main
exit:
    li $v0, 10
    syscall

##FINISH PROGRAM

################################################################################
#   I/O utility subroutines

#Print functions that print previously registered values
print_integer:
    li $v0, 1
    syscall

    jr $ra

print_float:
    li $v0, 2
    syscall
    jr $ra


print_string:
    li $v0, 4
    syscall
    jr $ra

#Subroutine for printing results
print_results:
    addi $sp, $sp, -4
    sw	 $ra, 0($sp)

    move $s6, $v0   #stores v0 before procedure call
    mov.s $f16, $f0 #stores f0 for later printing

    move $a0, $v1 #moves result string address into $a0, for syscall
    jal print_string

    li $t0, 1
    bne $s1, $t0, float_print_results #If s1 (int or float) holds 1, continue flow

    int_print_results:
        move $a0, $s6
        jal print_integer

        j end_print_results

    float_print_results:
	mov.s $f12, $f16 #Passes float result as parameter
	jal print_float

	j end_print_results

end_print_results:

    la $a0, newline #prints trailing newline character
    jal print_string

    lw	 $ra, 0($sp) #loads return address
    addi $sp, $sp, 4

    jr $ra

#Reads integer and returns
read_option:
    li $v0, 5
    syscall

    jr $ra


#Two integer readings
read_a_b_int:
    li $v0, 5
    syscall	    #$v0 receives A

    move $v1, $v0   #$v1 receives A

    li $v0, 5
    syscall	    #$v0 receives B

    #Just a good and old XOR swap, because yes.
    xor $v0, $v0, $v1
    xor $v1, $v0, $v1 #$v0 = A
    xor $v0, $v0, $v1 #$v1 = B

    jr $ra

#Two float readings
read_a_b_float:
    li $v0, 6
    syscall	    #$f0 receives A

    mov.s $f2, $f0   #$f2 receives A

    li $v0, 6
    syscall	    #$f0 receives B

    mov.s $f4, $f2
    mov.s $f2, $f0
    mov.s $f0, $f4

    jr $ra

#One integer readings
read_a_int:
    li $v0, 5
    syscall

    jr $ra

read_a_float:
    li $v0, 6
    syscall

    jr $ra

################################################################################
#   Actual calculator functions

#Sum
sum:

    la $v1, asw_sum
    li $t0, 1
    bne $s1, $t0, sum_float

sum_int:
    add $v0, $a0, $a1
    jr $ra

sum_float:
    add.s $f0, $f12, $f14
    jr $ra


#Subtraction
sub:

    la $v1, asw_sub
    li $t0, 1
    bne $s1, $t0, sub_float

sub_int:
    sub $v0, $a0, $a1
    jr $ra

sub_float:
    sub.s $f0, $f12, $f14
    jr $ra


#Multiplication
mul:
    la $v1, asw_mul

    li $t0, 1
    bne $s1, $t0, mul_float

mul_int:
    mul $v0, $a0, $a1
    jr $ra

mul_float:
    mul.s $f0, $f12, $f14
    jr $ra


#in this case, we need to print the result in a different fashion, since in my
#approach, when dividing in integer mode, both the integer division and the
#remainder will be shown

#Division, A / B where A => a0/f12, B => a1/f14. Result in v0/f0
div:
    addi $sp, $sp, -4
    sw $ra, 0($sp)

    la $v1, asw_div

    li $t0, 1
    bne $s1, $t0, div_float

div_int:
    div $a0, $a1

    beq $a1, $0, zero_div_handler#If divisor is 0, throw error

    #moves low (quocient)
    mflo $v0

    la $a0, asw_div #loads answer string
    jal print_results

    #moves from high (remaninder)
    mfhi $v0

    la $a0, asw_div_rem
    jal print_results

    j end_div

div_float:

    sub.s $f8, $f8, $f8       # store the value 0 in register $f0
    c.eq.s $f14, $f8
    bc1t zero_div_handler   # if 0 will handle zero division
    nop

    div.s $f0, $f12, $f14

    la $a0, asw_div
    jal print_results

    j end_div

end_div:
    lw $ra, 0($sp)
    addi $sp, $sp, 4
    jr $ra

#Power, A ^ B where A => a0/f12, B => a1/f14 (cast to int). Result in v0/f0
pow:
    la $v1, asw_pow

    li $t0, 1 #Initial values for computing exponentiation
    move $t1, $a1

    li $t0, 1 #Checks the numeric type, and branches to correct loop
    bne $s1, $t0, float_pow

    #It makes no sense to power a number to a negative and ask for integer
    #result, so throws an error in this case
    blt $a1, $0, negative_exponent_int_pow

    int_pow_iter_positive:
	beq $t1, $0, end_pow #if 0 ends subroutine

	mul $t0, $t0, $a0

	addi $t1, $t1, -1 #Decreases number of products to be done
	j int_pow_iter_positive

    float_pow:

        li $t2, 1	    #initial value of 1 will be moved to register f16
        mtc1 $t2, $f16
        cvt.s.w $f16, $f16

        cvt.w.s $f14, $f14	#Converts B, float to integer (number of iterations)
        mfc1 $t1, $f14	#Actually moves to int register

        blt $t1, $0, float_pow_iter_negative #If power is less than 0, do exponentiation of neg vals

    float_pow_iter_positive:
	ble $t1, $0, end_pow	#if <= 0 ends subroutine

	mul.s $f16, $f16, $f12

	addi $t1, $t1, -1	#Decreases number of products to be done
	j float_pow_iter_positive

    float_pow_iter_negative:
	bge $t1, $0, end_pow	#if >= 0 ends subroutine

	div.s $f16, $f16, $f12

	addi $t1, $t1, 1	#Decreases number of divisions to be done
	j float_pow_iter_negative

    end_pow:

        move $v0, $t0	#Int result
	mov.s $f0, $f16	#Float result

	jr $ra

#Square root using Newton's method. Input is in $f12. Result is in $f0.
sqrt:
    la $v1, asw_sqrt #sqrt answer

    xor $t0, $t0, $t0	#zera t0
    mtc1 $t0, $f18	#Passa para o coprocessador 1 (float)
    cvt.s.w $f18, $f18	#Converte 0 para float

    c.lt.s $f12, $f18		# in case input is negative
    bc1t negative_error_handler # error will be thrown
    nop

    c.eq.s $f12, $f18
    bc1t sqrt_of_zero # error will be thrown
    nop

    mov.s $f6, $f12

sqrt_iter:

    nop
    mov.s $f8, $f6		# temp x
    div.s $f10, $f12, $f8	#Input / temp
    add.s $f6,  $f6,  $f10	#temp + (Input / temp)
    lwc1  $f10, zero_pt_5_const	#0.5 in register f8
    mul.s $f6, $f6, $f10	#f6 <= newX (algorithm)
    sub.s $f8, $f6, $f8
    abs.s $f8, $f8

    lwc1  $f10, zero_epsilon_pos#convergence positive epsilon
    c.lt.s $f8, $f10		#less than epsilon
    bc1f sqrt_iter		#if greater than epsilon, re_iterate

    mov.s $f0, $f6  #return value

    jr $ra

sqrt_of_zero:
    nop #Read that after branching with co-proc1 is good to insert nop
    xor $t0, $t0, $t0	#zera t0
    mtc1 $t0, $f0	#Passa para o coprocessador 1 (float)
    cvt.s.w $f0, $f0	#Converte 0 para float

    jr $ra


#Formula for BMI a.k.a IMC is: weight^2/height
#A (weight) is in f12
#B (height) is in f14
imc:
    la $v1, asw_imc

    xor $t0, $t0, $t0	#zera t0
    mtc1 $t0, $f18	#Passa para o coprocessador 1 (float)
    cvt.s.w $f18, $f18	#Converte 0 para float

    c.le.s $f12, $f18		  # in case weight is zero or less
    bc1t z_less_error_handler   # error will be thrown
    nop

    c.le.s $f14, $f18		  # in case height is zero or less
    bc1t z_less_error_handler   # error will be thrown
    nop

    mul.s $f14, $f14, $f14 # Weight squared
    div.s $f0,	$f12, $f14 # Divided by height

    jr $ra


#Factorial, A!. A is in a0. Result in v0.
fac:

    blt $a0, $0, negative_error_handler #Fac imposible in negative numbers
    beq $a0, $0, fac_case_zero		#0 needs special treatment

    la $v1, asw_fac # "A!" for answer

    move $a1, $a0
    li $v0, 1 #Neutral element of multiplications

    fac_iter: #Current product in a0, current number in a1
        addi $sp, $sp, -8	#Reserves space on stack
        sw $ra, 4($sp)	#Stores return address
        sw $a1, 0($sp)	#Stores number to be multiplied

        addi $a1, $a1, -1	#Decreases number to be multiplied with

        li $t0, 2		#2 must be the last number
        blt $a1, $t0, end_fac

    next_fac_iter:
        jal fac_iter

    end_fac:

        lw $t0, 0($sp)
        mul $v0, $v0, $t0

        lw $ra, 4($sp)
        addi $sp, $sp,  8	#Returns space on stack

        jr $ra

    fac_case_zero:
        li $v0, 1 #Since a 0 number set has only one possible way of arrangement

        jr $ra

#Fibonacci sequence until given 'ceiling' value A, stored in a0
fib:

    ble $a0, $0, z_less_error_handler #Error if A <= 0

    addi $sp, $sp, -8	#Space for saving ra
    sw $ra, 4($sp)	#Stack return address
    sw $a0, 0($sp)	#Save parameter

    la $a0, asw_fib
    jal print_string

    lw $a0, 0($sp)  #"A" parameter

    la $a0, colon   #Format print
    jal print_string

    la $a0, newline #Format print
    jal print_string

    li $t0, 1 #Beginning of iteration
    li $t1, 1

    fib_iter:

	move $a0, $t0		#Print current value
        jal print_integer
	la $a0, newline
        jal print_string

	add $t3, $t0, $t1	#Fibonacci series iteration fn = f_n-1 + f_n-2
        move $t0, $t1
	move $t1, $t3

	lw $t3, 0($sp)		#Load ceiling value to t3

	ble $t0, $t3, fib_iter	#If value hasnt reached ceiling, iterate again

    lw $ra, 4($sp)	#Stack return address
    addi $sp, $sp,  8	#Space for saving ra

    jr $ra


#Table of a given number A, stored in a0
tab:
    addi $sp, $sp, -12	#Reserves stack space for return address and parameter
    sw $ra, 8($sp)	#Saves return address on stack, since other calls happen
    sw $a0, 4($sp)	#Saves parameter on stack, since other calls happen

    li $t1, 1	    #Index begins at 1
    sw $t1, 0($sp)  #Stores current index on stack

    la $a0, asw_tab_pt1	#Table of ...
    jal print_string

    lw $a0, 4($sp)	#Loads parameter "A" for printing
    jal print_integer

    la $a0, newline	#Print \n
    jal print_string

    tab_iter:

        lw $a0, 4($sp)	    # "A"
	jal print_integer

	la $a0, asw_tab_pt2 # *
	jal print_string

	lw $a0, 0($sp)	    # "i"
	jal print_integer

	la $a0, asw_tab_pt3 # =
	jal print_string

	lw $t1, 0($sp)	    #Loads index from stack
	lw $t2, 4($sp)	    #Loads parameter from stack
	mul $t2, $t2, $t1   #Parameter times index

	addi $t1, $t1, 1    #Increases index value on 1 unit
	sw $t1, 0($sp)	    #Stores index on stack

	move $a0, $t2	    #Prints current result
	jal print_integer

        la $a0, newline	#Print \n
	jal print_string

	lw $t1, 0($sp)	    #Loads index from stack (again since reg. is temp.)
	li $t0, 10	    #10 iterations must be done
	ble $t1, $t0, tab_iter

    lw $ra, 8($sp)	#Loads return address from stack.
    addi $sp, $sp, 12	#Returns space acquired

    jr $ra

################################################################################
#List of posible cases for error handling

z_less_error_handler:

    la $a0, zle_err_msg
    j error_handler

negative_exponent_int_pow:

    la $a0, neg_exp_err_msg
    j error_handler

negative_error_handler:

    la $a0, neg_err_msg
    j error_handler

zero_div_handler:

    la $a0, zdv_err_msg
    j error_handler

num_type_handler:

    la $a0, num_t_err_msg
    j error_handler

error_handler:

    #addi $sp, $sp, -4 #saves return address
    #sw $ra, 0($sp)

    #0 value to registers
    xor $v0, $v0, $v0
    sub.s $f0, $f0, $f0

    jal print_string #prints error message

    #lw $ra, 0($sp)
    #addi $sp, $sp, 4
    jr $s7

