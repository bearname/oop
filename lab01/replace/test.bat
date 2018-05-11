set PROGRAM="%~1"

REM �������� ������ ��������� ��� �������� ���������� ������� ����������
%PROGRAM% input.txt "%TEMP%\output.txt"
if NOT ERRORLEVEL 1 goto err
echo test "invalid arguments count" succeeded 

REM �������� ������ ������ � ������ �����
%PROGRAM% empty.txt "%TEMP%\empty.txt" ma test
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\empty.txt" empty.txt
if ERRORLEVEL 1 goto err 
echo emtpy test succeeded

REM �������� ������ ��������� ��� ������ ������ ������
%PROGRAM% input.txt "%TEMP%\output.txt" "" "mama"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" check-empty-search.txt
if ERRORLEVEL 1 goto err
echo test "empty search string" succeeded

REM �������� ������ ��������� ��� ������ ������ ������
%PROGRAM% input.txt "output.txt" "It outclasses SCM tools like Subversion, CVS" "" 
if ERRORLEVEL 1 goto err
fc.exe "output.txt" check-empty-replace.txt
if ERRORLEVEL 1 goto err
echo test "empty replace string" succeeded

REM mama
%PROGRAM% input.txt "%TEMP%\output.txt" "ma" "mama" 
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" check-mama.txt
if ERRORLEvel 1 goto err
echo test "mama" succeeded

REM 1231234
%PROGRAM% input.txt "%TEMP%\output.txt" "1231234" "@!" 
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" check-1231234.txt
if ERRORLEvel 1 goto err
echo test "1231234" succeeded
                                          
REM ������� ��������� ��� ������ ��� ������������� ������ � �������� ����
%PROGRAM% input.txt %PROGRAM% "1231234" "@!" > "%TEMP%\output.txt"
if NOT ERRORLEVEL 1 goto err
echo test "data flushed to disk" succeeded

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1
