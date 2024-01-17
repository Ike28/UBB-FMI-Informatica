from Lexer import Lexer

lexer = Lexer()
fip, ts_const, ts_ident, mesaj = lexer.scan_program("programe/aria_perimetrul.bas")

print(mesaj + '\n')

print("Tabela de constante:")
print(ts_const)
print('\nTabela de identificatori:')
print(ts_ident)
print()

print("Forma interna a programului:")
for elem in fip:
    print(elem)
