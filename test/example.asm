    .global_start

    .text
_start:
# write "Hello, World!" to stdout
    mov         $1,         %rax        # syscall write
    mov         $1,         %rdi        # 1 is stdout
    mov         $message,   %rsi        # pointer to message
    mov         $15,        %rdx        # the length of the string
    syscall     

# read form stdin
    mov         $0,         %rax        # syscall write
    mov         $0,         %rdi        # 0 is stdin
    mov         $message,   %rsi        # pointer to message
    mov         $15,        %rdx        # the length of the string
    syscall     

# write to stdout
    mov         $1,         %rax        # syscall write
    mov         $1,         %rdi        # 1 is stdout
    mov         $message,   %rsi        # pointer to message
    mov         $15,        %rdx        # the length of the string
    syscall     

    mov         $20,        %rbx        

# while (rbx > 0) --rbx;
loop:
    cmp         $0,         %rbx        
    jle         endofloop   # if rbx <= 0, jump to endofloop
    sub         $1,         %rbx        
    jmp         loop        
endofloop:

# if ebx < 0; ebx = 100

exit:
    mov         $60,        %rax        
    mov         %rbx,       %rdi        
    syscall     

    .data
message:
    .ascii"Hello,World!\n\0" 

