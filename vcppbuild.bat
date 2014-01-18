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
cl.exe /MD /Zi /nologo /W3 /WX- /O2 /Oi /Oy- /GL /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_UNICODE" /D "UNICODE" /Gm- /EHsc /GS /Gy /fp:precise /Zc:wchar_t /Zc:forScope /I"..\ext\include" %1.cpp %2
del %1.obj