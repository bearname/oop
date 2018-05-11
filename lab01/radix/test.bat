set PROGRAM="%~1"
                          
REM �������� ������ ��������� ��� �������� ���������� ������� ����������
%PROGRAM% 
if ERRORLEVEL EQU 0 goto err
echo test "invalid arguments count" succeeded 
 
REM �������� ��� ������ ��������� <source notation>
%PROGRAM% "" 26 FF
if ERRORLEVEL EQU 0 goto err
echo test "empty <source notation>" succeeded 

REM ������������ ��� �������� <source notation>
%PROGRAM% 999999999999999999999 26 FF
if ERRORLEVEL EQU 0 goto err
echo test "overflow <source notation>" succeeded 

REM �������� ��� ������ ��������� <destination notation>
%PROGRAM% 26 "" FF
if ERRORLEVEL EQU 0 goto err
echo test "empty <destination notation>" succeeded

REM ������������ ��� �������� <destination notation>
%PROGRAM% 2 999999999999999999999 0101100
if ERRORLEVEL EQU 0 goto err
echo test "overflow <destination notation>" succeeded 
                                
REM �������� ��� ������ ��������� <value>
%PROGRAM% 18 26 ""
if ERRORLEVEL EQU 0 goto err
echo test "empty <value>" succeeded  

REM �������� ��� ��������� <value>, ���������� ������������ ������� � <source notation>
%PROGRAM% 2 26 %#42 
if ERRORLEVEL EQU 0 goto err
echo test "invalid <value>" succeeded  
     
REM �������� �������� ����� 010101 �� 56-�� ������� ��������� � 26-��
%PROGRAM% 56 26 010101 
if ERRORLEVEL EQU 0 goto err
echo test "010101 from 56th notation to 26th notation" succeeded                       

REM �������� �������� ����� ZF �� 2-�� ������� ��������� � 26-��
%PROGRAM% 36 56 ZF 
if ERRORLEVEL EQU 0 goto err
echo test "ZF from 36th notation to 56th notation" succeeded                       

REM �������� �������� ����� ZF �� 36-�� ������� ��������� � 23-��
%PROGRAM% 36 23 ZFZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ 
if ERRORLEVEL EQU 0 goto err
echo test "overflow" succeeded                       

REM �������� �������� ����� 010101 �� 2-�� ������� ��������� � 26-��
%PROGRAM% 2 26 010101 
if ERRORLEVEL EQU 1 goto err
echo test "010101 from 2th notation to 26th notation" succeeded                       

REM �������� �������� ����� 15436 �� 2-�� ������� ��������� � 26-��
%PROGRAM% 27 2 15436 
if ERRORLEVEL EQU 1 goto err
echo test "15436 from 27th notation to 2th notation" succeeded                       

REM �������� �������� ����� -174G �� 27-�� ������� ��������� � 3-��
%PROGRAM% 27 3 -174G 
if ERRORLEVEL EQU 1 goto err
echo test "-174G from 27th notation to 3th notation" succeeded                       

ECHO Program testing succeeded :-)
EXIT 0

:err
ECHO Program testing failed :-(
EXIT 1