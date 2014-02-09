@echo off
call ../vcppbuild.bat semaphore "/link user32.lib ../ext/libs/ptypes.lib"
semaphore.exe
pause