# Comenzi de asamblare, linkeditare, debug si rulare multimodul asm-asm

# 1. Asamblare module asm
nasm -fobj lab11main.asm
nasm -fobj transform.asm

# 2. Linkeditare module asm
# * PE poate fi inlocuit de alta optiune pentru tip de fisier
# * console poate fi inlocuit de alta optiune pentru tip de aplicatie generata
# * start poate fi inlocuit de alt punct de intrare in program
# Optiunile se gasesc in ALINK.txt
alink lab11main.obj transform.obj -o PE -subsys console -entry start

# 3. Rulare
lab11main.exe

# 4. Debug
OLLYDBG.EXE lab11main.exe
