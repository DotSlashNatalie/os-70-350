	BITS 16

start:
	mov ax, 07C0h		; Set up 4K stack space after this bootloader
	add ax, 288		; (4096 + 512) / 16 bytes per paragraph
	mov ss, ax
	mov sp, 4096

	mov ax, 07C0h		; Set data segment to where we're loaded
	mov ds, ax

	mov     ax, 12h
	int     10h
	mov si, text_string	; Put string position into SI
	mov bl, 3
	call print_string	; Call our string-printing routine
	

	jmp $			; Jump here - infinite loop!


	
text_string db 'This is my cool new Operating System!', 0
counter db 0

print_string:			; Routine: output string in SI to screen
	mov ah, 0Eh		; int 10h 'print char' function

.repeat:
	lodsb			; Get character from string
	
	
	cmp byte [counter], 1
	jle .skipcolor
	mov bl, 4
.skipcolor:

	cmp al, 0
	je .done		; If char is zero, end of string
	int 10h			; Otherwise, print it
	
	mov dx, [counter]
	inc dx
	mov [counter], dx
	;add counter, 1

	jmp .repeat

.done:
	ret


	times 510-($-$$) db 0	; Pad remainder of boot sector with 0s
	dw 0xAA55		; The standard PC boot signature