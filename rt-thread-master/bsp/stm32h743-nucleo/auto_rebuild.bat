::clean output files
del *.log /s
del *.dblite /s
del project.* /s
del *.scvd /s

rd /s /q .\build
rd /s /q .\settings
rd /s /q .\DebugConfig

::start cmd window and do the command
::start cmd.exe /c "scons --target=mdk5 -s"
start cmd.exe /c "scons --target=iar -s&&scons --target=mdk5 -s"

::start ��������һ��Ӧ��
::cmd /k ��ʾcmd���������ִ����󲻹رմ��ڡ�
::���Ҫ��ִ����ɺ�رմ��ڿ�����/c ��
::��ϸ��ʹ��cmd/?�鿴

::"����1&&����2&&.." 
::��Ҫִ�еĶ�������ʹ������ȫ�����������������������&&�ָ���
::���ֻ��һ��������������Ҳ���ԡ�

::�磺
::@echo off  
::start cmd /k "cd/d E:\&&echo hello&&pause&&ping www.163.com"