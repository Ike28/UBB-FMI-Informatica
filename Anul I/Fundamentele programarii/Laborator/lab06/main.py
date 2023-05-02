from Logic.file_management import *
from UI.console import run_console
from Tests.run_all_tests import run_all_tests


def main():

    thing_list = load_file()  # cu fisiere json
    write_file([], 'undo_tree.txt')
    write_file([], 'redo_tree.txt')
    # thing_list = []  # cu consola
    thing_list = run_console(thing_list)


run_all_tests()
main()
