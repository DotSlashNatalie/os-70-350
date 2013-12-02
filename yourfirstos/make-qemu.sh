#!/bin/bash

nasm -f bin -o os.flp firstos.asm
qemu-system-x86_64.exe -m 128 -fda os.flp