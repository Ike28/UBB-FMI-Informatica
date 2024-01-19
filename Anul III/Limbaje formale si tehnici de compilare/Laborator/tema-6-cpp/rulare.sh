# descarcati asm-tools: https://www.cs.ubbcluj.ro/~vancea/asc/files/ASM_tools.zip
bison -d analyser.y
flex analyser.l
gcc lex.yy.c analyser.tab.c -o analyser -std=c99
./analyser < program.cpp > program.asm
# deschideti npp din asm-tools si deschideti program.asm
# Ctrl+F7: asamblare
# Ctrl+F6: rulare
# F6: deschide debug in ollydbg
