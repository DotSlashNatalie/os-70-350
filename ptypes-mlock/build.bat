@echo off
call ../vcppbuild.bat mlock "/link user32.lib ../ext/libs/ptypes.lib"
mlock.exe
pause