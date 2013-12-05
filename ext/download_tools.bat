@echo off

if NOT [%1] == [] goto end2

:start
bitsadmin /complete test > nul
bitsadmin /create test > log.txt
bitsadmin /addfile test http://cdn.srchub.org/ostools.exe %CD%\ostools.exe >> log.txt
bitsadmin /resume test >> log.txt
bitsadmin /setnotifycmdline test "%SystemRoot%\system32\cmd.exe" "/c %CD%\download_tools.bat %CD%" >> log.txt
goto end3

:end2
bitsadmin.exe /complete test > nul
%1\ostools.exe -gm2 -y

:end3