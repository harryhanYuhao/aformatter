  .global     _start      

  .text
        _start:
# write "Hello, World!" to stdout
  mov      $1,         %rax        # syscall write
    mov       $1,         %rdi        # 1 is stdout
   mov       $message,   %rsi        # pointer to message
    mov         $15,        %rdx        # the length of the string
   syscall     



# exit syscall
 mov  $60,    %rax        
 mov       %rbx,       %rdi        
   syscall     

    .data
message:
    .ascii "Hello, World!\n\0"

