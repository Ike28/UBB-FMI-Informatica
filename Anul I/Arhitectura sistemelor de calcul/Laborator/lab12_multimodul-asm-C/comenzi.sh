# Comenzi de compilare, debug si rulare multimodul asm-C
# Se utilizeaza VS (x86) Native Tools Command Prompt

# 1. Asamblare module asm
#	 * fara posibilitate de debug
nasm lab12tobinary.asm -fwin32 -o lab12tobinary.obj
nasm lab12tohex.asm -fwin32 -o lab12tohex.obj
#	 * cu posibilitate ulterioara de debug
nasm lab12tobinary.asm -fwin32 -g -o lab12tobinary.obj
nasm lab12tohex.asm -fwin32 -g -o lab12tohex.obj

# 2. Compilare program C cu linkeditare module asm
#	 * fara posibilitate de debug
cl lab12main.c /link lab12tobinary.obj lab12tohex.obj
#	 * cu posibilitate ulterioara de debug
cl /Z7 lab12main.c /link lab12tobinary.obj lab12tohex.obj
#	 * cu posibilitate de debug in Visual Studio
cl /Z{7|i|I} lab12main.c /link lab12tobinary.obj lab12tohex.obj

# 3. Rulare
lab12main.exe

# 4. Debug - Open in OllyDBG la lab12main.exe
