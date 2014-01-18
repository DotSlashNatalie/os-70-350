@echo off
call ../vcppbuild.bat main "/link user32.lib ../ext/libs/ptypes.lib"
main.exe
pause