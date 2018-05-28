// һЩ���õġ����õĽӿ�

#ifndef __OPENLOONGSON_PUBLIC_H
#define __OPENLOONGSON_PUBLIC_H


#include <stdio.h>


// pmon�ṩ�Ĵ�ӡ��������main()����
struct callvectors {
	int     (*open) (char *, int, int);
	int     (*close) (int);
	int     (*read) (int, void *, int);
	int     (*write) (int, void *, int);
	long long   (*lseek) (int, long long, int);
	int     (*printf) (const char *, ...);
	void    (*cacheflush) (void);
	char    *(*gets) (char *);
};
#define	myprintf (*callvec->printf)
#define	mygets   (*callvec->gets)
extern struct callvectors *callvec;


#define MIN(a, b)           ((a) > (b) ? (b) : (a))
#define MAX(a, b)           ((a) > (b) ? (a) : (b))

#define DIV_ROUND_UP(n, d)      (((n) + (d) - 1) / (d))

typedef enum
{
    FALSE=0, 
    TRUE=1
}BOOL;

/*
 * ��ָ���Ĵ�����ָ��λ��1
 * @reg �Ĵ�����ַ
 * @bit ��Ҫ��1����һbit
 */
void reg_set_one_bit(volatile unsigned int *reg, unsigned int bit);


/*
 * ��ָ���Ĵ�����ָ��λ����
 * @reg �Ĵ�����ַ
 * @bit ��Ҫ�������һbit
 */
void reg_clr_one_bit(volatile unsigned int *reg, unsigned int bit);


/*
 * ��ȡָ���Ĵ�����ָ��λ��ֵ
 * @reg �Ĵ�����ַ
 * @bit ��Ҫ��ȡֵ����һbit
 * @ret ָ��λ��ֵ
 */
unsigned int reg_get_bit(volatile unsigned int *reg, unsigned int bit);


/*
 * ��Ĵ�����д��8bit(һ���ֽ�)����
 * @data ��д�������
 * @addr �Ĵ�����ַ
 */
void reg_write_8(unsigned char data, volatile unsigned char *addr);


/*
 * �ӼĴ�������8bit(һ���ֽ�)����
 * @addr �Ĵ�����ַ
 * @ret ����������
 */
unsigned char reg_read_8(volatile unsigned char *addr);


/*
 * ��Ĵ�����дһ��32bit������
 * @data ��д�������
 * @addr �Ĵ�����ַ
 */
void reg_write_32(unsigned int data, volatile unsigned int *addr);


/*
 * �ӼĴ�������һ��32bit����
 * @addr �Ĵ�����ַ
 * @ret ����������
 */
unsigned int reg_read_32(volatile unsigned int *addr);


/**
 * ffs - find first bit set
 * @x: the word to search
 */
int ls1c_ffs(int x);

/*
 * fls - find last (most-significant) bit set
 * @x: the word to search
 *
 * This is defined the same way as ffs.
 * Note fls(0) = 0, fls(1) = 1, fls(0x80000000) = 32.
 */
int ls1c_fls(int x);


#endif

