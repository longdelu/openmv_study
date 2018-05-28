/*
* File      : drv_usart.c
* This file is part of RT-Thread RTOS
* COPYRIGHT (C) 2015, RT-Thread Development Team
*
*  This program is free software; you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation; either version 2 of the License, or
*  (at your option) any later version.
*
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License along
*  with this program; if not, write to the Free Software Foundation, Inc.,
*  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*
* Change Logs:
* Date           Author       Notes
* 2009-01-05     Bernard      the first version
* 2015-08-01     xiaonong     the first version for stm32f7xx
* 2016-01-15     ArdaFu       the first version for stm32f4xx with STM32 HAL
* 2016-01-15     zyh          the first version for stm32f401rc with STM32 HAL
*/
#include "drv_usart.h"
#include "board.h"
#include <rtdevice.h>
#include <rthw.h>
#include <rtthread.h>
/* STM32 uart driver */
struct drv_uart
{
    UART_HandleTypeDef UartHandle;
    IRQn_Type irq;
};

static rt_err_t drv_configure(struct rt_serial_device *serial,
                              struct serial_configure *cfg)
{
    struct drv_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);
    uart = (struct drv_uart *)serial->parent.user_data;
    uart->UartHandle.Init.BaudRate   = cfg->baud_rate;
    uart->UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
    uart->UartHandle.Init.Mode       = UART_MODE_TX_RX;
    uart->UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;
    uart->UartHandle.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
    switch (cfg->data_bits)
    {
    case DATA_BITS_8:
        uart->UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
        break;
    case DATA_BITS_9:
        uart->UartHandle.Init.WordLength = UART_WORDLENGTH_9B;
        break;
    default:
        uart->UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
        break;
    }
    switch (cfg->stop_bits)
    {
    case STOP_BITS_1:
        uart->UartHandle.Init.StopBits   = UART_STOPBITS_1;
        break;
    case STOP_BITS_2:
        uart->UartHandle.Init.StopBits   = UART_STOPBITS_2;
        break;
    default:
        uart->UartHandle.Init.StopBits   = UART_STOPBITS_1;
        break;
    }
    switch (cfg->parity)
    {
    case PARITY_NONE:
        uart->UartHandle.Init.Parity     = UART_PARITY_NONE;
        break;
    case PARITY_ODD:
        uart->UartHandle.Init.Parity     = UART_PARITY_ODD;
        break;
    case PARITY_EVEN:
        uart->UartHandle.Init.Parity     = UART_PARITY_EVEN;
        break;
    default:
        uart->UartHandle.Init.Parity     = UART_PARITY_NONE;
        break;
    }
    if (HAL_UART_Init(&uart->UartHandle) != HAL_OK)
    {
        return RT_ERROR;
    }
    return RT_EOK;
}

static rt_err_t drv_control(struct rt_serial_device *serial,
                            int cmd, void *arg)
{
    struct drv_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    uart = (struct drv_uart *)serial->parent.user_data;
    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        NVIC_DisableIRQ(uart->irq);
        /* disable interrupt */
        __HAL_UART_DISABLE_IT(&uart->UartHandle, UART_IT_RXNE);
        break;
    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        HAL_NVIC_SetPriority(uart->irq, 5, 0);
        NVIC_EnableIRQ(uart->irq);
        /* enable interrupt */
        __HAL_UART_ENABLE_IT(&uart->UartHandle, UART_IT_RXNE);
        break;
    }
    return RT_EOK;
}

static int drv_putc(struct rt_serial_device *serial, char c)
{
    struct drv_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    uart = (struct drv_uart *)serial->parent.user_data;
    while ((__HAL_UART_GET_FLAG(&uart->UartHandle, UART_FLAG_TXE) == RESET));
    uart->UartHandle.Instance->TDR = c;
    return 1;
}

static int drv_getc(struct rt_serial_device *serial)
{
    int ch;
    struct drv_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    uart = (struct drv_uart *)serial->parent.user_data;
    ch = -1;
    if (__HAL_UART_GET_FLAG(&uart->UartHandle, UART_FLAG_RXNE) != RESET)
        ch = uart->UartHandle.Instance->RDR & 0xff;
    return ch;
}

static const struct rt_uart_ops drv_uart_ops =
{
    drv_configure,
    drv_control,
    drv_putc,
    drv_getc,
};

