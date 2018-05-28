// Ӳ����ʱ��ͷ�ļ�


#ifndef __OPENLOONGSON_TIMER_H
#define __OPENLOONGSON_TIMER_H


#include "ls1c_public.h"


// Ӳ����ʱ��
typedef enum
{
    TIMER_PWM0,                     // PWM0����Ӳ����ʱ��
    TIMER_PWM1,                     // PWM1����Ӳ����ʱ��
    TIMER_PWM2,                     // PWM2����Ӳ����ʱ��
    TIMER_PWM3                      // PWM3����Ӳ����ʱ��
}ls1c_timer_t;


// Ӳ����ʱ����Ϣ
typedef struct
{
    ls1c_timer_t timer;                  // Ӳ����ʱ��
    unsigned long time_ns;          // ��ʱʱ��
}timer_info_t;



/*
 * ��ʼ����ʱ��������ʼ��ʱ
 * @timer_info ��ʱ���Ͷ�ʱʱ����Ϣ
 */
void timer_init(timer_info_t *timer_info);


/*
 * �ж�ָ����ʱ���Ƿ�ʱ
 * @timer_info ��ʱ��
 * @ret TRUE or FALSE
 */
BOOL timer_is_time_out(timer_info_t *timer_info);


/*
 * ֹͣ��ʱ��
 * @timer_info ��ʱ��
 */
void timer_stop(timer_info_t *timer_info);



/*
 * ��ȡ��ʱ���ӳ�ʼ�������ڵ�ʱ��(ʵ�ּ�ʱ����)����λns
 * @timer_info Ӳ����ʱ��
 * @ret ʱ�䣬��λns
 */
unsigned long timer_get_time_ns(timer_info_t *timer_info);


/*
 * ��ӡtimer��ؼĴ�����ֵ
 * @timer_info Ӳ����ʱ��
 */
void timer_print_regs(timer_info_t *timer_info);


#endif

