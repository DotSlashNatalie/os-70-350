@echo off
call ../vcppbuild.bat main "/link /LIBPATH:../ext/libs"
main.exe
pause