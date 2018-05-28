// �����ʱԴ�ļ�


#include "ls1c_clock.h"




/*
 * ��ʱָ��ʱ�䣬��λms
 * @j ��ʱʱ�䣬��λms
 */
void delay_ms(int j)
{
    int k_max = clk_get_cpu_rate()/1000/3;  // ����1000��ʾms������3Ϊ�������õľ���(�������Ϊ���ڲ�ѭ��ִ��һ����Ҫ��ʱ�Ӹ���)
    int k = k_max;

    for ( ; j > 0; j--)
    {
        for (k = k_max; k > 0; k--)
        {
            __asm__ ("nop");        // ע�⣬���������������࣬����ᱻ�Ż���
        }
    }

    return ;
}


/*
 * ��ʱָ��ʱ�䣬��λus
 * @n ��ʱʱ�䣬��λus
 */
void delay_us(int n)
{
    int count_1us = clk_get_cpu_rate() / 1000000 / 3;   // ��ʱ1us��ѭ������
    int count_max;                                      // ��ʱn΢���ѭ������
    int tmp;

    // ������ʱ����΢��(ע�⣬�������ֶ��Ż��ģ�cpuƵ�ʸı��˿�����Ҫ�����Ż�����ʱcpuƵ��Ϊ252Mhz)
    if (10 >= n)                // <=10us
    {
        count_1us -= 35;
    }
    else if (100 >= n)          // <= 100us
    {
        count_1us -= 6;
    }
    else                        // > 100us
    {
        count_1us -= 1;
    }
    count_max = n * count_1us;

    // ��ʱ
    for (tmp = count_max; tmp > 0; tmp--)
    {
        __asm__ ("nop");        // ע�⣬���������������࣬����ᱻ�Ż���            
    }

    return ;
}


/*
 * ��ʱָ��ʱ�䣬��λs
 * @i ��ʱʱ�䣬��λs
 */
void delay_s(int i)
{
    for ( ; i > 0; i--)
    {
        delay_ms(1000);
    }

    return ;
}



