/*
 * File      : board.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006-2012, RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date                Author         Notes
 * 2010-06-25     Bernard        first version
 * 2011-08-08     lgnq             modified for Loongson LS1B
 * 2015-07-06     chinesebear   modified for Loongson LS1C
 */

#ifndef __BOARD_H__
#define __BOARD_H__

void rt_hw_board_init(void);

/* 32M SDRAM */
#define RT_HW_HEAP_END	(0x80000000 + 32 * 1024 * 1024)
#define CPU_HZ			(252 * 1000000)

#endif
