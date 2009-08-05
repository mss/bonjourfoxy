@echo off
vcbuild >NUL 2>NUL
if %ERRORLEVEL% == -1 GOTO BUILD
echo Looks like vcvarsall.bat has not been called...
call "%VS90COMNTOOLS%vsvars32.bat"
:BUILD
IF "%1" == "clean" FOR /F %%t IN ('dir /ad/b') do IF EXIST %%t\bf%%t.vcproj @vcbuild %%t\bf%%t.vcproj /clean /nologo /platform=Win32 Debug
FOR /F %%t IN ('dir /ad/b') do IF EXIST %%t\bf%%t.vcproj @vcbuild %%t\bf%%t.vcproj /nologo /platform=Win32 Debug