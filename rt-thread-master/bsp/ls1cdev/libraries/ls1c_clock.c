/*************************************************************************
 *
 * ʱ����غ���
 *
 *************************************************************************/


#include "ls1c_regs.h"
#include "ls1c_public.h"


// �����Ƶ��
#define AHB_CLK                 (24000000)
#define APB_CLK                 (AHB_CLK)


// START_FREQ�Ĵ���bits
#define M_PLL_SHIFT             (8)
#define M_PLL                   (0xff << M_PLL_SHIFT)       // PLL��Ƶϵ������������
#define FRAC_N_SHIFT            (16)
#define FRAC_N                  (0xff << FRAC_N_SHIFT)      // PLL��Ƶϵ����С������
#define DIV_SDRAM_SHIFT         (0)
#define DIV_SDRAM               (0x3  << DIV_SDRAM_SHIFT)

// CLK_DIV_PARAM�Ĵ���bits
#define DIV_PIX_EN              (0x1  << 31)
#define DIV_PIX                 (0x7f << 24)
#define DIV_CAM_EN              (0x1  << 23)
#define DIV_CAM                 (0x7f << 16)
#define DIV_CPU_EN              (0x1  << 15)
#define DIV_CPU                 (0x7f << 8)
#define DIV_PIX_VALID           (0x1  << 5)
#define DIV_PIX_SEL             (0x1  << 4)
#define DIV_CAM_VALID           (0x1  << 3)
#define DIV_CAM_SEL             (0x1  << 2)
#define DIV_CPU_VALID           (0x1  << 1)
#define DIV_CPU_SEL             (0x1  << 0)

#define DIV_PIX_SHIFT           (24)
#define DIV_CAM_SHIFT           (16)
#define DIV_CPU_SHIFT           (8)


/*
 * ��ȡPLLƵ��
 * @ret PLLƵ��
 */
unsigned long clk_get_pll_rate(void)
{
    unsigned int ctrl;
    unsigned long pll_rate = 0;

    ctrl = reg_read_32((volatile unsigned int *)LS1C_START_FREQ);
    pll_rate = (((ctrl & M_PLL) >> M_PLL_SHIFT) + ((ctrl & FRAC_N) >> FRAC_N_SHIFT)) * APB_CLK / 4;
    
    return pll_rate;
}


/*
 * ��ȡCPUƵ��
 * @ret CPUƵ��
 */
unsigned long clk_get_cpu_rate(void)
{
    unsigned long pll_rate, cpu_rate;
    unsigned int ctrl;

    pll_rate = clk_get_pll_rate();
    ctrl = reg_read_32((volatile unsigned int *)LS1C_CLK_DIV_PARAM);

    // ѡ��ʱ����Դ
    if (DIV_CPU_SEL & ctrl)     // pll��Ƶ��Ϊʱ���ź�
    {
        if (DIV_CPU_EN & ctrl)
        {
            cpu_rate = pll_rate / ((ctrl & DIV_CPU) >> DIV_CPU_SHIFT);
        }
        else
        {
            cpu_rate = pll_rate / 2;
        }
    }
    else                        // bypassģʽ��������Ϊʱ������
    {
        cpu_rate = APB_CLK;
    }

    return cpu_rate;
}


/*
 * ��ȡDDRƵ��
 * @ret DDRƵ��
 */
unsigned long clk_get_ddr_rate(void)
{
    unsigned long cpu_rate = 0;
    unsigned long ddr_rate = 0;
    unsigned int ctrl;

    cpu_rate = clk_get_cpu_rate();
    ctrl = reg_read_32((volatile unsigned int *)LS1C_START_FREQ);
    ctrl = (ctrl & DIV_SDRAM) >> DIV_SDRAM_SHIFT;

    switch (ctrl)
    {
        case 0:
            ddr_rate = cpu_rate / 2;
            break;

        case 1:
            ddr_rate = cpu_rate / 4;
            break;

        case 2:
        case 3:
            ddr_rate = cpu_rate / 3;
            break;
    }

    return ddr_rate;
}


/*
 * ��ȡAPBƵ��
 * @ret APBƵ��
 */
unsigned long clk_get_apb_rate(void)
{
    return clk_get_ddr_rate();
}


/*
 * ��ȡDCƵ��
 * @ret DCƵ��
 */
unsigned long clk_get_dc_rate(void)
{
    unsigned long pll_rate, dc_rate;
    unsigned int ctrl;

    pll_rate = clk_get_pll_rate();
    ctrl = reg_read_32((volatile unsigned int *)LS1C_CLK_DIV_PARAM);

    dc_rate = pll_rate / ((ctrl & DIV_PIX) >> DIV_PIX_SHIFT);

    return dc_rate;
}



