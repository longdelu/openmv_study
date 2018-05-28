// ��װgpio�ӿ�


#include "ls1c_public.h"
#include "ls1c_regs.h"
#include "ls1c_gpio.h"
#include "ls1c_pin.h"


/*
 * ��ȡָ��gpio��CFG�Ĵ���
 * @gpio gpio���
 * @ret CFG�Ĵ���
 */
volatile unsigned int *gpio_get_cfg_reg(unsigned int gpio)
{
    volatile unsigned int *gpio_cfgx = NULL;            // GPIO_CFGx�Ĵ���
    unsigned int port = GPIO_GET_PORT(gpio);

    switch (port)
    {
        case 0:
            gpio_cfgx = (volatile unsigned int *)LS1C_GPIO_CFG0;
            break;

        case 1:
            gpio_cfgx = (volatile unsigned int *)LS1C_GPIO_CFG1;
            break;

        case 2:
            gpio_cfgx = (volatile unsigned int *)LS1C_GPIO_CFG2;
            break;

        case 3:
            gpio_cfgx = (volatile unsigned int *)LS1C_GPIO_CFG3;
            break;

        default:
            gpio_cfgx = NULL;
            break;
    }

    return gpio_cfgx;
}


/*
 * ��ȡָ��gpio��EN�Ĵ���
 * @gpio gpio���
 * @ret EN�Ĵ���
 */
volatile unsigned int *gpio_get_en_reg(unsigned int gpio)
{
    volatile unsigned int *gpio_enx = NULL;         // GPIO_ENx�Ĵ���
    unsigned int port = GPIO_GET_PORT(gpio);
    
    switch (port)
    {
        case 0:
            gpio_enx = (volatile unsigned int *)LS1C_GPIO_EN0;
            break;

        case 1:
            gpio_enx = (volatile unsigned int *)LS1C_GPIO_EN1;
            break;

        case 2:
            gpio_enx = (volatile unsigned int *)LS1C_GPIO_EN2;
            break;

        case 3:
            gpio_enx = (volatile unsigned int *)LS1C_GPIO_EN3;
            break;

        default:
            gpio_enx    = NULL;
            return gpio_enx;
    }

    return gpio_enx;
}

/*
 * gpio��ʼ��
 * @gpio gpio���ţ�ȡֵ��Χ[0, 127]
 * @mode gpio�Ĺ���ģʽ(���롢���)
 *
 * ��: ��gpio50��ʼ��Ϊ���
 * gpio_init(50, gpio_mode_output);
 */
void gpio_init(unsigned int gpio, gpio_mode_t mode)
{
    volatile unsigned int *gpio_enx = NULL;        // GPIO_ENx�Ĵ���
    unsigned int pin = GPIO_GET_PIN(gpio);

    // ��pin��Ϊ��ͨGPIO
    pin_set_purpose(gpio, PIN_PURPOSE_GPIO);

    // ����gpio����ģʽ(���롢���)
    gpio_enx  = gpio_get_en_reg(gpio);
    if (gpio_mode_output == mode)       // ���
    {
        reg_clr_one_bit(gpio_enx, pin);
    }
    else                                // ����
    {
        reg_set_one_bit(gpio_enx, pin);
    }

    return ;
}


/*
 * ��ָ��gpio����ߵ�ƽ��͵�ƽ
 * @gpio gpio���ţ�ȡֵ��Χ[0, 127]
 * @level ��ƽֵ
 *
 * ��: ��gpio50������͵�ƽ
 * gpio_set(50, gpio_level_low);
 */
