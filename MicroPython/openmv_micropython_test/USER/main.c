#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "sdram.h"
#include "malloc.h"
/************************************************
 ALIENTEK ������STM32F429������ ʵ��1
 �����ʵ��-HAL��汾
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/




/*������������ʹ��HAL�⺯��ʵ�ֿ���IO�����*/
 
int main(void)
{
    HAL_Init();                     //��ʼ��HAL��   
    Stm32_Clock_Init(360,25,2,8);   //����ʱ��,180Mhz
    delay_init(180);                //��ʼ����ʱ����
    LED_Init();                     //��ʼ��LED  
    SDRAM_Init();                   //SDRAM��ʼ��
    my_mem_init(SRAMIN);            //��ʼ���ڲ��ڴ��
    my_mem_init(SRAMEX);            //��ʼ���ⲿSDRAM�ڴ��
    my_mem_init(SRAMCCM);		        //��ʼ��CCM�ڴ�� 
    
    while(1)
    {
        HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_RESET); //LED0��Ӧ����PB1���ͣ�������ͬ��LED0(0)
        HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);   //LED1��Ӧ����PB0���ߣ��𣬵�ͬ��LED1(1)
        delay_ms(500);										//��ʱ500ms
        HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_SET);   //LED0��Ӧ����PB1���ߣ��𣬵�ͬ��LED0(1)
        HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET); //LED1��Ӧ����PB0���ͣ�������ͬ��LED1(0)
        delay_ms(500);                                      //��ʱ500ms 
    }
}
 

 
/*����������ʹ��λ������ʵ�֣�*/
/*
int main(void)
{ 
    HAL_Init();                     //��ʼ��HAL��   
    Stm32_Clock_Init(360,25,2,8);   //����ʱ��,180Mhz
    delay_init(180);                //��ʼ����ʱ����
    LED_Init();                     //��ʼ��LED    while(1)
	{
         LED0=0;			     //LED0��
	     LED1=1;				 //LED1��
		 delay_ms(500);
		 LED0=1;				//LED0��
		 LED1=0;				//LED1��
		 delay_ms(500);
	 }
}*/




/*
����������ʹ��ֱ�Ӳ����������ʽʵ�������
*/
/*
int main(void)
{ 
    HAL_Init();                     //��ʼ��HAL��   
    Stm32_Clock_Init(360,25,2,8);   //����ʱ��,180Mhz
    delay_init(180);                //��ʼ����ʱ����
    LED_Init();                     //��ʼ��LED  
	while(1)
	{
      GPIOB->BSRR=GPIO_PIN_1;     //LED0��
	  GPIOB->BSRR=GPIO_PIN_0<<16; //LED1��
	  delay_ms(500);
      GPIOB->BSRR=GPIO_PIN_1<<16; //LED0��
	  GPIOB->BSRR=GPIO_PIN_0;     //LED1��
	  delay_ms(500);
	 }
 }	
*/




