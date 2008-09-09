@echo off
C:\Python25\python setup.py py2exe
copy dist\bonjour2content-json.exe ..\bin
rmdir /s/q build
rmdir /s/q dist