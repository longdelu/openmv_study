-- cn --
����Ҫ���ɹ����ļ�:
1. �޸ĵ�ǰ�ļ����� rtconfig.py :
CROSS_TOOL='keil'           #ʹ�õĹ�����.
STM32_TYPE = 'STM32F10X_HD' #STM32��Ӧ���ͺ�.
EXEC_PATH 	= 'C:/Keil' #Keil��װ·��.
IAR_PATH 	= 'C:/Program Files/IAR Systems/Embedded Workbench 6.0 Evaluation' #IAR��װ·��.
2. �޸ĵ�ǰ�ļ����� rtconfig.h ������Ҫ�Ĺ���.
3. MDK���ڵ�ǰ�ļ�����ִ�� scons --target=mdk  �� scons --target=mdk4 ����MDK 4�����ļ� project.uvproj
        ���ڵ�ǰ�ļ�����ִ�� scons --target=mdk5 ����MDK 5�����ļ� project.uvprojx
   IAR���ڵ�ǰ�ļ�����ִ�� scons --target=iar ����IAR���� project.eww.
4. ��bsp\stm32f10x\drivers��board.h��STM32_SRAM_SIZE��ֵ�޸�Ϊ��оƬSRAM��Сһ��.

note: ��Ҫ��װ python 2.7,scons.
      ���������ο�http://www.rt-thread.org/book/13.html
                  ��http://www.rt-thread.org/dokuwiki/doku.php?id=%E9%85%8D%E7%BD%AErt-thread%E5%BC%80%E5%8F%91%E7%8E%AF%E5%A2%83

-- en --
Generate project files as needed:
1. Modify the files in the current folder:
CROSS_TOOL='keil'           #The tool chain in use.
STM32_TYPE = 'STM32F10X_HD' #The type of stm32.
EXEC_PATH 	= 'C:/Keil' #The installation path of the Keil.
IAR_PATH 	= 'C:/Program Files/IAR Systems/Embedded Workbench 6.0 Evaluation' #The installation path of the IAR.
2. Configure the required functionality by modifying rtconfig.h in the current folder.
3. MDK:Execute the scons --target=mdk or scons --target=mdk4 in the current folder to generate the MDK4 project project.uvproj.
       Or execute the scons --target=mdk5 in the current folder to generate the MDK5 project project.uvprojx.
   IAR:Execute the scons --target=iar in the current folder to generate the IAR project project.eww.
4. Change the value of STM32_SRAM_SIZE in board.h(bsp\stm32f10x\drivers) to match the chip SRAM size.

note:Need to install python 2.7 and scons.
     For more information, please refer to the website http://www.rt-thread.org/book/13.html
                                               and     http://www.rt-thread.org/dokuwiki/doku.php?id=%E9%85%8D%E7%BD%AErt-thread%E5%BC%80%E5%8F%91%E7%8E%AF%E5%A2%83


