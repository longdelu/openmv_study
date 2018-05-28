/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DRV_NAND_H
#define __DRV_NAND_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <rtthread.h>
#include <board.h>
#include "stm32f4xx.h"
#include <rtdevice.h>
     
//********************************************************************************
//����˵��
//V1.1 20160520
//1,����Ӳ��ECC֧��(������NAND_ECC_SECTOR_SIZE��СΪ��λ���ж�дʱ����)
//2,����NAND_Delay����,���ڵȴ�tADL/tWHR
//3,����NAND_WritePageConst����,������Ѱ����.
//V1.2 20160525
//1,ȥ��NAND_SEC_SIZE�궨�壬��NAND_ECC_SECTOR_SIZE���
//2,ȥ��nand_dev�ṹ�������secbufָ�룬�ò���
////////////////////////////////////////////////////////////////////////////////// 	
 
#define NAND_MAX_PAGE_SIZE			4096		//����NAND FLASH������PAGE��С��������SPARE������Ĭ��4096�ֽ�
#define NAND_ECC_SECTOR_SIZE		512			//ִ��ECC����ĵ�Ԫ��С��Ĭ��512�ֽ�

//NAND���Խṹ��
typedef struct
{
    uint16_t page_totalsize;     	//ÿҳ�ܴ�С��main����spare���ܺ�
    uint16_t page_mainsize;      	//ÿҳ��main����С
    uint16_t page_sparesize;     	//ÿҳ��spare����С
    uint8_t  block_pagenum;      	//ÿ���������ҳ����
    uint16_t plane_blocknum;     	//ÿ��plane�����Ŀ�����
    uint16_t block_totalnum;     	//�ܵĿ�����
    uint16_t good_blocknum;      	//�ÿ�����    
    uint16_t valid_blocknum;     	//��Ч������(���ļ�ϵͳʹ�õĺÿ�����)
    uint32_t id;             		//NAND FLASH ID
    uint16_t *lut;      			   	//LUT�������߼���-�����ת��
	uint32_t ecc_hard;				//Ӳ�����������ECCֵ
	uint32_t ecc_hdbuf[NAND_MAX_PAGE_SIZE/NAND_ECC_SECTOR_SIZE];//ECCӲ������ֵ������  	
	uint32_t ecc_rdbuf[NAND_MAX_PAGE_SIZE/NAND_ECC_SECTOR_SIZE];//ECC��ȡ��ֵ������
}nand_attriute;      

extern nand_attriute nand_dev;				//nand��Ҫ�����ṹ�� 

//λ������,ʵ��51���Ƶ�GPIO���ƹ���
//����ʵ��˼��,�ο�<<CM3Ȩ��ָ��>>������(87ҳ~92ҳ).M4ͬM3����,ֻ�ǼĴ�����ַ����.
//IO�ڲ����궨��
#define GPIOD_IDR_Addr    (GPIOD_BASE+16) //0x40020C10 
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //���� 

#define NAND_RB  				 PDin(6) 	//NAND Flash����/æ���� 

#define NAND_ADDRESS			((rt_uint32_t)0x80000000)	//nand flash�ķ��ʵ�ַ,��NCE3,��ַΪ:0X8000 0000
#define NAND_CMD				(uint32_t)(0x010000)		//��������
#define NAND_ADDR				(uint32_t)(0x020000)		//���͵�ַ


//*((volatile rt_uint8_t *) 0X80000000)
//*((volatile rt_uint8_t *) 0X80010000)
//*((volatile rt_uint8_t *) 0X80020000)


//NAND FLASH����
#define NAND_READID         	0X90    	//��IDָ��
#define NAND_FEATURE			0XEF    	//��������ָ��
#define NAND_RESET          	0XFF    	//��λNAND
#define NAND_READSTA        	0X70   	 	//��״̬
#define NAND_AREA_A         	0X00   
#define NAND_AREA_TRUE1     	0X30  
#define NAND_WRITE0        	 	0X80
#define NAND_WRITE_TURE1    	0X10
#define NAND_ERASE0        	 	0X60
#define NAND_ERASE1         	0XD0
#define NAND_MOVEDATA_CMD0  	0X00
#define NAND_MOVEDATA_CMD1  	0X35
#define NAND_MOVEDATA_CMD2  	0X85
#define NAND_MOVEDATA_CMD3  	0X10

//NAND FLASH״̬
#define NSTA_READY       	   	0X40		//nand�Ѿ�׼����
#define NSTA_ERROR				0X01		//nand����
#define NSTA_TIMEOUT        	0X02		//��ʱ
#define NSTA_ECC1BITERR       	0X03		//ECC 1bit����
#define NSTA_ECC2BITERR       	0X04		//ECC 2bit���ϴ���


//NAND FLASH�ͺźͶ�Ӧ��ID��
#define MT29F4G08ABADA			0XDC909556	//MT29F4G08ABADA
#define MT29F16G08ABABA			0X48002689	//MT29F16G08ABABA

 struct stm32f4_nand
{
    rt_uint8_t id[5];
    struct rt_mutex lock;
    struct rt_completion comp;
};


void NAND_Init(void);
uint8_t NAND_ModeSet(uint8_t mode);
uint32_t NAND_ReadID(void);
uint8_t NAND_ReadStatus(void);
uint8_t NAND_WaitForReady(void);
//static rt_uint8_t nand_reset(void);
uint8_t NAND_WaitRB(__IO uint8_t rb);
void NAND_Delay(volatile rt_uint32_t i);
uint8_t NAND_ReadPage(uint32_t PageNum,uint16_t ColNum,uint8_t *pBuffer,uint16_t NumByteToRead);
uint8_t NAND_ReadPageComp(uint32_t PageNum,uint16_t ColNum,uint32_t CmpVal,uint16_t NumByteToRead,uint16_t *NumByteEqual);
uint8_t NAND_WritePage(uint32_t PageNum,uint16_t ColNum,uint8_t *pBuffer,uint16_t NumByteToWrite);
uint8_t NAND_WritePageConst(uint32_t PageNum,uint16_t ColNum,uint32_t cval,uint16_t NumByteToWrite);
uint8_t NAND_CopyPageWithoutWrite(uint32_t Source_PageNum,uint32_t Dest_PageNum);
uint8_t NAND_CopyPageWithWrite(uint32_t Source_PageNum,uint32_t Dest_PageNum,uint16_t ColNum,uint8_t *pBuffer,uint16_t NumByteToWrite);
uint8_t NAND_ReadSpare(uint32_t PageNum,uint16_t ColNum,uint8_t *pBuffer,uint16_t NumByteToRead);
uint8_t NAND_WriteSpare(uint32_t PageNum,uint16_t ColNum,uint8_t *pBuffer,uint16_t NumByteToRead);
uint8_t NAND_EraseBlock(uint32_t BlockNum);
void NAND_EraseChip(void);

uint16_t NAND_ECC_Get_OE(uint8_t oe,uint32_t eccval);
uint8_t NAND_ECC_Correction(uint8_t* data_buf,uint32_t eccrd,uint32_t ecccl);
int nand_hy27uf_hw_init(void);

#ifdef __cplusplus
}
#endif

#endif
