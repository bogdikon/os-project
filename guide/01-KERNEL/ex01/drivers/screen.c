/*------------------------------------------------------------------------------
*	Guide:	01-KERNEL
*	File:	ex01 / drivers / screen.c
*	Title:	Функции работы с экраном
* ------------------------------------------------------------------------------
*	Description:
* ----------------------------------------------------------------------------*/


#include "screen.h"
#include "lowlevel_io.h"
#include "../common.h"


void	kprint(u8 *str)
{
	/* Функция печати строки */

	while (*str)
	{
		putchar(*str, WHITE_ON_BLACK);
		str++;
	}
}

void	putchar(u8 character, u16 attribute_byte)
{
	/* Более высокоуровневая функция печати символа */

	u32 offset;

	offset = get_cursor();
	if (character == '\n')
	{
		// Переводим строку.
		// Попробуйте сами понять что происходит на строчке кода ниже :)
		set_cursor((offset - offset % MAX_COLS) + MAX_COLS*2);
	} 
	else 
	{
		write(character, attribute_byte, offset);
		set_cursor(offset+2);
	}
}

void	clear_screen()
{
	/* Функция очистки экрана */

	u32	offset = 0;
	while (offset < (MAX_ROWS * MAX_COLS * 2))
	{
		write('\0', 0x0f, offset);
		offset += 2;
	}
	set_cursor(0);
}

void	write(u8 character, u8 attribute_byte, u32 offset)
{
	/* Функция печати символа на экран с помощью VGA по адресу 0xb8000 */

	// u8 character: байт, соответствующий символу
	// u8 attribute_byte: байт, соответствующий цвету текста/фона символа
	// u32 offset: смещение (позиция), по которому нужно распечатать символ
	u8 *vga = (u8 *) VIDEO_ADDRESS;
	vga[offset] = character;
	vga[offset + 1] = attribute_byte;
}

u32		get_cursor()
{
	/* Функция, возвращающая позицию курсора (char offset). */

	port_byte_out(REG_SCREEN_CTRL, 14);				// Запрашиваем верхний байт
	u8 high_byte = port_byte_in(REG_SCREEN_DATA);	// Принимаем его
	port_byte_out(REG_SCREEN_CTRL, 15);				// Запрашиваем нижний байт
	u8 low_byte = port_byte_in(REG_SCREEN_DATA);	// Принимаем и его
	// Возвращаем смещение умножая его на 2, т.к. порты возвращают смещение в
	// клетках экрана (cell offset), а нам нужно в символах (char offset), т.к.
	// на каждый символ у нас 2 байта
	return (((high_byte << 8) + low_byte) * 2);
}

void	set_cursor(u16 pos)
{
	/* Функция, устаналивающая курсор по смещнию (позиции) pos */
	/* Поиграться с битами можно тут http://bitwisecmd.com/ */

	pos /= 2;	// конвертируем в cell offset (в позицию по клеткам, а не
				// символам)
	// Устанавливаем позицию курсора
	port_byte_out(REG_SCREEN_CTRL, 14);			// Указываем, что будем
												// передавать верхний байт
	port_byte_out(REG_SCREEN_DATA, (pos >> 8));	// Передаем верхний байт
	port_byte_out(REG_SCREEN_CTRL, 15);			// Указываем, что будем
												// передавать нижний байт
	port_byte_out(REG_SCREEN_DATA, (pos & 0xff));	// передаем нижний байт
}