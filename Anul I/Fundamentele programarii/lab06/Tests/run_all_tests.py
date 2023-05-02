from Tests.test_crud import *
from Tests.test_thing_functions import test_thing_functions
from Tests.test_operatiuni import *
from Tests.test_terminal import test_execute_terminal_command
from Tests.test_undo import *
from Tests.test_redo import *


def run_all_tests():

    test_add_thing()
    test_delete_thing()
    test_update_thing()
    test_get_by_id()
    test_thing_functions()
    test_change_location()
    test_concat_to_description_by_price()
    test_sort_inventory_by_price()
    test_priciest_per_room()
    test_sum_at_location()
    test_execute_terminal_command()
    test_remove_last_in_undo()
    test_get_undo_tree()
    test_register_undo()
    test_clear_redo_tree()
    test_get_redo_tree()
    test_register_redo()
    test_remove_last_in_redo()
