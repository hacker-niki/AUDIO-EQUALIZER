PUBLIC  add_3

_TEXT  SEGMENT

add_3  PROC

    push  rbp
    mov   rbp, rsp

    xor rax, rax
    mov   rax, rcx  ;  The 1st argument
    add   rax, rdx  ;  The 2nd argument
    add   rax, r8  ;  The 3rd argument

    pop   rbp
    ret   0

add_3 ENDP

_TEXT  ENDS

END          ; END directive required at end of file