#if defined(BSP_USING_UART1)
/* UART1 device driver structure */
static struct drv_uart uart1;
struct rt_serial_device serial1;
void USART1_IRQHandler(void)
{
    struct drv_uart *uart;
    uart = &uart1;
    /* enter interrupt */
    rt_interrupt_enter();
    /* UART in mode Receiver -------------------------------------------------*/
    if ((__HAL_UART_GET_FLAG(&uart->UartHandle, UART_FLAG_RXNE) != RESET) &&
            (__HAL_UART_GET_IT_SOURCE(&uart->UartHandle, UART_IT_RXNE) != RESET))
    {
        rt_hw_serial_isr(&serial1, RT_SERIAL_EVENT_RX_IND);
        /* Clear RXNE interrupt flag */
        __HAL_UART_CLEAR_FLAG(&uart->UartHandle, UART_FLAG_RXNE);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART1 */

#if defined(BSP_USING_UART2)
/* UART2 device driver structure */
static struct drv_uart uart2;
struct rt_serial_device serial2;
void USART2_IRQHandler(void)
{
    struct drv_uart *uart;
    uart = &uart2;
    /* enter interrupt */
    rt_interrupt_enter();
    /* UART in mode Receiver -------------------------------------------------*/
    if ((__HAL_UART_GET_FLAG(&uart->UartHandle, UART_FLAG_RXNE) != RESET) &&
            (__HAL_UART_GET_IT_SOURCE(&uart->UartHandle, UART_IT_RXNE) != RESET))
    {
        rt_hw_serial_isr(&serial2, RT_SERIAL_EVENT_RX_IND);
        /* Clear RXNE interrupt flag */
        __HAL_UART_CLEAR_FLAG(&uart->UartHandle, UART_FLAG_RXNE);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART2 */

#if defined(BSP_USING_UART3)
/* UART3 device driver structure */
static struct drv_uart uart3;
struct rt_serial_device serial3;
void USART3_IRQHandler(void)
{
    struct drv_uart *uart;
    uart = &uart3;
    /* enter interrupt */
    rt_interrupt_enter();
    /* UART in mode Receiver -------------------------------------------------*/
    if ((__HAL_UART_GET_FLAG(&uart->UartHandle, UART_FLAG_RXNE) != RESET) &&
            (__HAL_UART_GET_IT_SOURCE(&uart->UartHandle, UART_IT_RXNE) != RESET))
    {
        rt_hw_serial_isr(&serial3, RT_SERIAL_EVENT_RX_IND);
        /* Clear RXNE interrupt flag */
        __HAL_UART_CLEAR_FLAG(&uart->UartHandle, UART_FLAG_RXNE);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART3 */

#if defined(BSP_USING_UART4)
/* UART4 device driver structure */
static struct drv_uart uart4;
struct rt_serial_device serial4;
void UART4_IRQHandler(void)
{
    struct drv_uart *uart;
    uart = &uart4;
    /* enter interrupt */
    rt_interrupt_enter();
    /* UART in mode Receiver -------------------------------------------------*/
    if ((__HAL_UART_GET_FLAG(&uart->UartHandle, UART_FLAG_RXNE) != RESET) &&
            (__HAL_UART_GET_IT_SOURCE(&uart->UartHandle, UART_IT_RXNE) != RESET))
    {
        rt_hw_serial_isr(&serial4, RT_SERIAL_EVENT_RX_IND);
        /* Clear RXNE interrupt flag */
        __HAL_UART_CLEAR_FLAG(&uart->UartHandle, UART_FLAG_RXNE);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART4 */

#if defined(BSP_USING_UART5)
/* UART5 device driver structure */
static struct drv_uart uart5;
struct rt_serial_device serial5;
void UART5_IRQHandler(void)
{
    struct drv_uart *uart;
    uart = &uart5;
    /* enter interrupt */
    rt_interrupt_enter();
    /* UART in mode Receiver -------------------------------------------------*/
    if ((__HAL_UART_GET_FLAG(&uart->UartHandle, UART_FLAG_RXNE) != RESET) &&
            (__HAL_UART_GET_IT_SOURCE(&uart->UartHandle, UART_IT_RXNE) != RESET))
    {
        rt_hw_serial_isr(&serial5, RT_SERIAL_EVENT_RX_IND);
        /* Clear RXNE interrupt flag */
        __HAL_UART_CLEAR_FLAG(&uart->UartHandle, UART_FLAG_RXNE);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART5 */

#if defined(BSP_USING_LPUART1)
/* UART6 device driver structure */
static struct drv_uart lpuart1;
struct rt_serial_device lpserial1;
void LPUART1_IRQHandler(void)
{
    struct drv_uart *uart;
    uart = &lpuart1;
    /* enter interrupt */
    rt_interrupt_enter();
    /* UART in mode Receiver -------------------------------------------------*/
    if ((__HAL_UART_GET_FLAG(&uart->UartHandle, UART_FLAG_RXNE) != RESET) &&
            (__HAL_UART_GET_IT_SOURCE(&uart->UartHandle, UART_IT_RXNE) != RESET))
    {
        rt_hw_serial_isr(&lpserial1, RT_SERIAL_EVENT_RX_IND);
        /* Clear RXNE interrupt flag */
        __HAL_UART_CLEAR_FLAG(&uart->UartHandle, UART_FLAG_RXNE);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_LPUART1 */

/**
* @brief UART MSP Initialization
*        This function configures the hardware resources used in this example:
*           - Peripheral's clock enable
*           - Peripheral's GPIO Configuration
*           - NVIC configuration for UART interrupt request enable
* @param huart: UART handle pointer
* @retval None
*/
void HAL_UART_MspInit(UART_HandleTypeDef *uartHandle)
{

    GPIO_InitTypeDef GPIO_InitStruct;
    if (uartHandle->Instance == LPUART1)
    {
        /* LPUART1 clock enable */
        __HAL_RCC_LPUART1_CLK_ENABLE();
        /* GPIOC clock enable */
        __HAL_RCC_GPIOC_CLK_ENABLE();
        /**LPUART1 GPIO Configuration
        PC0     ------> LPUART1_RX
        PC1     ------> LPUART1_TX
        */
        GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF8_LPUART1;
        HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
    }
    else if (uartHandle->Instance == UART4)
    {
        /* UART4 clock enable */
        __HAL_RCC_UART4_CLK_ENABLE();
        /* GPIOA clock enable */
        __HAL_RCC_GPIOA_CLK_ENABLE();
        /**UART4 GPIO Configuration
        PA0     ------> UART4_TX
        PA1     ------> UART4_RX
        */
        GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF8_UART4;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    }
    else if (uartHandle->Instance == UART5)
    {
        /* UART5 clock enable */
        __HAL_RCC_UART5_CLK_ENABLE();
        /* GPIOD clock enable */
        __HAL_RCC_GPIOD_CLK_ENABLE();
        /* GPIOC clock enable */
        __HAL_RCC_GPIOC_CLK_ENABLE();
        /**UART5 GPIO Configuration
        PC12     ------> UART5_TX
        PD2     ------> UART5_RX
        */
        GPIO_InitStruct.Pin = GPIO_PIN_12;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF8_UART5;
        HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_2;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF8_UART5;
        HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
    }
    else if (uartHandle->Instance == USART1)
    {
        /* USART1 clock enable */
        __HAL_RCC_USART1_CLK_ENABLE();
        /* GPIOA clock enable */
        __HAL_RCC_GPIOA_CLK_ENABLE();
        /**USART1 GPIO Configuration
        PA9     ------> USART1_TX
        PA10     ------> USART1_RX
        */
        GPIO_InitStruct.Pin = GPIO_PIN_9 | GPIO_PIN_10;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    }
    else if (uartHandle->Instance == USART2)
    {
        /* USART2 clock enable */
        __HAL_RCC_USART2_CLK_ENABLE();
        /* GPIOA clock enable */
        __HAL_RCC_GPIOA_CLK_ENABLE();
        /**USART2 GPIO Configuration
        PA2     ------> USART2_TX
        PA3     ------> USART2_RX
        */
        GPIO_InitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_3;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    }
    else if (uartHandle->Instance == USART3)
    {
        /* USART3 clock enable */
        __HAL_RCC_USART3_CLK_ENABLE();
        /* GPIOC clock enable */
        __HAL_RCC_GPIOC_CLK_ENABLE();
        /**USART3 GPIO Configuration
        PC4     ------> USART3_TX
        PC5     ------> USART3_RX
        */
        GPIO_InitStruct.Pin = GPIO_PIN_4 | GPIO_PIN_5;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
        HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
    }
}


void HAL_UART_MspDeInit(UART_HandleTypeDef *uartHandle)
{

    if (uartHandle->Instance == LPUART1)
    {
        /* Peripheral clock disable */
        __HAL_RCC_LPUART1_CLK_DISABLE();

        /**LPUART1 GPIO Configuration
        PC0     ------> LPUART1_RX
        PC1     ------> LPUART1_TX
        */
        HAL_GPIO_DeInit(GPIOC, GPIO_PIN_0 | GPIO_PIN_1);
    }
    else if (uartHandle->Instance == UART4)
    {
        /* Peripheral clock disable */
        __HAL_RCC_UART4_CLK_DISABLE();

        /**UART4 GPIO Configuration
        PA0     ------> UART4_TX
        PA1     ------> UART4_RX
        */
        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_0 | GPIO_PIN_1);
    }
    else if (uartHandle->Instance == UART5)
    {
        /* Peripheral clock disable */
        __HAL_RCC_UART5_CLK_DISABLE();

        /**UART5 GPIO Configuration
        PC12     ------> UART5_TX
        PD2     ------> UART5_RX
        */
        HAL_GPIO_DeInit(GPIOC, GPIO_PIN_12);

        HAL_GPIO_DeInit(GPIOD, GPIO_PIN_2);
    }
    else if (uartHandle->Instance == USART1)
    {
        /* Peripheral clock disable */
        __HAL_RCC_USART1_CLK_DISABLE();

        /**USART1 GPIO Configuration
        PA9     ------> USART1_TX
        PA10     ------> USART1_RX
        */
        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9 | GPIO_PIN_10);
    }
    else if (uartHandle->Instance == USART2)
    {
        /* Peripheral clock disable */
        __HAL_RCC_USART2_CLK_DISABLE();

        /**USART2 GPIO Configuration
        PA2     ------> USART2_TX
        PA3     ------> USART2_RX
        */
        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2 | GPIO_PIN_3);
    }
    else if (uartHandle->Instance == USART3)
    {
        /* Peripheral clock disable */
        __HAL_RCC_USART3_CLK_DISABLE();

        /**USART3 GPIO Configuration
        PC4     ------> USART3_TX
        PC5     ------> USART3_RX
        */
        HAL_GPIO_DeInit(GPIOC, GPIO_PIN_4 | GPIO_PIN_5);
    }
}

int bsp_hw_usart_init(void)
{
    struct drv_uart *uart;
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
#ifdef BSP_USING_UART1
    uart = &uart1;
    uart->UartHandle.Instance = USART1;
    uart->irq = USART1_IRQn;
    serial1.ops    = &drv_uart_ops;
    serial1.config = config;
    /* register UART1 device */
    rt_hw_serial_register(&serial1, "uart1",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
#endif /* BSP_USING_UART1 */
#ifdef BSP_USING_UART2
    uart = &uart2;
    uart->UartHandle.Instance = USART2;
    uart->irq = USART2_IRQn;
    serial2.ops    = &drv_uart_ops;
    serial2.config = config;
    /* register UART2 device */
    rt_hw_serial_register(&serial2, "uart2",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
#endif /* BSP_USING_UART2 */
#ifdef BSP_USING_UART3
    uart = &uart3;
    uart->UartHandle.Instance = USART3;
    uart->irq = USART3_IRQn;
    serial3.ops    = &drv_uart_ops;
    serial3.config = config;
    /* register UART3 device */
    rt_hw_serial_register(&serial3, "uart3",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
#endif /* BSP_USING_UART3 */
#ifdef BSP_USING_UART4
    uart = &uart4;
    uart->UartHandle.Instance = UART4;
    uart->irq = UART4_IRQn;
    serial4.ops    = &drv_uart_ops;
    serial4.config = config;
    /* register UART4 device */
    rt_hw_serial_register(&serial4, "uart4",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
#endif /* BSP_USING_UART4 */
#ifdef BSP_USING_UART5
    uart = &uart5;
    uart->UartHandle.Instance = UART5;
    uart->irq = UART5_IRQn;
    serial5.ops    = &drv_uart_ops;
    serial5.config = config;
    /* register UART5 device */
    rt_hw_serial_register(&serial5, "uart5",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
#endif /* BSP_USING_UART5 */
#ifdef BSP_USING_LPUART1
    uart = &lpuart1;
    uart->UartHandle.Instance = LPUART1;
    uart->irq = LPUART1_IRQn;
    lpserial1.ops    = &drv_uart_ops;
    lpserial1.config = config;
    /* register LPUART1 device */
    rt_hw_serial_register(&lpserial1, "lpuart1",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
#endif /* BSP_USING_LPUART1 */
    return 0;
}
INIT_BOARD_EXPORT(bsp_hw_usart_init);
