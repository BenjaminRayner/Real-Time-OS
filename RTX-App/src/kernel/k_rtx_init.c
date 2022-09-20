/**************************************************************************//**
 * @file        k_rtx_init.c
 * @brief       RTX System Initialization C file
 *****************************************************************************/

#include "k_rtx_init.h"
#include "k_rtx.h"
#include "k_inc.h"

int errno = 0;

/**************************************************************************//**
 * @brief   	system set up before calling rtx_init() from thread mode  
 * @pre         processor should be in thread mode using MSP, rtx_init is not called
 * @post        PSP is intialized and points to NULL task user stack
 * @return      0 on success and non-zero on failure
 * @note        you may add extra code here
 *****************************************************************************/
int k_pre_rtx_init (void *args)
{
    if ( k_mem_init(((RTX_SYS_INFO *)(args))->mem_algo) != RTX_OK) {
        return RTX_ERR;
    }
    
    g_tcbs[TID_NULL].u_sp_base = (U32)k_alloc_p_stack(TID_NULL, PROC_STACK_SIZE);
    __set_PSP(g_tcbs[TID_NULL].u_sp_base);
    
    return RTX_OK;
}

int k_rtx_init(RTX_SYS_INFO *sys_info, TASK_INIT *tasks, int num_tasks)
{
    errno = 0;

    if (sys_info == NULL) {
        errno = EINVAL;
        return RTX_ERR;
    }
    
    /* interrupts are already disabled when we enter here */
    if ( uart_irq_init(0) != RTX_OK ) {
        return RTX_ERR;
    }
    
    /* add timer(s) initialization code */
    
    if ( k_tsk_init(tasks, num_tasks) != RTX_OK ) {
        return RTX_ERR;
    }
    
    /* add message passing initialization code */
    
    k_tsk_start();        // start the first task
    return RTX_OK;
}

int k_get_sys_info(RTX_SYS_INFO *buffer)
{
    return RTX_OK;
}

/*
 *===========================================================================
 *                             END OF FILE
 *===========================================================================
 */
