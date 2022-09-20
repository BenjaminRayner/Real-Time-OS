/**************************************************************************//**
 * @file        null_task.c
 * @brief       The NULL Task Template Code
 *****************************************************************************/

#include "LPC17xx.h"
#include "rtx.h"
#include "uart_polling.h"
#include "printf.h"

void task_null(void)
{
#ifdef DEBUG_0
    task_t tid = tsk_gettid();
#endif
    while (1) {
#ifdef DEBUG_0
        for ( int i = 0; i < 5; i++ ){
            printf("==============Task NULL: TID = %d ===============\r\n", tid);
        }
#endif
        tsk_yield();
    }
}
/*
 *===========================================================================
 *                             END OF FILE
 *===========================================================================
 */

