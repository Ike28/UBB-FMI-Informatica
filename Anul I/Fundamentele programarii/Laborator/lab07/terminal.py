from Domain.bcolors import Colors
from Logic.file_management import load_file
from Tests.run_all_tests import run_all_tests
from UI.terminal_console import handle_multiple_commands


def open_terminal():
    print(f'\n  {Colors.DARK_GRAY}TERMINAL INVENTAR')
    print(f'\n  Introduceti help pentru a consulta sintaxa comenzilor.{Colors.END}')
    print(f'Introduceti comenzile dorite. Datele se separa doar prin virgula, iar comenzile doar prin punct si virgula:{Colors.END}\n')

    thing_list = load_file()  # cu fisiere json
    # thing_list = [] #cu consola

    thing_list = handle_multiple_commands(thing_list)


run_all_tests()
open_terminal()
