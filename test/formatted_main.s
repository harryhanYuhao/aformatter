    .text 
    .file "main.c"
.globl	           format_strbuf_list# -- Begin function format_strbuf_list
.p2align	           4,          0x90
.type	           format_strbuf_list,@function
format_strbuf_list:#@format_strbuf_list
.cfi_startproc
%bb.0:
pushq       %rbp
.cfi_def_cfa_offset16
.cfi_offset%rbp,-16
movq        %rsp,       %rbp
.cfi_def_cfa_register%rbp
subq        $16,        %rsp
movq        %rdi,       -8(%rbp)
movq        -8(%rbp),   %rax
movq        (%rax),     %rax
movq        %rax,       -16(%rbp)
movq        -16(%rbp),  %rdi
callq       strip_initial_space
movq        -16(%rbp),  %rdi
callq       strip_trailing_space
movq        -16(%rbp),  %rdi
callq       strip_repetitive_linebreaks
movq        -16(%rbp),  %rdi
callq       strbuf_tokenisation
movq        -16(%rbp),  %rdi
callq       format_insert_spaces
addq        $16,        %rsp
popq        %rbp
.cfi_def_cfa%rsp,8
retq
.Lfunc_end0:
.sizeformat_strbuf_list,    .Lfunc_end0-format_strbuf_list
.cfi_endproc
# -- End function
.globltest#--Beginfunctiontest
.p2align4,0x90
.typetest,@function
test:#      @test
.cfi_startproc
# %bb.0:
pushq       %rbp
.cfi_def_cfa_offset16
.cfi_offset%rbp,-16
movq        %rsp,       %rbp
.cfi_def_cfa_register%rbp
subq        $48,        %rsp
movl        $10,        %edi
movl        $8,         %esi
callq       calloc
movq        %rax,       -8(%rbp)
movl        $0,         -12(%rbp)
.LBB1_1:#=>ThisInnerLoopHeader:Depth=1
cmpl        $10,        -12(%rbp)
jge             .LBB1_4
# %bb.2:                                #   in Loop: Header=BB1_1 Depth=1
leaq        -24(%rbp),  %rdi
callq       strbuf_init
movq        -24(%rbp),  %rdx
movq        -8(%rbp),   %rax
movslq      -12(%rbp),  %rcx
movq        %rdx,       (%rax,%rcx,8)
# %bb.3:                                #   in Loop: Header=BB1_1 Depth=1
movl        -12(%rbp),  %eax
addl        $1,         %eax
movl        %eax,       -12(%rbp)
jmp             .LBB1_1
.LBB1_4:
movl        $0,         -28(%rbp)
.LBB1_5:#=>ThisInnerLoopHeader:Depth=1
cmpl        $9,         -28(%rbp)
jge             .LBB1_8
# %bb.6:                                #   in Loop: Header=BB1_5 Depth=1
movq        -8(%rbp),   %rax
movl        -28(%rbp),  %ecx
addl        $1,         %ecx
movslq      %ecx,       %rcx
movq        (%rax,%rcx,8),%rcx
movq        -8(%rbp),   %rax
movslq      -28(%rbp),  %rdx
movq        (%rax,%rdx,8),%rax
movq        %rcx,       16(%rax)
# %bb.7:                                #   in Loop: Header=BB1_5 Depth=1
movl        -28(%rbp),  %eax
addl        $1,         %eax
movl        %eax,       -28(%rbp)
jmp             .LBB1_5
.LBB1_8:
movl        $0,         -32(%rbp)
.LBB1_9:#=>ThisInnerLoopHeader:Depth=1
cmpl        $10,        -32(%rbp)
jge             .LBB1_12
# %bb.10:                               #   in Loop: Header=BB1_9 Depth=1
movl        -32(%rbp),  %eax
addl        $40,        %eax
# kill: def $al killed $al killed $eax
movb        %al,        -33(%rbp)
movq        -8(%rbp),   %rax
movslq      -32(%rbp),  %rcx
movq        (%rax,%rcx,8),%rdi
leaq        -33(%rbp),  %rsi
movl        $1,         %edx
callq       strbuf_append
# %bb.11:                               #   in Loop: Header=BB1_9 Depth=1
movl        -32(%rbp),  %eax
addl        $1,         %eax
movl        %eax,       -32(%rbp)
jmp             .LBB1_9
.LBB1_12:
movq        -8(%rbp),   %rax
movq        (%rax),     %rdi
movl        $1,         %esi
callq       print_strbuf_list
addq        $48,        %rsp
popq        %rbp
.cfi_def_cfa%rsp,8
retq
.Lfunc_end1:
.sizetest,    .Lfunc_end1-test
.cfi_endproc
# -- End function
.globlinit#--Beginfunctioninit
.p2align4,0x90
.typeinit,@function
init:#      @init
.cfi_startproc
# %bb.0:
pushq       %rbp
.cfi_def_cfa_offset16
.cfi_offset%rbp,-16
movq        %rsp,       %rbp
.cfi_def_cfa_register%rbp
callq       init_global_variables
popq        %rbp
.cfi_def_cfa%rsp,8
retq
.Lfunc_end2:
.sizeinit,    .Lfunc_end2-init
.cfi_endproc
# -- End function
.globlcreate_backup#--Beginfunctioncreate_backup
.p2align4,0x90
.typecreate_backup,@function
create_backup:#@create_backup
.cfi_startproc
# %bb.0:
pushq       %rbp
.cfi_def_cfa_offset16
.cfi_offset%rbp,-16
movq        %rsp,       %rbp
.cfi_def_cfa_register%rbp
subq        $96,        %rsp
movq        %rdi,       -8(%rbp)
movq        %rsi,       -16(%rbp)
movq        -8(%rbp),   %rdi
movl        $578,       %esi        # imm = 0x242
movl        $438,       %edx        # imm = 0x1B6
movb        $0,         %al
callq       open
movl        %eax,       -20(%rbp)
movq        -16(%rbp),  %rax
movq        %rax,       -32(%rbp)
.LBB3_1:#=>ThisInnerLoopHeader:Depth=1
movq        -32(%rbp),  %rax
cmpq        $0,         8(%rax)
je              .LBB3_3
# %bb.2:                                #   in Loop: Header=BB3_1 Depth=1
movl        -20(%rbp),  %edi
movq        -32(%rbp),  %rax
movq        8(%rax),    %rsi
movq        -32(%rbp),  %rax
movq        (%rax),     %rdx
callq       write
.LBB3_3:#inLoop:Header=BB3_1Depth=1
movq        -32(%rbp),  %rax
cmpq        $0,         16(%rax)
jne             .LBB3_5
# %bb.4:
jmp             .LBB3_6
.LBB3_5:#inLoop:Header=BB3_1Depth=1
movq        -32(%rbp),  %rax
movq        16(%rax),   %rax
movq        %rax,       -32(%rbp)
jmp             .LBB3_1
.LBB3_6:
movl        -20(%rbp),  %edi
callq       close
cmpl        $-1,        %eax
jne             .LBB3_8
# %bb.7:
leaq        -96(%rbp),  %rdi
movq        -8(%rbp),   %rcx
movl        $64,        %esi
movabsq     $.L.str,    %rdx
movb        $0,         %al
callq       snprintf
leaq        -96(%rbp),  %rdi
movl        $4294967295,%esi#imm=0xFFFFFFFF
callq       exit_program
.LBB3_8:
addq        $96,        %rsp
popq        %rbp
.cfi_def_cfa%rsp,8
retq
.Lfunc_end3:
.sizecreate_backup,    .Lfunc_end3-create_backup
.cfi_endproc
# -- End function
.globlmain#--Beginfunctionmain
.p2align4,0x90
.typemain,@function
main:#      @main
.cfi_startproc
# %bb.0:
pushq       %rbp
.cfi_def_cfa_offset16
.cfi_offset%rbp,-16
movq        %rsp,       %rbp
.cfi_def_cfa_register%rbp
subq        $128,       %rsp
movl        $0,         -4(%rbp)
movl        %edi,       -8(%rbp)
movq        %rsi,       -16(%rbp)
callq       init
cmpl        $1,         -8(%rbp)
jg              .LBB4_2
# %bb.1:
movabsq     $.L.str.1,  %rdi
movabsq     $.L.str.2,  %rsi
movb        $0,         %al
callq       printf
movl        $0,         -4(%rbp)
jmp             .LBB4_5
.LBB4_2:
leaq        -24(%rbp),  %rdi
callq       strbuf_init
movq        -24(%rbp),  %rdi
movq        -16(%rbp),  %rax
movq        8(%rax),    %rsi
callq       read_to_strbuf
movq        -16(%rbp),  %rax
movq        8(%rax),    %rdi
addq        $4,         %rdi
callq       strlen
movq        %rax,       %rdi
movl        $1,         %esi
callq       calloc
movq        %rax,       -32(%rbp)
movq        -32(%rbp),  %rdi
movq        -16(%rbp),  %rax
movq        8(%rax),    %rdx
movabsq     $.L.str.3,  %rsi
movb        $0,         %al
callq       sprintf
movq        -32(%rbp),  %rsi
movabsq     $.L.str.1,  %rdi
movb        $0,         %al
callq       printf
movq        -32(%rbp),  %rdi
movq        -24(%rbp),  %rsi
callq       create_backup
leaq        -24(%rbp),  %rdi
callq       format_strbuf_list
movq        -16(%rbp),  %rax
movq        8(%rax),    %rdi
movl        $514,       %esi        # imm = 0x202
movb        $0,         %al
callq       open
movl        %eax,       -36(%rbp)
movq        -24(%rbp),  %rdi
movl        -36(%rbp),  %esi
callq       print_strbuf_list
movl        -36(%rbp),  %edi
callq       close
cmpl        $-1,        %eax
jne             .LBB4_4
# %bb.3:
leaq        -112(%rbp), %rdi
movq        -16(%rbp),  %rax
movq        8(%rax),    %rcx
movl        $64,        %esi
movabsq     $.L.str,    %rdx
movb        $0,         %al
callq       snprintf
leaq        -112(%rbp), %rdi
movl        $4294967295,%esi#imm=0xFFFFFFFF
callq       exit_program
.LBB4_4:
movq        -24(%rbp),  %rdi
movl        $1,         %esi
callq       print_strbuf_list
movq        -16(%rbp),  %rax
movq        8(%rax),    %rcx
movq        -32(%rbp),  %r9
movabsq     $.L.str.4,  %rdi
movabsq     $.L.str.5,  %rsi
movabsq     $.L.str.6,  %rax
movabsq     $.L.str.7,  %r8
movq        %rax,       %rdx
movq        %rax,       (%rsp)
movb        $0,         %al
callq       printf
movl        $0,         -4(%rbp)
.LBB4_5:
movl        -4(%rbp),   %eax
addq        $128,       %rsp
popq        %rbp
.cfi_def_cfa%rsp,8
retq
.Lfunc_end4:
.sizemain,    .Lfunc_end4-main
.cfi_endproc
# -- End function
.type    .L.str,@object#@.str
.section    .rodata.str1.1,"aMS",@progbits,1
.L.str:
.asciz"failtoopen        file        %s"
.size    .L.str,21

