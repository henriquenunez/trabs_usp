	.file	"codigo.c"
	.text
.Ltext0:
	.globl	FORMAT_STR
	.section	.rodata
	.align 8
.LC0:
	.string	"Nome: %s\nMarca: %s\nC\303\263digo de barras: %s\nPre\303\247o: %.2f\302\243\n"
	.section	.data.rel.local,"aw"
	.align 8
	.type	FORMAT_STR, @object
	.size	FORMAT_STR, 8
FORMAT_STR:
	.quad	.LC0
	.section	.rodata
.LC1:
	.string	"%u"
	.text
	.globl	input_operation
	.type	input_operation, @function
input_operation:
.LFB6:
	.file 1 "codigo.c"
	.loc 1 49 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	.loc 1 49 1
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	.loc 1 52 5
	leaq	-16(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	__isoc99_scanf@PLT
	.loc 1 53 8
	movl	-16(%rbp), %eax
	movl	%eax, -12(%rbp)
	.loc 1 55 12
	movl	-12(%rbp), %eax
	.loc 1 56 1
	movq	-8(%rbp), %rdx
	xorq	%fs:40, %rdx
	je	.L3
	call	__stack_chk_fail@PLT
.L3:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	input_operation, .-input_operation
	.globl	clear_vec
	.type	clear_vec, @function
clear_vec:
.LFB7:
	.loc 1 59 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	.loc 1 60 16
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	.loc 1 60 7
	testq	%rax, %rax
	je	.L6
	.loc 1 62 2
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	free@PLT
	.loc 1 63 24
	movq	-8(%rbp), %rax
	movq	$0, (%rax)
	.loc 1 64 17
	movq	-8(%rbp), %rax
	movq	$-1, 8(%rax)
.L6:
	.loc 1 66 1
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	clear_vec, .-clear_vec
	.section	.rodata
	.align 8
.LC2:
	.string	"Insert operation:\n0 for inserting register\n1 for reading registers\n2 for stop"
.LC3:
	.string	"wb"
.LC4:
	.string	"products.bin"
.LC5:
	.string	"rb"
.LC6:
	.string	"\n********REGISTERS********"
.LC7:
	.string	"stop"
	.text
	.globl	main
	.type	main, @function
main:
.LFB8:
	.loc 1 86 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	.loc 1 90 10
	movb	$0, -29(%rbp)
.L12:
	.loc 1 95 2
	leaq	.LC2(%rip), %rdi
	call	puts@PLT
	.loc 1 97 7
	movl	$0, %eax
	call	input_operation
	movl	%eax, -28(%rbp)
	.loc 1 98 2
	cmpl	$2, -28(%rbp)
	je	.L8
	cmpl	$2, -28(%rbp)
	ja	.L9
	cmpl	$0, -28(%rbp)
	je	.L10
	cmpl	$1, -28(%rbp)
	je	.L11
	jmp	.L9
.L10:
	.loc 1 101 15
	leaq	.LC3(%rip), %rsi
	leaq	.LC4(%rip), %rdi
	call	fopen@PLT
	movq	%rax, -24(%rbp)
	.loc 1 102 3
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	write_entries
	.loc 1 103 3
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	fclose@PLT
	.loc 1 104 3
	jmp	.L9
.L11:
	.loc 1 106 15
	leaq	.LC5(%rip), %rsi
	leaq	.LC4(%rip), %rdi
	call	fopen@PLT
	movq	%rax, -24(%rbp)
	.loc 1 107 17
	movq	-24(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	read_entries
	movq	%rax, -16(%rbp)
	movq	%rdx, -8(%rbp)
	.loc 1 108 3
	leaq	.LC6(%rip), %rdi
	call	puts@PLT
	.loc 1 109 3
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rdi
	movq	%rax, %rsi
	call	print_registers
	.loc 1 112 3
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	fclose@PLT
	.loc 1 113 3
	jmp	.L9
.L8:
	.loc 1 115 3
	leaq	.LC7(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	.loc 1 116 8
	movb	$1, -29(%rbp)
.L9:
	.loc 1 118 5
	cmpb	$0, -29(%rbp)
	je	.L12
	.loc 1 120 12
	movl	$0, %eax
	.loc 1 121 1
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	main, .-main
	.globl	write_register
	.type	write_register, @function
write_register:
.LFB9:
	.loc 1 127 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	.loc 1 128 5
	movq	-8(%rbp), %rax
	movq	%rax, %rcx
	movl	$20, %edx
	movl	$1, %esi
	leaq	16(%rbp), %rdi
	call	fwrite@PLT
	.loc 1 129 5
	movq	-8(%rbp), %rdx
	leaq	36(%rbp), %rax
	movq	%rdx, %rcx
	movl	$20, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fwrite@PLT
	.loc 1 130 5
	movq	-8(%rbp), %rdx
	leaq	56(%rbp), %rax
	movq	%rdx, %rcx
	movl	$13, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fwrite@PLT
	.loc 1 131 5
	movq	-8(%rbp), %rdx
	leaq	72(%rbp), %rax
	movq	%rdx, %rcx
	movl	$1, %edx
	movl	$4, %esi
	movq	%rax, %rdi
	call	fwrite@PLT
	.loc 1 132 1
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	write_register, .-write_register
	.section	.rodata
.LC8:
	.string	"Deu merda!"
	.text
	.globl	read_register
	.type	read_register, @function
read_register:
.LFB10:
	.loc 1 136 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$104, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -104(%rbp)
	movq	%rsi, -112(%rbp)
	.loc 1 136 1
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	.loc 1 138 5
	leaq	-96(%rbp), %rax
	movl	$60, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	memset@PLT
	.loc 1 139 9
	movq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	feof@PLT
	.loc 1 139 8
	cmpl	$-1, %eax
	jne	.L16
	.loc 1 139 26 discriminator 1
	leaq	.LC8(%rip), %rdi
	call	puts@PLT
.L16:
	.loc 1 142 5
	movq	-112(%rbp), %rdx
	leaq	-96(%rbp), %rax
	movq	%rdx, %rcx
	movl	$20, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	.loc 1 143 5
	movq	-112(%rbp), %rax
	leaq	-96(%rbp), %rdx
	leaq	20(%rdx), %rdi
	movq	%rax, %rcx
	movl	$20, %edx
	movl	$1, %esi
	call	fread@PLT
	.loc 1 144 5
	movq	-112(%rbp), %rax
	leaq	-96(%rbp), %rdx
	leaq	40(%rdx), %rdi
	movq	%rax, %rcx
	movl	$13, %edx
	movl	$1, %esi
	call	fread@PLT
	.loc 1 145 5
	movq	-112(%rbp), %rax
	leaq	-96(%rbp), %rdx
	leaq	56(%rdx), %rdi
	movq	%rax, %rcx
	movl	$1, %edx
	movl	$4, %esi
	call	fread@PLT
	.loc 1 147 12
	movq	-104(%rbp), %rax
	movq	-96(%rbp), %rcx
	movq	-88(%rbp), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	-80(%rbp), %rcx
	movq	-72(%rbp), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	-64(%rbp), %rcx
	movq	-56(%rbp), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	-48(%rbp), %rdx
	movq	%rdx, 48(%rax)
	movl	-40(%rbp), %edx
	movl	%edx, 56(%rax)
	.loc 1 148 1
	movq	-24(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L18
	call	__stack_chk_fail@PLT
.L18:
	movq	-104(%rbp), %rax
	addq	$104, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	read_register, .-read_register
	.section	.rodata
.LC9:
	.string	" %s %s %s %f"
	.text
	.globl	input_register
	.type	input_register, @function
input_register:
.LFB11:
	.loc 1 153 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$200, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -200(%rbp)
	.loc 1 153 1
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	.loc 1 160 5
	leaq	-180(%rbp), %rsi
	leaq	-48(%rbp), %rcx
	leaq	-80(%rbp), %rdx
	leaq	-112(%rbp), %rax
	movq	%rsi, %r8
	movq	%rax, %rsi
	leaq	.LC9(%rip), %rdi
	movl	$0, %eax
	call	__isoc99_scanf@PLT
	.loc 1 164 5
	movq	-112(%rbp), %rax
	movq	-104(%rbp), %rdx
	movq	%rax, -176(%rbp)
	movq	%rdx, -168(%rbp)
	movl	-96(%rbp), %eax
	movl	%eax, -160(%rbp)
	.loc 1 165 5
	movq	-80(%rbp), %rax
	movq	-72(%rbp), %rdx
	movq	%rax, -156(%rbp)
	movq	%rdx, -148(%rbp)
	movl	-64(%rbp), %eax
	movl	%eax, -140(%rbp)
	.loc 1 166 5
	movq	-48(%rbp), %rax
	movq	%rax, -136(%rbp)
	movl	-40(%rbp), %eax
	movl	%eax, -128(%rbp)
	movzbl	-36(%rbp), %eax
	movb	%al, -124(%rbp)
	.loc 1 167 25
	movss	-180(%rbp), %xmm0
	movss	%xmm0, -120(%rbp)
	.loc 1 169 12
	movq	-200(%rbp), %rax
	movq	-176(%rbp), %rcx
	movq	-168(%rbp), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	-160(%rbp), %rcx
	movq	-152(%rbp), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	-144(%rbp), %rcx
	movq	-136(%rbp), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	-128(%rbp), %rdx
	movq	%rdx, 48(%rax)
	movl	-120(%rbp), %edx
	movl	%edx, 56(%rax)
	.loc 1 170 1
	movq	-24(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L21
	call	__stack_chk_fail@PLT
.L21:
	movq	-200(%rbp), %rax
	addq	$200, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE11:
	.size	input_register, .-input_register
	.globl	output_register
	.type	output_register, @function
output_register:
.LFB12:
	.loc 1 174 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$96, %rsp
	.loc 1 174 1
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	.loc 1 175 10
	movq	$0, -64(%rbp)
	movq	$0, -56(%rbp)
	movl	$0, -48(%rbp)
	movb	$0, -44(%rbp)
	.loc 1 176 10
	movq	$0, -32(%rbp)
	movq	$0, -24(%rbp)
	movl	$0, -16(%rbp)
	movb	$0, -12(%rbp)
	.loc 1 177 10
	movq	$0, -78(%rbp)
	movl	$0, -70(%rbp)
	movw	$0, -66(%rbp)
	.loc 1 180 5
	movq	16(%rbp), %rax
	movq	24(%rbp), %rdx
	movq	%rax, -64(%rbp)
	movq	%rdx, -56(%rbp)
	movl	32(%rbp), %eax
	movl	%eax, -48(%rbp)
	.loc 1 181 5
	movq	36(%rbp), %rax
	movq	44(%rbp), %rdx
	movq	%rax, -32(%rbp)
	movq	%rdx, -24(%rbp)
	movl	52(%rbp), %eax
	movl	%eax, -16(%rbp)
	.loc 1 182 5
	movq	56(%rbp), %rax
	movq	%rax, -78(%rbp)
	movl	64(%rbp), %eax
	movl	%eax, -70(%rbp)
	movzbl	68(%rbp), %eax
	movb	%al, -66(%rbp)
	.loc 1 183 18
	movss	72(%rbp), %xmm0
	movss	%xmm0, -84(%rbp)
	.loc 1 186 5
	cvtss2sd	-84(%rbp), %xmm0
	movq	FORMAT_STR(%rip), %rax
	leaq	-78(%rbp), %rcx
	leaq	-32(%rbp), %rdx
	leaq	-64(%rbp), %rsi
	movq	%rax, %rdi
	movl	$1, %eax
	call	printf@PLT
	.loc 1 190 1
	nop
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L23
	call	__stack_chk_fail@PLT
.L23:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE12:
	.size	output_register, .-output_register
	.globl	write_entries
	.type	write_entries, @function
write_entries:
.LFB13:
	.loc 1 196 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$104, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -104(%rbp)
	.loc 1 196 1
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
.L28:
	.loc 1 201 18
	leaq	-96(%rbp), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	input_register
	.loc 1 202 18
	movss	-40(%rbp), %xmm0
	.loc 1 202 4
	movss	.LC10(%rip), %xmm1
	ucomiss	%xmm1, %xmm0
	jp	.L25
	movss	.LC10(%rip), %xmm1
	ucomiss	%xmm1, %xmm0
	jne	.L25
	.loc 1 205 13
	movl	$0, %eax
	.loc 1 214 1
	movq	-24(%rbp), %rsi
	xorq	%fs:40, %rsi
	je	.L29
	jmp	.L31
.L25:
	.loc 1 208 2
	movq	-104(%rbp), %rdx
	subq	$64, %rsp
	movq	%rsp, %rax
	movq	-96(%rbp), %rcx
	movq	-88(%rbp), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	-80(%rbp), %rcx
	movq	-72(%rbp), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	-64(%rbp), %rcx
	movq	-56(%rbp), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	-48(%rbp), %rcx
	movq	%rcx, 48(%rax)
	movl	-40(%rbp), %ecx
	movl	%ecx, 56(%rax)
	movq	%rdx, %rdi
	call	write_register
	addq	$64, %rsp
	.loc 1 201 16
	jmp	.L28
.L31:
	.loc 1 214 1
	call	__stack_chk_fail@PLT
.L29:
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE13:
	.size	write_entries, .-write_entries
	.globl	read_entries
	.type	read_entries, @function
read_entries:
.LFB14:
	.loc 1 218 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$152, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -152(%rbp)
	movl	%esi, -156(%rbp)
	.loc 1 218 1
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	.loc 1 221 9
	movl	$0, -132(%rbp)
	.loc 1 227 17
	movq	-152(%rbp), %rax
	movq	%rax, %rdi
	call	file_check_size
	movq	%rax, -128(%rbp)
	.loc 1 237 10
	movq	-128(%rbp), %rax
	testq	%rax, %rax
	js	.L33
	cvtsi2ssq	%rax, %xmm0
	jmp	.L34
.L33:
	movq	%rax, %rdx
	shrq	%rdx
	andl	$1, %eax
	orq	%rax, %rdx
	cvtsi2ssq	%rdx, %xmm0
	addss	%xmm0, %xmm0
.L34:
	movss	.LC11(%rip), %xmm1
	divss	%xmm1, %xmm0
	.loc 1 237 4
	cvttss2sil	%xmm0, %eax
	movslq	%eax, %rdx
	.loc 1 236 57
	movq	%rdx, %rax
	salq	$4, %rax
	subq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	.loc 1 237 20
	movl	-156(%rbp), %eax
	cltq
	.loc 1 236 32
	cmpq	%rax, %rdx
	jbe	.L35
	.loc 1 237 38 discriminator 1
	movq	-128(%rbp), %rax
	testq	%rax, %rax
	js	.L36
	cvtsi2ssq	%rax, %xmm0
	jmp	.L37
.L36:
	movq	%rax, %rdx
	shrq	%rdx
	andl	$1, %eax
	orq	%rax, %rdx
	cvtsi2ssq	%rdx, %xmm0
	addss	%xmm0, %xmm0
.L37:
	movss	.LC11(%rip), %xmm1
	divss	%xmm1, %xmm0
	.loc 1 237 32 discriminator 1
	cvttss2sil	%xmm0, %eax
	.loc 1 236 32 discriminator 1
	cltq
	jmp	.L38
.L35:
	.loc 1 236 32 is_stmt 0 discriminator 2
	movl	-156(%rbp), %eax
	cltq
.L38:
	.loc 1 236 32 discriminator 4
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, -120(%rbp)
	.loc 1 240 7 is_stmt 1 discriminator 4
	cmpl	$0, -156(%rbp)
	je	.L39
	.loc 1 241 34
	movq	-128(%rbp), %rax
	testq	%rax, %rax
	js	.L40
	cvtsi2ssq	%rax, %xmm0
	jmp	.L41
.L40:
	movq	%rax, %rdx
	shrq	%rdx
	andl	$1, %eax
	orq	%rax, %rdx
	cvtsi2ssq	%rdx, %xmm0
	addss	%xmm0, %xmm0
.L41:
	movss	.LC11(%rip), %xmm1
	divss	%xmm1, %xmm0
	.loc 1 241 29
	cvttss2sil	%xmm0, %eax
	.loc 1 241 17
	cmpl	%eax, -156(%rbp)
	cmovle	-156(%rbp), %eax
	movl	%eax, -156(%rbp)
	jmp	.L45
.L39:
	.loc 1 242 25
	movq	-128(%rbp), %rax
	testq	%rax, %rax
	js	.L43
	cvtsi2ssq	%rax, %xmm0
	jmp	.L44
.L43:
	movq	%rax, %rdx
	shrq	%rdx
	andl	$1, %eax
	orq	%rax, %rdx
	cvtsi2ssq	%rdx, %xmm0
	addss	%xmm0, %xmm0
.L44:
	movss	.LC11(%rip), %xmm1
	divss	%xmm1, %xmm0
	.loc 1 242 18
	cvttss2sil	%xmm0, %eax
	movl	%eax, -156(%rbp)
	.loc 1 247 10
	jmp	.L45
.L47:
	.loc 1 249 9
	leaq	-96(%rbp), %rax
	movq	-152(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	read_register
	.loc 1 252 14
	movl	-132(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$4, %rax
	subq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	movq	-120(%rbp), %rax
	addq	%rdx, %rax
	.loc 1 252 22
	movq	-96(%rbp), %rcx
	movq	-88(%rbp), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	-80(%rbp), %rcx
	movq	-72(%rbp), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	-64(%rbp), %rcx
	movq	-56(%rbp), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	-48(%rbp), %rdx
	movq	%rdx, 48(%rax)
	movl	-40(%rbp), %edx
	movl	%edx, 56(%rax)
	.loc 1 253 7
	addl	$1, -132(%rbp)
.L45:
	.loc 1 247 11
	movq	-152(%rbp), %rax
	movq	%rax, %rdi
	call	feof@PLT
	.loc 1 247 10
	cmpl	$-1, %eax
	je	.L46
	.loc 1 247 27 discriminator 1
	movl	-132(%rbp), %eax
	cmpl	-156(%rbp), %eax
	jl	.L47
.L46:
	.loc 1 257 18
	movq	-120(%rbp), %rax
	movq	%rax, -112(%rbp)
	.loc 1 258 18
	movl	-132(%rbp), %eax
	cltq
	movq	%rax, -104(%rbp)
	.loc 1 262 12
	movq	-112(%rbp), %rax
	movq	-104(%rbp), %rdx
	.loc 1 263 1
	movq	-24(%rbp), %rbx
	xorq	%fs:40, %rbx
	je	.L49
	call	__stack_chk_fail@PLT
.L49:
	addq	$152, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE14:
	.size	read_entries, .-read_entries
	.section	.rodata
.LC12:
	.string	"\n#%d\n"
	.text
	.globl	print_registers
	.type	print_registers, @function
print_registers:
.LFB15:
	.loc 1 267 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$40, %rsp
	.cfi_offset 3, -24
	movq	%rdi, %rax
	movq	%rsi, %rcx
	movq	%rcx, %rdx
	movq	%rax, -48(%rbp)
	movq	%rdx, -40(%rbp)
.LBB2:
	.loc 1 268 13
	movl	$0, -20(%rbp)
	.loc 1 268 5
	jmp	.L51
.L52:
	.loc 1 270 2 discriminator 3
	movl	-20(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC12(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	.loc 1 271 46 discriminator 3
	movq	-48(%rbp), %rcx
	.loc 1 271 52 discriminator 3
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$4, %rax
	subq	%rdx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	.loc 1 271 2 discriminator 3
	subq	$64, %rsp
	movq	%rsp, %rdx
	movq	(%rax), %rcx
	movq	8(%rax), %rbx
	movq	%rcx, (%rdx)
	movq	%rbx, 8(%rdx)
	movq	16(%rax), %rcx
	movq	24(%rax), %rbx
	movq	%rcx, 16(%rdx)
	movq	%rbx, 24(%rdx)
	movq	32(%rax), %rcx
	movq	40(%rax), %rbx
	movq	%rcx, 32(%rdx)
	movq	%rbx, 40(%rdx)
	movq	48(%rax), %rcx
	movq	%rcx, 48(%rdx)
	movl	56(%rax), %eax
	movl	%eax, 56(%rdx)
	call	output_register
	addq	$64, %rsp
	.loc 1 268 47 discriminator 3
	addl	$1, -20(%rbp)
.L51:
	.loc 1 268 23 discriminator 1
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	.loc 1 268 38 discriminator 1
	movq	-40(%rbp), %rax
	.loc 1 268 5 discriminator 1
	cmpq	%rax, %rdx
	jb	.L52
.LBE2:
	.loc 1 273 5
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	clear_vec
	.loc 1 274 1
	nop
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE15:
	.size	print_registers, .-print_registers
	.globl	file_check_size
	.type	file_check_size, @function
file_check_size:
.LFB16:
	.loc 1 280 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -56(%rbp)
	.loc 1 280 1
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	.loc 1 286 5
	leaq	-32(%rbp), %rdx
	movq	-56(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	fgetpos@PLT
	.loc 1 287 5
	movq	-56(%rbp), %rax
	movl	$0, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	fseek@PLT
.L54:
	.loc 1 290 2 discriminator 1
	movq	-56(%rbp), %rdx
	leaq	-41(%rbp), %rax
	movq	%rdx, %rcx
	movl	$1, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	.loc 1 293 13 discriminator 1
	movq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	feof@PLT
	.loc 1 293 5 discriminator 1
	testl	%eax, %eax
	je	.L54
	.loc 1 294 12
	movq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	ftell@PLT
	.loc 1 294 10
	movq	%rax, -40(%rbp)
	.loc 1 296 5
	leaq	-32(%rbp), %rdx
	movq	-56(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	fsetpos@PLT
	.loc 1 298 12
	movq	-40(%rbp), %rax
	.loc 1 299 1
	movq	-8(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L56
	call	__stack_chk_fail@PLT
.L56:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE16:
	.size	file_check_size, .-file_check_size
	.globl	get_barcode
	.type	get_barcode, @function
get_barcode:
.LFB17:
	.loc 1 303 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -56(%rbp)
	.loc 1 303 1
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	.loc 1 304 10
	movq	$0, -22(%rbp)
	movl	$0, -14(%rbp)
	movw	$0, -10(%rbp)
.LBB3:
	.loc 1 307 14
	movl	$0, -36(%rbp)
	.loc 1 307 5
	jmp	.L58
.L59:
	.loc 1 307 69 discriminator 3
	movl	-36(%rbp), %eax
	movslq	%eax, %rdx
	movq	-56(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %edx
	.loc 1 307 52 discriminator 3
	movl	-36(%rbp), %eax
	cltq
	movb	%dl, -22(%rbp,%rax)
	.loc 1 307 30 discriminator 3
	addl	$1, -36(%rbp)
.L58:
	.loc 1 307 5 discriminator 1
	cmpl	$12, -36(%rbp)
	jle	.L59
.LBE3:
	.loc 1 309 14
	leaq	-22(%rbp), %rax
	movq	%rax, -32(%rbp)
	.loc 1 311 12
	movq	-32(%rbp), %rax
	.loc 1 312 1
	movq	-8(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L61
	call	__stack_chk_fail@PLT
.L61:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE17:
	.size	get_barcode, .-get_barcode
	.section	.rodata
	.align 4
.LC10:
	.long	3212836864
	.align 4
.LC11:
	.long	1113849856
	.text
.Letext0:
	.file 2 "/usr/lib/gcc/x86_64-pc-linux-gnu/9.2.1/include/stddef.h"
	.file 3 "/usr/include/bits/types.h"
	.file 4 "/usr/include/bits/types/__mbstate_t.h"
	.file 5 "/usr/include/bits/types/__fpos_t.h"
	.file 6 "/usr/include/bits/types/struct_FILE.h"
	.file 7 "/usr/include/bits/types/FILE.h"
	.file 8 "/usr/include/stdio.h"
	.file 9 "/usr/include/bits/sys_errlist.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0x8bb
	.value	0x4
	.long	.Ldebug_abbrev0
	.byte	0x8
	.uleb128 0x1
	.long	.LASF108
	.byte	0xc
	.long	.LASF109
	.long	.LASF110
	.quad	.Ltext0
	.quad	.Letext0-.Ltext0
	.long	.Ldebug_line0
	.uleb128 0x2
	.long	.LASF7
	.byte	0x2
	.byte	0xd1
	.byte	0x17
	.long	0x39
	.uleb128 0x3
	.byte	0x8
	.byte	0x7
	.long	.LASF0
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.long	.LASF1
	.uleb128 0x4
	.byte	0x8
	.uleb128 0x3
	.byte	0x1
	.byte	0x8
	.long	.LASF2
	.uleb128 0x3
	.byte	0x2
	.byte	0x7
	.long	.LASF3
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.long	.LASF4
	.uleb128 0x3
	.byte	0x2
	.byte	0x5
	.long	.LASF5
	.uleb128 0x5
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x3
	.byte	0x8
	.byte	0x5
	.long	.LASF6
	.uleb128 0x2
	.long	.LASF8
	.byte	0x3
	.byte	0x98
	.byte	0x19
	.long	0x6c
	.uleb128 0x2
	.long	.LASF9
	.byte	0x3
	.byte	0x99
	.byte	0x1b
	.long	0x6c
	.uleb128 0x6
	.byte	0x8
	.long	0x91
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.long	.LASF10
	.uleb128 0x7
	.long	0x91
	.uleb128 0x8
	.byte	0x4
	.byte	0x4
	.byte	0x10
	.byte	0x3
	.long	0xbf
	.uleb128 0x9
	.long	.LASF11
	.byte	0x4
	.byte	0x12
	.byte	0x13
	.long	0x40
	.uleb128 0x9
	.long	.LASF12
	.byte	0x4
	.byte	0x13
	.byte	0xa
	.long	0xbf
	.byte	0
	.uleb128 0xa
	.long	0x91
	.long	0xcf
	.uleb128 0xb
	.long	0x39
	.byte	0x3
	.byte	0
	.uleb128 0xc
	.byte	0x8
	.byte	0x4
	.byte	0xd
	.byte	0x9
	.long	0xf3
	.uleb128 0xd
	.long	.LASF13
	.byte	0x4
	.byte	0xf
	.byte	0x7
	.long	0x65
	.byte	0
	.uleb128 0xd
	.long	.LASF14
	.byte	0x4
	.byte	0x14
	.byte	0x5
	.long	0x9d
	.byte	0x4
	.byte	0
	.uleb128 0x2
	.long	.LASF15
	.byte	0x4
	.byte	0x15
	.byte	0x3
	.long	0xcf
	.uleb128 0xe
	.long	.LASF19
	.byte	0x10
	.byte	0x5
	.byte	0xa
	.byte	0x10
	.long	0x127
	.uleb128 0xd
	.long	.LASF16
	.byte	0x5
	.byte	0xc
	.byte	0xb
	.long	0x73
	.byte	0
	.uleb128 0xd
	.long	.LASF17
	.byte	0x5
	.byte	0xd
	.byte	0xf
	.long	0xf3
	.byte	0x8
	.byte	0
	.uleb128 0x2
	.long	.LASF18
	.byte	0x5
	.byte	0xe
	.byte	0x3
	.long	0xff
	.uleb128 0xe
	.long	.LASF20
	.byte	0xd8
	.byte	0x6
	.byte	0x31
	.byte	0x8
	.long	0x2ba
	.uleb128 0xd
	.long	.LASF21
	.byte	0x6
	.byte	0x33
	.byte	0x7
	.long	0x65
	.byte	0
	.uleb128 0xd
	.long	.LASF22
	.byte	0x6
	.byte	0x36
	.byte	0x9
	.long	0x8b
	.byte	0x8
	.uleb128 0xd
	.long	.LASF23
	.byte	0x6
	.byte	0x37
	.byte	0x9
	.long	0x8b
	.byte	0x10
	.uleb128 0xd
	.long	.LASF24
	.byte	0x6
	.byte	0x38
	.byte	0x9
	.long	0x8b
	.byte	0x18
	.uleb128 0xd
	.long	.LASF25
	.byte	0x6
	.byte	0x39
	.byte	0x9
	.long	0x8b
	.byte	0x20
	.uleb128 0xd
	.long	.LASF26
	.byte	0x6
	.byte	0x3a
	.byte	0x9
	.long	0x8b
	.byte	0x28
	.uleb128 0xd
	.long	.LASF27
	.byte	0x6
	.byte	0x3b
	.byte	0x9
	.long	0x8b
	.byte	0x30
	.uleb128 0xd
	.long	.LASF28
	.byte	0x6
	.byte	0x3c
	.byte	0x9
	.long	0x8b
	.byte	0x38
	.uleb128 0xd
	.long	.LASF29
	.byte	0x6
	.byte	0x3d
	.byte	0x9
	.long	0x8b
	.byte	0x40
	.uleb128 0xd
	.long	.LASF30
	.byte	0x6
	.byte	0x40
	.byte	0x9
	.long	0x8b
	.byte	0x48
	.uleb128 0xd
	.long	.LASF31
	.byte	0x6
	.byte	0x41
	.byte	0x9
	.long	0x8b
	.byte	0x50
	.uleb128 0xd
	.long	.LASF32
	.byte	0x6
	.byte	0x42
	.byte	0x9
	.long	0x8b
	.byte	0x58
	.uleb128 0xd
	.long	.LASF33
	.byte	0x6
	.byte	0x44
	.byte	0x16
	.long	0x2d3
	.byte	0x60
	.uleb128 0xd
	.long	.LASF34
	.byte	0x6
	.byte	0x46
	.byte	0x14
	.long	0x2d9
	.byte	0x68
	.uleb128 0xd
	.long	.LASF35
	.byte	0x6
	.byte	0x48
	.byte	0x7
	.long	0x65
	.byte	0x70
	.uleb128 0xd
	.long	.LASF36
	.byte	0x6
	.byte	0x49
	.byte	0x7
	.long	0x65
	.byte	0x74
	.uleb128 0xd
	.long	.LASF37
	.byte	0x6
	.byte	0x4a
	.byte	0xb
	.long	0x73
	.byte	0x78
	.uleb128 0xd
	.long	.LASF38
	.byte	0x6
	.byte	0x4d
	.byte	0x12
	.long	0x50
	.byte	0x80
	.uleb128 0xd
	.long	.LASF39
	.byte	0x6
	.byte	0x4e
	.byte	0xf
	.long	0x57
	.byte	0x82
	.uleb128 0xd
	.long	.LASF40
	.byte	0x6
	.byte	0x4f
	.byte	0x8
	.long	0x2df
	.byte	0x83
	.uleb128 0xd
	.long	.LASF41
	.byte	0x6
	.byte	0x51
	.byte	0xf
	.long	0x2ef
	.byte	0x88
	.uleb128 0xd
	.long	.LASF42
	.byte	0x6
	.byte	0x59
	.byte	0xd
	.long	0x7f
	.byte	0x90
	.uleb128 0xd
	.long	.LASF43
	.byte	0x6
	.byte	0x5b
	.byte	0x17
	.long	0x2fa
	.byte	0x98
	.uleb128 0xd
	.long	.LASF44
	.byte	0x6
	.byte	0x5c
	.byte	0x19
	.long	0x305
	.byte	0xa0
	.uleb128 0xd
	.long	.LASF45
	.byte	0x6
	.byte	0x5d
	.byte	0x14
	.long	0x2d9
	.byte	0xa8
	.uleb128 0xd
	.long	.LASF46
	.byte	0x6
	.byte	0x5e
	.byte	0x9
	.long	0x47
	.byte	0xb0
	.uleb128 0xd
	.long	.LASF47
	.byte	0x6
	.byte	0x5f
	.byte	0xa
	.long	0x2d
	.byte	0xb8
	.uleb128 0xd
	.long	.LASF48
	.byte	0x6
	.byte	0x60
	.byte	0x7
	.long	0x65
	.byte	0xc0
	.uleb128 0xd
	.long	.LASF49
	.byte	0x6
	.byte	0x62
	.byte	0x8
	.long	0x30b
	.byte	0xc4
	.byte	0
	.uleb128 0x2
	.long	.LASF50
	.byte	0x7
	.byte	0x7
	.byte	0x19
	.long	0x133
	.uleb128 0xf
	.long	.LASF111
	.byte	0x6
	.byte	0x2b
	.byte	0xe
	.uleb128 0x10
	.long	.LASF51
	.uleb128 0x6
	.byte	0x8
	.long	0x2ce
	.uleb128 0x6
	.byte	0x8
	.long	0x133
	.uleb128 0xa
	.long	0x91
	.long	0x2ef
	.uleb128 0xb
	.long	0x39
	.byte	0
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x2c6
	.uleb128 0x10
	.long	.LASF52
	.uleb128 0x6
	.byte	0x8
	.long	0x2f5
	.uleb128 0x10
	.long	.LASF53
	.uleb128 0x6
	.byte	0x8
	.long	0x300
	.uleb128 0xa
	.long	0x91
	.long	0x31b
	.uleb128 0xb
	.long	0x39
	.byte	0x13
	.byte	0
	.uleb128 0x2
	.long	.LASF54
	.byte	0x8
	.byte	0x54
	.byte	0x12
	.long	0x127
	.uleb128 0x11
	.long	.LASF55
	.byte	0x8
	.byte	0x89
	.byte	0xe
	.long	0x333
	.uleb128 0x6
	.byte	0x8
	.long	0x2ba
	.uleb128 0x11
	.long	.LASF56
	.byte	0x8
	.byte	0x8a
	.byte	0xe
	.long	0x333
	.uleb128 0x11
	.long	.LASF57
	.byte	0x8
	.byte	0x8b
	.byte	0xe
	.long	0x333
	.uleb128 0x11
	.long	.LASF58
	.byte	0x9
	.byte	0x1a
	.byte	0xc
	.long	0x65
	.uleb128 0xa
	.long	0x373
	.long	0x368
	.uleb128 0x12
	.byte	0
	.uleb128 0x7
	.long	0x35d
	.uleb128 0x6
	.byte	0x8
	.long	0x98
	.uleb128 0x7
	.long	0x36d
	.uleb128 0x11
	.long	.LASF59
	.byte	0x9
	.byte	0x1b
	.byte	0x1a
	.long	0x368
	.uleb128 0x3
	.byte	0x8
	.byte	0x5
	.long	.LASF60
	.uleb128 0x3
	.byte	0x8
	.byte	0x7
	.long	.LASF61
	.uleb128 0x13
	.long	.LASF62
	.byte	0x1
	.byte	0x6
	.byte	0xd
	.long	0x36d
	.uleb128 0x9
	.byte	0x3
	.quad	FORMAT_STR
	.uleb128 0xe
	.long	.LASF63
	.byte	0x3c
	.byte	0x1
	.byte	0x18
	.byte	0x10
	.long	0x3ea
	.uleb128 0xd
	.long	.LASF64
	.byte	0x1
	.byte	0x1a
	.byte	0xa
	.long	0x30b
	.byte	0
	.uleb128 0xd
	.long	.LASF65
	.byte	0x1
	.byte	0x1b
	.byte	0xa
	.long	0x30b
	.byte	0x14
	.uleb128 0xd
	.long	.LASF66
	.byte	0x1
	.byte	0x1c
	.byte	0xa
	.long	0x3ea
	.byte	0x28
	.uleb128 0xd
	.long	.LASF67
	.byte	0x1
	.byte	0x1d
	.byte	0xe
	.long	0x3fa
	.byte	0x38
	.byte	0
	.uleb128 0xa
	.long	0x91
	.long	0x3fa
	.uleb128 0xb
	.long	0x39
	.byte	0xc
	.byte	0
	.uleb128 0x3
	.byte	0x4
	.byte	0x4
	.long	.LASF68
	.uleb128 0x2
	.long	.LASF69
	.byte	0x1
	.byte	0x1e
	.byte	0x3
	.long	0x3a8
	.uleb128 0xe
	.long	.LASF70
	.byte	0x10
	.byte	0x1
	.byte	0x21
	.byte	0x10
	.long	0x435
	.uleb128 0xd
	.long	.LASF71
	.byte	0x1
	.byte	0x23
	.byte	0xc
	.long	0x47
	.byte	0
	.uleb128 0xd
	.long	.LASF72
	.byte	0x1
	.byte	0x24
	.byte	0xc
	.long	0x2d
	.byte	0x8
	.byte	0
	.uleb128 0x2
	.long	.LASF73
	.byte	0x1
	.byte	0x25
	.byte	0x3
	.long	0x40d
	.uleb128 0x14
	.long	.LASF112
	.byte	0x7
	.byte	0x4
	.long	0x40
	.byte	0x1
	.byte	0x28
	.byte	0xe
	.long	0x466
	.uleb128 0x15
	.long	.LASF74
	.byte	0
	.uleb128 0x15
	.long	.LASF75
	.byte	0x1
	.uleb128 0x15
	.long	.LASF76
	.byte	0x2
	.byte	0
	.uleb128 0x2
	.long	.LASF77
	.byte	0x1
	.byte	0x2d
	.byte	0x3
	.long	0x441
	.uleb128 0x16
	.long	.LASF80
	.byte	0x1
	.value	0x12e
	.byte	0x7
	.long	0x8b
	.quad	.LFB17
	.quad	.LFE17-.LFB17
	.uleb128 0x1
	.byte	0x9c
	.long	0x4e7
	.uleb128 0x17
	.long	.LASF82
	.byte	0x1
	.value	0x12e
	.byte	0x19
	.long	0x8b
	.uleb128 0x3
	.byte	0x91
	.sleb128 -72
	.uleb128 0x18
	.long	.LASF78
	.byte	0x1
	.value	0x130
	.byte	0xa
	.long	0x4e7
	.uleb128 0x2
	.byte	0x91
	.sleb128 -38
	.uleb128 0x18
	.long	.LASF79
	.byte	0x1
	.value	0x131
	.byte	0xb
	.long	0x8b
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x19
	.quad	.LBB3
	.quad	.LBE3-.LBB3
	.uleb128 0x1a
	.string	"i"
	.byte	0x1
	.value	0x133
	.byte	0xe
	.long	0x65
	.uleb128 0x2
	.byte	0x91
	.sleb128 -52
	.byte	0
	.byte	0
	.uleb128 0xa
	.long	0x91
	.long	0x4f7
	.uleb128 0xb
	.long	0x39
	.byte	0xd
	.byte	0
	.uleb128 0x16
	.long	.LASF81
	.byte	0x1
	.value	0x117
	.byte	0x8
	.long	0x2d
	.quad	.LFB16
	.quad	.LFE16-.LFB16
	.uleb128 0x1
	.byte	0x9c
	.long	0x55b
	.uleb128 0x1b
	.string	"fp"
	.byte	0x1
	.value	0x117
	.byte	0x1e
	.long	0x333
	.uleb128 0x3
	.byte	0x91
	.sleb128 -72
	.uleb128 0x18
	.long	.LASF72
	.byte	0x1
	.value	0x119
	.byte	0xc
	.long	0x2d
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x18
	.long	.LASF83
	.byte	0x1
	.value	0x11a
	.byte	0xc
	.long	0x31b
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x18
	.long	.LASF84
	.byte	0x1
	.value	0x11b
	.byte	0x13
	.long	0x49
	.uleb128 0x2
	.byte	0x91
	.sleb128 -57
	.byte	0
	.uleb128 0x1c
	.long	.LASF94
	.byte	0x1
	.value	0x10a
	.byte	0x6
	.quad	.LFB15
	.quad	.LFE15-.LFB15
	.uleb128 0x1
	.byte	0x9c
	.long	0x5ab
	.uleb128 0x17
	.long	.LASF85
	.byte	0x1
	.value	0x10a
	.byte	0x1d
	.long	0x435
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0x19
	.quad	.LBB2
	.quad	.LBE2-.LBB2
	.uleb128 0x1a
	.string	"i"
	.byte	0x1
	.value	0x10c
	.byte	0xd
	.long	0x65
	.uleb128 0x2
	.byte	0x91
	.sleb128 -36
	.byte	0
	.byte	0
	.uleb128 0x1d
	.long	.LASF86
	.byte	0x1
	.byte	0xd9
	.byte	0x8
	.long	0x435
	.quad	.LFB14
	.quad	.LFE14-.LFB14
	.uleb128 0x1
	.byte	0x9c
	.long	0x63d
	.uleb128 0x1e
	.string	"fp"
	.byte	0x1
	.byte	0xd9
	.byte	0x1b
	.long	0x333
	.uleb128 0x3
	.byte	0x91
	.sleb128 -168
	.uleb128 0x1f
	.long	.LASF87
	.byte	0x1
	.byte	0xd9
	.byte	0x23
	.long	0x65
	.uleb128 0x3
	.byte	0x91
	.sleb128 -172
	.uleb128 0x20
	.long	.LASF88
	.byte	0x1
	.byte	0xdb
	.byte	0xc
	.long	0x435
	.uleb128 0x3
	.byte	0x91
	.sleb128 -128
	.uleb128 0x20
	.long	.LASF89
	.byte	0x1
	.byte	0xdc
	.byte	0xf
	.long	0x63d
	.uleb128 0x3
	.byte	0x91
	.sleb128 -136
	.uleb128 0x20
	.long	.LASF90
	.byte	0x1
	.byte	0xdd
	.byte	0x9
	.long	0x65
	.uleb128 0x3
	.byte	0x91
	.sleb128 -148
	.uleb128 0x20
	.long	.LASF91
	.byte	0x1
	.byte	0xdf
	.byte	0xc
	.long	0x2d
	.uleb128 0x3
	.byte	0x91
	.sleb128 -144
	.uleb128 0x20
	.long	.LASF84
	.byte	0x1
	.byte	0xf5
	.byte	0xe
	.long	0x401
	.uleb128 0x3
	.byte	0x91
	.sleb128 -112
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x401
	.uleb128 0x1d
	.long	.LASF92
	.byte	0x1
	.byte	0xc3
	.byte	0x5
	.long	0x65
	.quad	.LFB13
	.quad	.LFE13-.LFB13
	.uleb128 0x1
	.byte	0x9c
	.long	0x685
	.uleb128 0x1e
	.string	"fp"
	.byte	0x1
	.byte	0xc3
	.byte	0x19
	.long	0x333
	.uleb128 0x3
	.byte	0x91
	.sleb128 -120
	.uleb128 0x20
	.long	.LASF93
	.byte	0x1
	.byte	0xc5
	.byte	0xe
	.long	0x401
	.uleb128 0x3
	.byte	0x91
	.sleb128 -112
	.byte	0
	.uleb128 0x21
	.long	.LASF95
	.byte	0x1
	.byte	0xad
	.byte	0x6
	.quad	.LFB12
	.quad	.LFE12-.LFB12
	.uleb128 0x1
	.byte	0x9c
	.long	0x6f2
	.uleb128 0x1f
	.long	.LASF93
	.byte	0x1
	.byte	0xad
	.byte	0x1f
	.long	0x401
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x20
	.long	.LASF96
	.byte	0x1
	.byte	0xaf
	.byte	0xa
	.long	0x6f2
	.uleb128 0x3
	.byte	0x91
	.sleb128 -80
	.uleb128 0x20
	.long	.LASF97
	.byte	0x1
	.byte	0xb0
	.byte	0xa
	.long	0x6f2
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x20
	.long	.LASF98
	.byte	0x1
	.byte	0xb1
	.byte	0xa
	.long	0x4e7
	.uleb128 0x3
	.byte	0x91
	.sleb128 -94
	.uleb128 0x20
	.long	.LASF99
	.byte	0x1
	.byte	0xb2
	.byte	0xb
	.long	0x3fa
	.uleb128 0x3
	.byte	0x91
	.sleb128 -100
	.byte	0
	.uleb128 0xa
	.long	0x91
	.long	0x702
	.uleb128 0xb
	.long	0x39
	.byte	0x14
	.byte	0
	.uleb128 0x22
	.long	.LASF100
	.byte	0x1
	.byte	0x98
	.byte	0xa
	.long	0x401
	.quad	.LFB11
	.quad	.LFE11-.LFB11
	.uleb128 0x1
	.byte	0x9c
	.long	0x774
	.uleb128 0x20
	.long	.LASF93
	.byte	0x1
	.byte	0x9a
	.byte	0xe
	.long	0x401
	.uleb128 0x3
	.byte	0x91
	.sleb128 -192
	.uleb128 0x20
	.long	.LASF96
	.byte	0x1
	.byte	0x9b
	.byte	0xa
	.long	0x6f2
	.uleb128 0x3
	.byte	0x91
	.sleb128 -128
	.uleb128 0x20
	.long	.LASF97
	.byte	0x1
	.byte	0x9c
	.byte	0xa
	.long	0x6f2
	.uleb128 0x3
	.byte	0x91
	.sleb128 -96
	.uleb128 0x20
	.long	.LASF98
	.byte	0x1
	.byte	0x9d
	.byte	0xa
	.long	0x6f2
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0x20
	.long	.LASF99
	.byte	0x1
	.byte	0x9e
	.byte	0xb
	.long	0x3fa
	.uleb128 0x3
	.byte	0x91
	.sleb128 -196
	.byte	0
	.uleb128 0x1d
	.long	.LASF101
	.byte	0x1
	.byte	0x87
	.byte	0xa
	.long	0x401
	.quad	.LFB10
	.quad	.LFE10-.LFB10
	.uleb128 0x1
	.byte	0x9c
	.long	0x7b6
	.uleb128 0x1e
	.string	"fp"
	.byte	0x1
	.byte	0x87
	.byte	0x1e
	.long	0x333
	.uleb128 0x3
	.byte	0x91
	.sleb128 -128
	.uleb128 0x20
	.long	.LASF93
	.byte	0x1
	.byte	0x89
	.byte	0xe
	.long	0x401
	.uleb128 0x3
	.byte	0x91
	.sleb128 -112
	.byte	0
	.uleb128 0x21
	.long	.LASF102
	.byte	0x1
	.byte	0x7e
	.byte	0x6
	.quad	.LFB9
	.quad	.LFE9-.LFB9
	.uleb128 0x1
	.byte	0x9c
	.long	0x7f2
	.uleb128 0x1e
	.string	"fp"
	.byte	0x1
	.byte	0x7e
	.byte	0x1b
	.long	0x333
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x1f
	.long	.LASF93
	.byte	0x1
	.byte	0x7e
	.byte	0x28
	.long	0x401
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.byte	0
	.uleb128 0x22
	.long	.LASF103
	.byte	0x1
	.byte	0x55
	.byte	0x5
	.long	0x65
	.quad	.LFB8
	.quad	.LFE8-.LFB8
	.uleb128 0x1
	.byte	0x9c
	.long	0x84f
	.uleb128 0x23
	.string	"fp"
	.byte	0x1
	.byte	0x57
	.byte	0xb
	.long	0x333
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x23
	.string	"op"
	.byte	0x1
	.byte	0x58
	.byte	0xf
	.long	0x466
	.uleb128 0x2
	.byte	0x91
	.sleb128 -44
	.uleb128 0x20
	.long	.LASF104
	.byte	0x1
	.byte	0x59
	.byte	0xc
	.long	0x435
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x20
	.long	.LASF105
	.byte	0x1
	.byte	0x5a
	.byte	0xa
	.long	0x91
	.uleb128 0x2
	.byte	0x91
	.sleb128 -45
	.byte	0
	.uleb128 0x21
	.long	.LASF106
	.byte	0x1
	.byte	0x3a
	.byte	0x6
	.quad	.LFB7
	.quad	.LFE7-.LFB7
	.uleb128 0x1
	.byte	0x9c
	.long	0x87d
	.uleb128 0x1f
	.long	.LASF107
	.byte	0x1
	.byte	0x3a
	.byte	0x18
	.long	0x87d
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x435
	.uleb128 0x24
	.long	.LASF113
	.byte	0x1
	.byte	0x30
	.byte	0xb
	.long	0x466
	.quad	.LFB6
	.quad	.LFE6-.LFB6
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x23
	.string	"op"
	.byte	0x1
	.byte	0x32
	.byte	0xf
	.long	0x466
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.uleb128 0x23
	.string	"in"
	.byte	0x1
	.byte	0x33
	.byte	0x12
	.long	0x40
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.byte	0
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x10
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0x17
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x13
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0x13
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0x21
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x14
	.uleb128 0x4
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x16
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2116
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x17
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x18
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x19
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.byte	0
	.byte	0
	.uleb128 0x1a
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x1b
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x1c
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2116
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1d
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2116
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1e
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x1f
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x20
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x21
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2116
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x22
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2116
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x23
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x24
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2116
	.uleb128 0x19
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_aranges,"",@progbits
	.long	0x2c
	.value	0x2
	.long	.Ldebug_info0
	.byte	0x8
	.byte	0
	.value	0
	.value	0
	.quad	.Ltext0
	.quad	.Letext0-.Ltext0
	.quad	0
	.quad	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF8:
	.string	"__off_t"
.LASF112:
	.string	"_operation"
.LASF22:
	.string	"_IO_read_ptr"
.LASF34:
	.string	"_chain"
.LASF7:
	.string	"size_t"
.LASF63:
	.string	"_register"
.LASF77:
	.string	"OPERATION"
.LASF40:
	.string	"_shortbuf"
.LASF82:
	.string	"barcode_address"
.LASF28:
	.string	"_IO_buf_base"
.LASF61:
	.string	"long long unsigned int"
.LASF73:
	.string	"VECTOR"
.LASF75:
	.string	"READ_ENTRIES"
.LASF113:
	.string	"input_operation"
.LASF15:
	.string	"__mbstate_t"
.LASF81:
	.string	"file_check_size"
.LASF83:
	.string	"save_state"
.LASF43:
	.string	"_codecvt"
.LASF60:
	.string	"long long int"
.LASF4:
	.string	"signed char"
.LASF80:
	.string	"get_barcode"
.LASF35:
	.string	"_fileno"
.LASF78:
	.string	"barcode_string"
.LASF23:
	.string	"_IO_read_end"
.LASF84:
	.string	"temp"
.LASF6:
	.string	"long int"
.LASF88:
	.string	"ret_vec"
.LASF21:
	.string	"_flags"
.LASF29:
	.string	"_IO_buf_end"
.LASF38:
	.string	"_cur_column"
.LASF52:
	.string	"_IO_codecvt"
.LASF104:
	.string	"data_holder"
.LASF37:
	.string	"_old_offset"
.LASF42:
	.string	"_offset"
.LASF103:
	.string	"main"
.LASF19:
	.string	"_G_fpos_t"
.LASF100:
	.string	"input_register"
.LASF106:
	.string	"clear_vec"
.LASF16:
	.string	"__pos"
.LASF107:
	.string	"this_vec"
.LASF66:
	.string	"barcode"
.LASF51:
	.string	"_IO_marker"
.LASF55:
	.string	"stdin"
.LASF1:
	.string	"unsigned int"
.LASF12:
	.string	"__wchb"
.LASF102:
	.string	"write_register"
.LASF0:
	.string	"long unsigned int"
.LASF26:
	.string	"_IO_write_ptr"
.LASF64:
	.string	"name"
.LASF58:
	.string	"sys_nerr"
.LASF101:
	.string	"read_register"
.LASF71:
	.string	"data"
.LASF72:
	.string	"size"
.LASF3:
	.string	"short unsigned int"
.LASF109:
	.string	"codigo.c"
.LASF30:
	.string	"_IO_save_base"
.LASF85:
	.string	"registers_vec"
.LASF11:
	.string	"__wch"
.LASF86:
	.string	"read_entries"
.LASF41:
	.string	"_lock"
.LASF36:
	.string	"_flags2"
.LASF48:
	.string	"_mode"
.LASF56:
	.string	"stdout"
.LASF87:
	.string	"n_first"
.LASF92:
	.string	"write_entries"
.LASF27:
	.string	"_IO_write_end"
.LASF70:
	.string	"_vector"
.LASF67:
	.string	"price"
.LASF111:
	.string	"_IO_lock_t"
.LASF20:
	.string	"_IO_FILE"
.LASF18:
	.string	"__fpos_t"
.LASF68:
	.string	"float"
.LASF59:
	.string	"sys_errlist"
.LASF95:
	.string	"output_register"
.LASF33:
	.string	"_markers"
.LASF17:
	.string	"__state"
.LASF65:
	.string	"brand"
.LASF2:
	.string	"unsigned char"
.LASF62:
	.string	"FORMAT_STR"
.LASF5:
	.string	"short int"
.LASF53:
	.string	"_IO_wide_data"
.LASF110:
	.string	"/home/hiram/Workspace/trabs_usp/arquivos/exercicios_2"
.LASF39:
	.string	"_vtable_offset"
.LASF105:
	.string	"STOP"
.LASF50:
	.string	"FILE"
.LASF76:
	.string	"stop"
.LASF99:
	.string	"tempPrice"
.LASF13:
	.string	"__count"
.LASF14:
	.string	"__value"
.LASF10:
	.string	"char"
.LASF90:
	.string	"index"
.LASF89:
	.string	"register_seq"
.LASF54:
	.string	"fpos_t"
.LASF69:
	.string	"REGISTER"
.LASF97:
	.string	"tempBrand"
.LASF98:
	.string	"tempBarcode"
.LASF9:
	.string	"__off64_t"
.LASF24:
	.string	"_IO_read_base"
.LASF32:
	.string	"_IO_save_end"
.LASF47:
	.string	"__pad5"
.LASF49:
	.string	"_unused2"
.LASF57:
	.string	"stderr"
.LASF108:
	.string	"GNU C17 9.2.1 20200130 -mtune=generic -march=x86-64 -g"
.LASF46:
	.string	"_freeres_buf"
.LASF31:
	.string	"_IO_backup_base"
.LASF93:
	.string	"this_register"
.LASF94:
	.string	"print_registers"
.LASF45:
	.string	"_freeres_list"
.LASF44:
	.string	"_wide_data"
.LASF74:
	.string	"WRITE_ENTRIES"
.LASF79:
	.string	"ret_addr"
.LASF25:
	.string	"_IO_write_base"
.LASF96:
	.string	"tempName"
.LASF91:
	.string	"file_size"
	.ident	"GCC: (Arch Linux 9.2.1+20200130-2) 9.2.1 20200130"
	.section	.note.GNU-stack,"",@progbits
