@setlocal enableextensions enabledelayedexpansion
@echo off
if exist "c:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\vcvarsall.bat" (
	call "c:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\vcvarsall.bat" x86
	goto compile
)
if exist "c:\Program Files (x86)\Microsoft Visual Studio 11.0\VC\vcvarsall.bat" ( 
	call "c:\Program Files (x86)\Microsoft Visual Studio 11.0\VC\vcvarsall.bat" x86
	goto compile
)
if exist "c:\Program Files (x86)\Microsoft Visual Studio 9.0\VC\vcvarsall.bat" (
	call "c:\Program Files (x86)\Microsoft Visual Studio 9.0\VC\vcvarsall.bat" x86
	goto compile
)
:compile
cl.exe /clr %1.cpp > nul
%1.exe
del %1.obj
pause