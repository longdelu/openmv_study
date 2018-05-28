/*
 * File      : ls1c_spi.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2012, RT-Thread Development Team
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
 * 2017-10-23     ��Ϊ��       first version
 */

// Ӳ��spi�ӿڵ�ͷ�ļ�

#ifndef __OPENLOONGSON_SPI_H
#define __OPENLOONGSON_SPI_H


// SPIģ����
#define LS1C_SPI_0                      (0)
#define LS1C_SPI_1                      (1)

// Ƭѡ
#define LS1C_SPI_CS_0                   (0)
#define LS1C_SPI_CS_1                   (1)
#define LS1C_SPI_CS_2                   (2)
#define LS1C_SPI_CS_3                   (3)

// ʱ�Ӽ��Ժ���λ
#define SPI_CPOL_1                      (1)
#define SPI_CPOL_0                      (0)
#define SPI_CPHA_1                      (1)
#define SPI_CPHA_0                      (0)


// �Ĵ���ƫ��
#define LS1C_SPI_SPCR_OFFSET                (0)     // ���ƼĴ���
#define LS1C_SPI_SPSR_OFFSET                (1)     // ״̬�Ĵ���
#define LS1C_SPI_TxFIFO_OFFSET              (2)     // ���͵����ݼĴ�������������ݼĴ�����ƫ����ͬ
#define LS1C_SPI_RxFIFO_OFFSET              (2)     // ���յ����ݼĴ������뷢�����ݼĴ�����ƫ����ͬ
#define LS1C_SPI_SPER_OFFSET                (3)     // �ⲿ�Ĵ���
#define LS1C_SPI_SFC_PARAM_OFFSET           (4)     // �������ƼĴ���
#define LS1C_SPI_SFC_SOFTCS_OFFSET          (5)     // Ƭѡ���ƼĴ���
#define LS1C_SPI_SFC_TIMING_OFFSET          (6)     // ʱ����ƼĴ���

// �Ĵ���SPCR�е�λ��
#define LS1C_SPI_SPCR_SPIE_BIT              (7)
#define LS1C_SPI_SPCR_SPIE_MASK             (0x01 << LS1C_SPI_SPCR_SPIE_BIT)
#define LS1C_SPI_SPCR_SPE_BIT               (6)
#define LS1C_SPI_SPCR_SPE_MASK              (0x01 << LS1C_SPI_SPCR_SPE_BIT)
#define LS1C_SPI_SPCR_CPOL_BIT              (3)
#define LS1C_SPI_SPCR_CPOL_MASK             (0x01 << LS1C_SPI_SPCR_CPOL_BIT)
#define LS1C_SPI_SPCR_CPHA_BIT              (2)
#define LS1C_SPI_SPCR_CPHA_MASK             (0x01 << LS1C_SPI_SPCR_CPHA_BIT)
#define LS1C_SPI_SPCR_SPR_BIT               (0)
#define LS1C_SPI_SPCR_SPR_MASK              (0x03 << LS1C_SPI_SPCR_SPR_BIT)

// �Ĵ���SPSR�е�λ��
#define LS1C_SPI_SPSR_SPIF_BIT              (7)
#define LS1C_SPI_SPSR_SPIF_MASK             (0x01 << LS1C_SPI_SPSR_SPIF_BIT)
#define LS1C_SPI_SPSR_WCOL_BIT              (6)
#define LS1C_SPI_SPSR_WCOL_MASK             (0x01 << LS1C_SPI_SPSR_WCOL_BIT)

// �Ĵ���SPER�е�λ��
#define LS1C_SPI_SPER_SPRE_BIT              (0)
#define LS1C_SPI_SPER_SPRE_MASK             (0x3 << LS1C_SPI_SPER_SPRE_BIT)

// �Ĵ���SFC_SOFTCS��λ��
#define LS1C_SPI_SFC_SOFTCS_CSN_BIT         (4)
#define LS1C_SPI_SFC_SOFTCS_CSN_MASK        (0x0f << LS1C_SPI_SFC_SOFTCS_CSN_BIT)
#define LS1C_SPI_SFC_SOFTCS_CSEN_BIT        (0)
#define LS1C_SPI_SFC_SOFTCS_CSEN_MASK       (0x0f << LS1C_SPI_SFC_SOFTCS_CSEN_BIT)

// ���ͳ�ʱ������ֵ
#define LS1C_SPI_TX_TIMEOUT                 (20000)



/*
 * ��ȡָ��SPIģ��Ļ���ַ
 * @SPIx SPIģ��ı��
 */
inline void *ls1c_spi_get_base(unsigned char SPIx);


/*
 * ����ʱ��
 * @spi_base ����ַ
 * @max_hz ���Ƶ�ʣ���λhz
 */
void ls1c_spi_set_clock(void *spi_base, unsigned long max_hz);


/*
 * ����ͨ��ģʽ(ʱ�Ӽ��Ժ���λ)
 * @spi_base ����ַ
 * @cpol ʱ�Ӽ���
 * @cpha ʱ����λ
 */
void ls1c_spi_set_mode(void *spi_base, unsigned char cpol, unsigned char cpha);


/*
 * ����ָ��ƬѡΪָ��״̬
 * @spi_base ����ַ
 * @cs Ƭѡ
 * @new_status Ƭѡ���ŵ���״̬��ȡֵΪ0��1�����ߵ�ƽ��͵�ƽ
 */
void ls1c_spi_set_cs(void *spi_base, unsigned char cs, int new_status);


/*
 * ͨ��ָ��SPI���ͽ���һ���ֽ�
 * ע�⣬�ڶ������ϵͳ�У��˺�����Ҫ���⡣
 * ����֤�ں�ĳ�����豸�շ�ĳ���ֽڵĹ����У����ܱ��л�����������ͬʱ���������ͬһ��SPI�����ϵĴ��豸ͨ��
 * ��Ϊ��о1c��ÿ·SPI�Ͽ��ܽ��в�ͬ�Ĵ��豸��ͨ��Ƶ�ʡ�ģʽ�ȿ��ܲ�ͬ
 * @spi_base ����ַ
 * @tx_ch �����͵�����
 * @ret �յ�������
 */
unsigned char ls1c_spi_txrx_byte(void *spi_base, unsigned char tx_ch);


/*
 * ��ӡָ��SPIģ������мĴ�����ֵ
 * @spi_base ����ַ
 */
void ls1c_spi_print_all_regs_info(void *spi_base);




#endif

