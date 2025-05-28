; Ensures that we jump straight into the kernel’s entry function.
[bits 32]           ; We’ re in protected mode by now , so use 32 - bit instructions.
[extern kermain]    ; Declate that we will be referencing the external symbol 'kermain',
                    ; so the linker can substitute the final address
call kermain        ; invoke kermain() in our C kernel
jmp $               ; Hang forever when we return from the kernel


