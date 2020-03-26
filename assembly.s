	.file	"hanoi.c"
	.text
	.globl	createTowers
	.type	createTowers, @function
createTowers:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movl	$24, %edi
	call	malloc@PLT
	movq	%rax, -8(%rbp)
	movl	-20(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movl	-20(%rbp), %eax
	cltq
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	calloc@PLT
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	movl	-20(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movl	-20(%rbp), %eax
	cltq
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	calloc@PLT
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 8(%rax)
	movl	-20(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movl	-20(%rbp), %eax
	cltq
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	calloc@PLT
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 16(%rax)
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	createTowers, .-createTowers
	.globl	populateTowers
	.type	populateTowers, @function
populateTowers:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L3
.L4:
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$2, %rdx
	addq	%rax, %rdx
	movl	-20(%rbp), %eax
	subl	-4(%rbp), %eax
	movl	%eax, (%rdx)
	addl	$1, -4(%rbp)
.L3:
	movl	-4(%rbp), %eax
	cmpl	-20(%rbp), %eax
	jl	.L4
	nop
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	populateTowers, .-populateTowers
	.section	.rodata
.LC0:
	.string	"\033[F"
	.text
	.globl	clear
	.type	clear, @function
clear:
.LFB8:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L6
.L7:
	movq	stdout(%rip), %rax
	movq	%rax, %rcx
	movl	$3, %edx
	movl	$1, %esi
	leaq	.LC0(%rip), %rdi
	call	fwrite@PLT
	addl	$1, -4(%rbp)
.L6:
	movl	-4(%rbp), %eax
	cmpl	-20(%rbp), %eax
	jl	.L7
	nop
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	clear, .-clear
	.section	.rodata
.LC1:
	.string	"%d\t%d\t%d\n"
	.text
	.globl	printTowers
	.type	printTowers, @function
printTowers:
.LFB9:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L9
.L10:
	movq	-32(%rbp), %rax
	movq	16(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$2, %rdx
	addq	%rdx, %rax
	movl	(%rax), %esi
	movq	-32(%rbp), %rax
	movq	8(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$2, %rdx
	addq	%rdx, %rax
	movl	(%rax), %ecx
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$2, %rdx
	addq	%rdx, %rax
	movl	(%rax), %edx
	movq	stdout(%rip), %rax
	movl	%esi, %r8d
	leaq	.LC1(%rip), %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf@PLT
	addl	$1, -4(%rbp)
.L9:
	movl	-4(%rbp), %eax
	cmpl	-20(%rbp), %eax
	jl	.L10
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	printTowers, .-printTowers
	.globl	printTowersWithoutADT
	.type	printTowersWithoutADT, @function
printTowersWithoutADT:
.LFB10:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	%rcx, -48(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L12
.L13:
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-48(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %esi
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %ecx
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %edx
	movq	stdout(%rip), %rax
	movl	%esi, %r8d
	leaq	.LC1(%rip), %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf@PLT
	addl	$1, -4(%rbp)
.L12:
	movl	-4(%rbp), %eax
	cmpl	-20(%rbp), %eax
	jl	.L13
	nop
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	printTowersWithoutADT, .-printTowersWithoutADT
	.globl	moveDisks
	.type	moveDisks, @function
moveDisks:
.LFB11:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movl	%edi, -4(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	movq	%rcx, -32(%rbp)
	movq	%r8, -40(%rbp)
	cmpl	$1, -4(%rbp)
	jne	.L15
	movq	-16(%rbp), %rax
	movl	(%rax), %edx
	movq	-24(%rbp), %rax
	movl	%edx, (%rax)
	movq	-16(%rbp), %rax
	movl	$0, (%rax)
.L15:
	cmpl	$1, -4(%rbp)
	jle	.L17
	movl	-4(%rbp), %eax
	leal	-1(%rax), %edi
	movq	-40(%rbp), %rsi
	movq	-24(%rbp), %rcx
	movq	-32(%rbp), %rdx
	movq	-16(%rbp), %rax
	movq	%rsi, %r8
	movq	%rax, %rsi
	call	moveDisks
	movl	-4(%rbp), %eax
	cltq
	salq	$2, %rax
	leaq	-4(%rax), %rdx
	movq	-16(%rbp), %rax
	addq	%rdx, %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$2, %rdx
	leaq	-4(%rdx), %rcx
	movq	-24(%rbp), %rdx
	addq	%rcx, %rdx
	movl	(%rax), %eax
	movl	%eax, (%rdx)
	movl	-4(%rbp), %eax
	cltq
	salq	$2, %rax
	leaq	-4(%rax), %rdx
	movq	-16(%rbp), %rax
	addq	%rdx, %rax
	movl	$0, (%rax)
	movl	-4(%rbp), %eax
	leal	-1(%rax), %edi
	movq	-40(%rbp), %rsi
	movq	-16(%rbp), %rcx
	movq	-24(%rbp), %rdx
	movq	-32(%rbp), %rax
	movq	%rsi, %r8
	movq	%rax, %rsi
	call	moveDisks
.L17:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE11:
	.size	moveDisks, .-moveDisks
	.section	.rodata
.LC2:
	.string	"%d"
	.text
	.globl	main
	.type	main, @function
main:
.LFB12:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	leaq	-20(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC2(%rip), %rdi
	movl	$0, %eax
	call	__isoc99_scanf@PLT
	movl	-20(%rbp), %eax
	movl	%eax, %edi
	call	createTowers
	movq	%rax, -16(%rbp)
	movl	-20(%rbp), %eax
	movq	-16(%rbp), %rdx
	movq	%rdx, %rsi
	movl	%eax, %edi
	call	populateTowers
	movl	-20(%rbp), %eax
	movq	-16(%rbp), %rdx
	movq	%rdx, %rsi
	movl	%eax, %edi
	call	printTowers
	movq	-16(%rbp), %rax
	movq	8(%rax), %rcx
	movq	-16(%rbp), %rax
	movq	16(%rax), %rdx
	movq	-16(%rbp), %rax
	movq	(%rax), %rsi
	movl	-20(%rbp), %eax
	movq	-16(%rbp), %rdi
	movq	%rdi, %r8
	movl	%eax, %edi
	call	moveDisks
	movl	-20(%rbp), %eax
	movq	-16(%rbp), %rdx
	movq	%rdx, %rsi
	movl	%eax, %edi
	call	printTowers
	movl	$0, %eax
	movq	-8(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L20
	call	__stack_chk_fail@PLT
.L20:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE12:
	.size	main, .-main
	.ident	"GCC: (Arch Linux 9.2.1+20200130-2) 9.2.1 20200130"
	.section	.note.GNU-stack,"",@progbits
