from Logic.file_management import *
from UI.console import run_console
from Tests.run_all_tests import run_all_tests


def main():

    thing_list = load_file() #nu imi merge cu json

    #thing_list = []
    thing_list = run_console(thing_list)


run_all_tests()
main()
