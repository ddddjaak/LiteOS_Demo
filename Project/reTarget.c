#include "stdio.h"

#pragma import(__use_no_semihosting)
/******************************************************************************
*??????????
******************************************************************************/
struct __FILE
{
	int handle;
/* Whatever you require here. If the only file you are using is */
/* standard output using printf() for debugging, no file handling */
/* is required. */
};
/* FILE is typedef’ d in stdio.h. */
FILE __stdout;

/// <summary>
/// ??_sys_exit()??????????
/// </summary>
/// <param name="x"></param>
/// <returns></returns>
void _sys_exit(int x)
{
	x = x;
}


/*
int fputc(int ch, FILE *f)
{
    //USART_SendData(USART1, (u8) ch);
    USART1->DR = (u8) ch;
   
    // Loop until the end of transmission
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
    {
    }

    return ch;
}
*/