from Tests.test_crud import *
from Tests.test_thing_functions import test_thing_functions


def run_all_tests():

    test_add_thing()
    test_delete_thing()
    test_update_thing()
    test_get_by_id()
    test_thing_functions()
