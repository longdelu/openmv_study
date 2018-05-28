/*
 * File      : board.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-09-22     Bernard      add board.h to this bsp
 */
#ifndef __BOARD_H__
#define __BOARD_H__

#include "stm32f7xx_hal.h"

/* whether use board external SDRAM memory */
#define EXT_SDRAM_BEGIN    (0xC0000000)
#define EXT_SDRAM_SIZE     (0x800000)
#define EXT_SDRAM_END      (EXT_SDRAM_BEGIN + EXT_SDRAM_SIZE)

#ifdef __CC_ARM
extern int Image$$RW_IRAM1$$ZI$$Limit;
#define HEAP_BEGIN    (&Image$$RW_IRAM1$$ZI$$Limit)
#elif __ICCARM__
#pragma section="HEAP"
#define HEAP_BEGIN    (__segment_end("HEAP"))
#else
extern int __bss_end;
#define HEAP_BEGIN    (&__bss_end)
#endif

#define STM32_SRAM_SIZE   (512)
#define HEAP_END          (0x20000000 + STM32_SRAM_SIZE * 1024)
#define HEAP_SIZE         (HEAP_END - (rt_uint32_t)HEAP_BEGIN)

extern void rt_hw_board_init(void);
#endif

