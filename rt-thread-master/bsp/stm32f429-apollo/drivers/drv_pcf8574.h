#ifndef __DRV_PCF8574_H
#define __DRV_PCF8574_H

#include <board.h>
#include <finsh.h>
#include <rtdevice.h>
#include <rthw.h>

//PCF8574����IO�Ĺ���
#define BEEP_IO         0		//��������������  	P0
#define AP_INT_IO       1   	//AP3216C�ж�����	P1
#define DCMI_PWDN_IO    2    	//DCMI�ĵ�Դ��������	P2
#define USB_PWR_IO      3    	//USB��Դ��������	P3
#define EX_IO      		4    	//��չIO,�Զ���ʹ�� 	P4
#define MPU_INT_IO      5   	//MPU9250�ж�����	P5
#define RS485_RE_IO     6    	//RS485_RE����		P6
#define ETH_RESET_IO    7    	//��̫����λ����		P7

rt_err_t rt_pcf8574_init(void);

void rt_pcf8574_write_bit(rt_uint8_t bit, rt_uint8_t state);
rt_uint8_t rt_pcf8574_read_bit(rt_uint8_t bit);

#endif

