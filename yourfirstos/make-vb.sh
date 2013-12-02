#!/bin/bash

vboxmanage=`which vboxmanage`
vboxname=os1_`hostname`_$USER
nasm -f bin -o os.img firstos.asm
$vboxmanage unregistervm $vboxname --delete 2> nul
$vboxmanage createvm --name $vboxname --basefolder $PWD --register
$vboxmanage modifyvm $vboxname --memory "256"
$vboxmanage modifyvm $vboxname --bioslogodisplaytime "1"
$vboxmanage storagectl $vboxname --name Floppy --add floppy --bootable on$PWD%CD%\os.img
$vboxmanage startvm $vboxname
pause
$vboxmanage controlvm $vboxname poweroff
timeout /t 2 /nobreak > NUL
$vboxmanage unregistervm $vboxname --delete