void gpio_set(unsigned int gpio, gpio_level_t level)
{
    volatile unsigned int *gpio_outx = NULL;       // GPIO_OUTx�Ĵ���
    unsigned int port   = GPIO_GET_PORT(gpio);
    unsigned int pin    = GPIO_GET_PIN(gpio);

    // ��ȡ�Ĵ�����ַ
    switch (port)
    {
        case 0:
            gpio_outx = (volatile unsigned int *)LS1C_GPIO_OUT0;
            break;

        case 1:
            gpio_outx = (volatile unsigned int *)LS1C_GPIO_OUT1;
            break;

        case 2:
            gpio_outx = (volatile unsigned int *)LS1C_GPIO_OUT2;
            break;

        case 3:
            gpio_outx = (volatile unsigned int *)LS1C_GPIO_OUT3;
            break;

        default:        // ��ȷ�ĳ���Ӧ���ߵ����ֱ�ӷ���
            return ;
    }

    // ���
    if (gpio_level_low == level)
    {
        reg_clr_one_bit(gpio_outx, pin);
    }
    else
    {
        reg_set_one_bit(gpio_outx, pin);
    }

    return ;
}


/*
 * ��ȡָ��gpio���ŵ�ֵ
 * @gpio gpio���ţ�ȡֵ��Χ[0,127]
 *
 * ��: ��ȡgpio50�����ϵ�ֵ
 * gpio_level_t level;
 * level = gpio_get(50);
 */
unsigned int gpio_get(unsigned int gpio)
{
    volatile unsigned int *gpio_inx = NULL;        // GPIO_INx�Ĵ���
    unsigned int port   = GPIO_GET_PORT(gpio);
    unsigned int pin    = GPIO_GET_PIN(gpio);

    // ��ȡ�Ĵ�����ַ
    switch (port)
    {
        case 0:
            gpio_inx = (volatile unsigned int *)LS1C_GPIO_IN0;
            break;

        case 1:
            gpio_inx = (volatile unsigned int *)LS1C_GPIO_IN1;
            break;

        case 2:
            gpio_inx = (volatile unsigned int *)LS1C_GPIO_IN2;
            break;

        case 3:
            gpio_inx = (volatile unsigned int *)LS1C_GPIO_IN3;
            break;

        default:        // ���������̲�Ӧ���ߵ����ֱ�ӷ���
            return 0;
    }

    // ��ȡ
    return reg_get_bit(gpio_inx, pin);
}


/**
 * �����ж�����
 * @gpio gpio����
 * @type �����жϵ��������ߵ�ƽ�������͵�ƽ�����������ش��� or �½��ش���
 */
void gpio_set_irq_type(unsigned int gpio, gpio_irq_type_t type)
{
    volatile unsigned int *int_pol = NULL;     // �жϼ���ѡ��Ĵ���
    volatile unsigned int *int_edge = NULL;    // �жϱ���ѡ��Ĵ���
    unsigned int port = GPIO_GET_PORT(gpio);
    unsigned int pin  = GPIO_GET_PIN(gpio);

    // ��ȡ�Ĵ�����ַ
    switch (port)
    {
        case 0:     // GPIO[31:0]
            int_pol     = (volatile unsigned int *)LS1C_INT2_POL;
            int_edge    = (volatile unsigned int *)LS1C_INT2_EDGE;
            break;

        case 1:     // GPIO[63:32]
            int_pol     = (volatile unsigned int *)LS1C_INT3_POL;
            int_edge    = (volatile unsigned int *)LS1C_INT3_EDGE;
            break;

        case 2:     // GPIO[95:64]
            int_pol     = (volatile unsigned int *)LS1C_INT4_POL;
            int_edge    = (volatile unsigned int *)LS1C_INT4_EDGE;
            break;
    }

    // �����ж�����
    switch (type)
    {
        case IRQ_TYPE_EDGE_RISING:
            *int_pol    |= (1 << pin);
            *int_edge   |= (1 << pin);
            break;

        case IRQ_TYPE_EDGE_FALLING:
            *int_pol    &= ~(1 << pin);
            *int_edge   |= (1 << pin);
            break;

        case IRQ_TYPE_LEVEL_HIGH:
            *int_pol    |= (1 << pin);
            *int_edge   &= ~(1 << pin);
            break;

        case IRQ_TYPE_LEVEL_LOW:
            *int_pol    &= ~(1 << pin);
            *int_edge   &= ~(1 << pin);
            break;

        default:
            break;
    }

    return ;
}


    
