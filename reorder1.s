	.text
	.align 4,0x90
	.globl _foo
_foo:
LFB0:
	movq	_B@GOTPCREL(%rip), %rdx
	movq	_A@GOTPCREL(%rip), %rcx
	movl	(%rdx), %eax
	addl	$1, %eax
	movl	%eax, (%rcx)
	movl	$0, (%rdx)
	ret
LFE0:
	.comm	_B,4,2
	.comm	_A,4,2
	.section __TEXT,__eh_frame,coalesced,no_toc+strip_static_syms+live_support
EH_frame1:
	.set L$set$0,LECIE1-LSCIE1
	.long L$set$0
LSCIE1:
	.long	0
	.byte	0x1
	.ascii "zR\0"
	.byte	0x1
	.byte	0x78
	.byte	0x10
	.byte	0x1
	.byte	0x10
	.byte	0xc
	.byte	0x7
	.byte	0x8
	.byte	0x90
	.byte	0x1
	.align 3
LECIE1:
LSFDE1:
	.set L$set$1,LEFDE1-LASFDE1
	.long L$set$1
LASFDE1:
	.long	LASFDE1-EH_frame1
	.quad	LFB0-.
	.set L$set$2,LFE0-LFB0
	.quad L$set$2
	.byte	0
	.align 3
LEFDE1:
	.subsections_via_symbols
