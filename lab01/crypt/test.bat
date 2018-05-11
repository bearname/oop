set PROGRAM="%~1"    

REM �������� ������ ��������� ��� �������� ���������� ������� ����������
%PROGRAM% 
if ERRORLEVEL EQU 0 goto err
echo test "invalid arguments count" succeeded       

REM �������� ������ ��������� ��� ������ ����� �������� �����
%PROGRAM% ""
if ERRORLEVEL EQU 0 goto err
echo test "empty input file name" succeeded 

REM �������� ������ ��������� ��� ���������� <action>
%PROGRAM% 213 input.txt "%TEMP%\output.txt" 24
if ERRORLEVEL EQU 0 goto err
echo test "invalid <action>" succeeded 
                                            
%PROGRAM% crypt empty.txt "%TEMP%\empty.txt" 17
if ERRORLEVEL EQU 0 goto err 
echo test "non existing input file"

%PROGRAM% crypt non-existing-file-name.txt "%TEMP%\non-existing-file-name.txt" 17
if ERRORLEVEL EQU 0 goto err 
echo test "non existing input file"

REM �������� ������ ��������� ��� ���������� ������� �����
%PROGRAM% crypt %PROGRAM% "%TEMP%\output.txt" 24
if ERRORLEVEL EQU 0 goto err
echo test "invalid input file name" succeeded 

REM �������� ������ ��������� ��� ������ ����� ��������� �����
%PROGRAM% crypt "" "%TEMP%\output.txt" 24
if ERRORLEVEL EQU 0 goto err
echo test "empty output file name" succeeded 

REM �������� ������ ��������� ��� ���������� �������� �����
%PROGRAM% crypt input.txt %PROGRAM% 255  
if ERRORLEVEL EQU 0 goto err
echo test "invalid output file name" succeeded 
                                              
REM �������� ������ ��������� ��� <key>, ���������� ������ �� �� ���������� ������� ���������
%PROGRAM% crypt input.txt "%TEMP%\output.txt" FF  
if ERRORLEVEL EQU 0 goto err
echo test "invalid notation" succeeded 

REM �������� ������ ���������, ����� <key> �� ������ � ���������� �������� 
%PROGRAM% crypt input.txt "%TEMP%\output.txt 999  
if ERRORLEVEL EQU 0 goto err
echo test "invalid range1" succeeded 

REM �������� ������ ���������, ����� <key> �� ������ � ���������� �������� 
%PROGRAM% crypt input.txt "%TEMP%\output.txt" -1
if ERRORLEVEL EQU 0 goto err
echo test "invalid range2" succeeded  
                                   
REM �������� ���������� � ������������
%PROGRAM% crypt input.txt "%TEMP%\input.crypt.txt" 56
if ERRORLEVEL EQU 1 goto err  
%PROGRAM% decrypt "%TEMP%\input.crypt.txt" "%TEMP%\input.decrypt.txt" 56
if ERRORLEVEL EQU 1 goto err
fc /B "%TEMP%\input.decrypt.txt" input.txt
if ERRORLEVEL 1 goto err
echo test "crypt and decrypt" succeeded

REM �������� ���������� � ������������ exe �����
%PROGRAM% crypt replace.exe "%TEMP%\replace.crypt.exe" 56
if ERRORLEVEL EQU 1 goto err  
%PROGRAM% decrypt "%TEMP%\replace.crypt.exe" "%TEMP%\replace.decrypt.exe" 56
if ERRORLEVEL EQU 1 goto err
fc.exe /B "%TEMP%\replace.decrypt.exe" replace.exe
if ERRORLEVEL 1 goto err
echo test "crypt and decrypt" succeeded

REM �������� ���������� � ������������ ������ ����
%PROGRAM% crypt %PROGRAM% "%TEMP%\crypt.crypt.exe" 56
if ERRORLEVEL EQU 1 goto err  
%PROGRAM% decrypt "%TEMP%\crypt.crypt.exe" "%TEMP%\crypt.decrypt.exe" 56
if ERRORLEVEL EQU 1 goto err
fc.exe /B "%TEMP%\crypt.decrypt.exe" %PROGRAM%
if ERRORLEVEL 1 goto err
echo test "crypt and decrypt" succeeded


ECHO Program testing succeeded :-)
EXIT 0

:err
ECHO Program testing failed :-(
EXIT 1