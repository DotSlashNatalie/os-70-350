@echo off
::pushd ..
::set parent=%cd%
::popd
call ../vcppbuild.bat main "/link /LIBPATH:../ext/libs"
main.exe
pause