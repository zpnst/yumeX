[bits 16]

print_string_loop:
    mov al, [bx]
    cmp al, 0
    je print_string_loop_end
    int 0x10
    add bx, 1
    jmp print_string_loop

print_string:
    pusha
    mov ah, 0x0e
    jmp print_string_loop
    print_string_loop_end:
    popa
    ret

print_nl:
    pusha
    
    mov ah, 0x0e
    mov al, 0x0a ; newline char
    int 0x10
    mov al, 0x0d ; carriage return
    int 0x10
    
    popa
    ret