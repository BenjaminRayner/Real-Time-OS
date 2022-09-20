/**************************************************************************//**
 * @file        ae_task_util.c
 * @brief       task management lab auto-tester utility functions
 *****************************************************************************/
 
#include "ae_tasks_util.h"
#include "ae_util.h"


int dump_task_info(RTX_TASK_INFO *ptr) 
{

    if ( ptr == NULL ) {
        return RTX_ERR;
    }
    
    printf("tid:          %d\r\n",   ptr->tid);
    printf("state:        %d\r\n",   ptr->state);
    printf("prio:         %d\r\n",   ptr->prio);
    printf("priv:         %d\r\n",   ptr->priv);
    printf("ptask:        0x%x\r\n", ptr->ptask);
    printf("k_sp_base:    0x%x\r\n", ptr->k_sp_base);
    printf("k_sp:         0x%x\r\n", ptr->k_sp);
    printf("k_stack_size: 0x%x\r\n", ptr->k_stack_size);
    printf("u_sp_base:    0x%x\r\n", ptr->u_sp_base);
    printf("u_sp:         0x%x\r\n", ptr->u_sp);
    printf("u_stack_size: 0x%x\r\n", ptr->u_stack_size);
    
    return RTX_OK;
}

int dump_tasks(task_t *p_tids, size_t len)
{
    RTX_TASK_INFO task_info;
    
    if ( p_tids == NULL ) {
        return RTX_ERR;
    }
    
    for ( int i = 0; i < len; i++ ) {
        int ret_val = tsk_get(p_tids[i], &task_info);
        if ( ret_val == RTX_OK ) {
            dump_task_info(&task_info);
        } else {
            printf ("ERR: tsk_get failed\r\n");
        }
    }
    return RTX_OK;
}

int dump_mbx_info(task_t tid)
{
    int space = mbx_get(tid);
    
    if ( space < 0 ) {
        printf("ERR: mbx_get on tid=%u failed\r\n", tid);
        return RTX_ERR;
    } 
    
    printf("TID = %u, malbox free bytes = %u.\r\n", tid, space); 
    return RTX_OK;
}

int dump_mailboxes(task_t *p_tids, size_t len)
{
    if ( p_tids == NULL ) {
        return RTX_ERR;
    }
    
    for ( int i = 0; i < len; i++) {
        printf("tid %u has a mailbox\r\n", p_tids[i]);
        dump_mbx_info(p_tids[i]);   
    }
    return RTX_OK;
}


/*
 *===========================================================================
 *                             END OF FILE
 *===========================================================================
 */
