@echo off
call ../vcppbuild.bat client "/link /LIBPATH:../ext/libs ptypes.lib /SUBSYSTEM:CONSOLE"
call ../vcppbuild.bat server "/link /LIBPATH:../ext/libs ptypes.lib /SUBSYSTEM:CONSOLE"