.type    .L.str.1,@object#@.str.1
.L.str.1:
.asciz"%s\n"
.size    .L.str.1,4

.type    .L.str.2,@object#@.str.2
.L.str.2:
.asciz"Noargumentgiven!"
.size    .L.str.2,19

.type    .L.str.3,@object#@.str.3
.L.str.3:
.asciz"%s.bak"
.size    .L.str.3,7

.type    .L.str.4,@object#@.str.4
.L.str.4:
.asciz"%sNOTE:%sTheprecedinglinesoverwritethefile%s;the         back        up          of          it          was         created     as          %s%s%s.\n"
.size    .L.str.4,94

.type    .L.str.5,@object#@.str.5
.L.str.5:
.asciz"\033[31;1m"
.size    .L.str.5,8

.type    .L.str.6,@object#@.str.6
.L.str.6:
.asciz"\033[0m"
.size    .L.str.6,5

.type    .L.str.7,@object#@.str.7
.L.str.7:
.asciz"\033[3m"
.size    .L.str.7,5

.ident"clangversion16.0.6      (Fedora     16.0.6-2.fc38)"
.section".note.GNU-stack","           ",@progbits
.addrsig
.addrsig_symformat_strbuf_list
.addrsig_symstrip_initial_space
.addrsig_symstrip_trailing_space
.addrsig_symstrip_repetitive_linebreaks
.addrsig_symstrbuf_tokenisation
.addrsig_symformat_insert_spaces
.addrsig_symcalloc
.addrsig_symstrbuf_init
.addrsig_symstrbuf_append
.addrsig_symprint_strbuf_list
.addrsig_syminit
.addrsig_syminit_global_variables
.addrsig_symcreate_backup
.addrsig_symopen
.addrsig_symwrite
.addrsig_symclose
.addrsig_symsnprintf
.addrsig_symexit_program
.addrsig_symprintf
.addrsig_symread_to_strbuf
.addrsig_symstrlen
.addrsig_symsprintf
