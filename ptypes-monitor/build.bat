@echo off
call ../vcppbuild.bat monitor "/link user32.lib ../ext/libs/ptypes.lib"
monitor.exe
pause