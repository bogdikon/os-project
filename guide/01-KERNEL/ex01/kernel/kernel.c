/*------------------------------------------------------------------------------
*	Guide:	01-KERNEL
*	File:	ex01 / kernel / kernel.c
*	Title:	Ядро
* ------------------------------------------------------------------------------
*	Description:
* ----------------------------------------------------------------------------*/


#include "../common.h"
#include "../drivers/screen.h"


s32		kmain()
{
	u8 i;
	u8 k;
	clear_screen();

	i = 0;
	while (i < 25)
	{
		k = 0;
		while (k < 10)
		{
			putchar(i + 'a', WHITE_ON_BLACK);
			k++;
		}
		putchar('\n', WHITE_ON_BLACK);
		i++;
	}

	return 0;
}
