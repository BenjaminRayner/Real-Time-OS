/**************************************************************************//**
 * @file        ae.c
 * @brief       Automated Evaluation (AE) Framework Source File
 *****************************************************************************/

#include "ae.h"

/**************************************************************************//**
 * @brief   	ae_init
 * @return		RTX_OK on success and RTX_ERR on failure
 * @param[out]  sys_info system initialization struct AE writes to
 * @param[out]	task_info boot-time tasks struct array AE writes to
 *
 *****************************************************************************/

int	ae_init(RTX_SYS_INFO *sys_info, 
                TASK_INIT    **tasks, 
                int          *num_tasks, 
                int          (*cb_func) (void *(arg)), 
                void         *arg)
{
	if ( ae_set_sys_info(sys_info) != RTX_OK ) {
		return RTX_ERR;
	}
    cb_func(arg);
	ae_set_init_tasks_info(tasks, num_tasks);
	return RTX_OK;
}


/**************************************************************************//**
 * @brief   	 debugger .ini can reference this one to exit 
 *****************************************************************************/

void ae_exit(void)
{
    while(1);
}

/**************************************************************************//**
 * @brief       fill the sys_info struct with system configuration info.
 * @return		RTX_OK on success and RTX_ERR on failure
 * @param[out]  sys_info system initialization struct AE writes to
 *
 *****************************************************************************/
int ae_set_sys_info(RTX_SYS_INFO *sys_info)
{
    if (sys_info == NULL) {
        return RTX_ERR;
    }

    sys_info->mem_algo      = BUDDY;
#ifndef ECE350_P4
    sys_info->sched         = DEFAULT;
#else    
    sys_info->sched         = EDF;
#endif    
    return RTX_OK;
}

void ae_set_init_tasks_info (TASK_INIT **pp_tasks, int *p_num_tasks)
{
    if (pp_tasks == NULL) {
		return;
	}
    set_ae_init_tasks(pp_tasks, p_num_tasks);
    
    return;
}



/*
 *===========================================================================
 *                             END OF FILE
 *===========================================================================
 */

