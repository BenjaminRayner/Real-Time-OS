/**************************************************************************//**
 * @file        main.c
 * @brief       main routine to start up the RTX in kernel mode 
 *****************************************************************************/

#include <LPC17xx.h>
#include "rtx.h"
#include "rtx_errno.h"
#include "uart_polling.h"
#include "printf.h"
#include "ae.h"
#include "timer.h"


/**************************************************************************//**
 * @brief   	main routine
 *          
 * @return      0 on success and non-zero on failure
 *****************************************************************************/
int main() 
{   
    /* initial tasks */
    static RTX_SYS_INFO sys;
    static TASK_INIT *p_tasks = NULL;
    static int num = 0;
    
    /* CMSIS system initialization */
    SystemInit();   
    __disable_irq();
    
	  timer_irq_init(TIMER0);     /* initialize timer0, fires interrupts per 500 usec */
    timer_freerun_init(TIMER1); /* initialize timer1, free running timer            */
    uart_irq_init(0); 				  /* uart0 interrupt driven, for RTX console 					*/
    uart_init(1);     					/* uart1 polling, for debugging                 		*/
    
    /* initialize printf to use uart1 by polling */
    init_printf(NULL, putc);
    
    __enable_irq();
    
    U32 ctrl = __get_CONTROL();
#ifdef DEBUG_1    
    printf("ctrl = %d, We should be at privileged level upon reset, so we can access SP.\r\n", ctrl); 
    printf("Read MSP = 0x%x\r\n", __get_MSP);
    printf("Read PSP = 0x%x\r\n", __get_PSP());
#endif // DEBUG_1    

    
    /* initialize the third-party testing framework */
    ae_init(&sys, &p_tasks, &num, &k_pre_rtx_init, &sys);
    __set_CONTROL(__get_CONTROL() | BIT(1));
    __isb(15); // see https://www.keil.com/support/man/docs/armcc/armcc_chr1435075770601.htm#:~:text=This%20intrinsic%20inserts%20an%20ISB,is%20also%20an%20optimization%20barrier.
    
    /* start the RTX */
    rtx_init(&sys, p_tasks, num);

    /* We should not reach here if everything goes well!!! */
    return RTX_ERR;  
}
/*
 *===========================================================================
 *                             END OF FILE
 *===========================================================================
 */
