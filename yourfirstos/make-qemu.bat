..\ext\nasm\nasm -f bin -o os.flp firstos.asm
..\ext\qemu\qemu-system-x86_64.exe -L ..\ext\qemu -m 128 -fda os.flp