@echo off
set vboxmanage="C:\Program Files\Oracle\VirtualBox\vboxmanage.exe"
set vboxname=os1_%COMPUTERNAME%_%USERNAME%
..\ext\nasm\nasm -f bin -o os.img firstos.asm
%vboxmanage% unregistervm %vboxname% --delete 2> nul
%vboxmanage% createvm --name %vboxname% --basefolder %CD% --register
%vboxmanage% modifyvm %vboxname% --memory "256"
%vboxmanage% modifyvm %vboxname% --bioslogodisplaytime "1"
%vboxmanage% storagectl %vboxname% --name Floppy --add floppy --bootable on
%vboxmanage% storageattach %vboxname% --device 0 --storagectl Floppy --type fdd --medium %CD%\os.img
%vboxmanage% startvm %vboxname%
pause
%vboxmanage% controlvm %vboxname% poweroff
timeout /t 2 /nobreak > NUL
%vboxmanage% unregistervm %vboxname% --delete
