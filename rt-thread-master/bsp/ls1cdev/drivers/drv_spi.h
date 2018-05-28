/*
 * File      : drv_spi.h
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
 * 2017-11-02     ��Ϊ��       first version
 */

#ifndef LS1C_DRV_SPI_H
#define LS1C_DRV_SPI_H


#include "../libraries/ls1c_spi.h"


struct ls1c_spi
{
    unsigned char SPIx;     // LS1C_SPI_0 or LS1C_SPI_1
};


struct ls1c_spi_cs
{
    unsigned char cs;       // LS1C_SPI_CS_0, LS1C_SPI_CS_1, LS1C_SPI_CS_2 or LS1C_SPI_CS_3
};



/*
 * ��ʼ����ע����о1c��spi����
 * @SPI SPI���ߣ�����LS1C_SPI_0�� LS1C_SPI_1
 * @spi_bus_name ��������
 * @ret 
 */
rt_err_t ls1c_spi_bus_register(rt_uint8_t SPI, const char *spi_bus_name);


#endif

