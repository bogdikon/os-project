; ========================== BOOT SECTOR / ex06 / main =========================
; Простая программа загрузочного сектора (boot sector), которая выводит на экран
; шестнадцатеричное число
; ------------------------------------------------------------------------------
; 
; ------------------------------------------------------------------------------
; Чтобы перевести наш файл boot_sect.asm в машинный код, нужно написать:
; nasm boot_sect.asm -f bin -o boot_sect.bin
; ------------------------------------------------------------------------------
; Справочник по синтаксису ассемблера NASM можно найти тут: 
; https://www.opennet.ru/docs/RUS/nasm/nasm_ru3.html

[org 0x7c00]


mov dx, 0x1fb6					; Перемещаем 0x1fb6 в регистр dx чтобы потом
								; задействовать его в функции print_hex
mov bx, HEX_OUT					; перемещаем HEX_OUT в bx

call print_hex					; Вызываем функцию print_hex

								; ------------------------------------------------------

jmp $							; бесконечный цикл

%include "print_string.asm"		; директива %include вставляет весь код из
								; файла print_string.asm в место, откуда она
								; была вызвана.
%include "print_hex.asm"

HEX_OUT:						; Объявляем метку HEX_OUT
	db "0x0000", 0				; Объявляем массив из символом, заканчивающийся
								; нулем (гугли: нуль терминированная строка)

times 510-($-$$) db 0			; Заполняем ненужные байты нулями
dw 0xaa55						; Вставляем в конец "магическое число"