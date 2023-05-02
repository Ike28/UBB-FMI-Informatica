from Logic.crud import delete_thing, update_thing, add_thing, get_by_id


def test_add_thing():

    testing_inventory = []
    add_thing(testing_inventory, 8, 'cutie5','O cutie goala si noua', 2, 'L2R3')
    assert testing_inventory == [[8, 'cutie5', 'O cutie goala si noua', 2.0, 'L2R3']]


def test_delete_thing():
    testing_inventory = [[8, 'cutie5', 'O cutie goala si noua', 2.0, 'L2R3']]
    testing_inventory = delete_thing(testing_inventory, 8)
    assert testing_inventory == []


def test_update_thing():
    testing_inventory = [[0, 'cutie5', 'O cutie goala si noua', 2.0, 'L2R3']]
    testing_thing = [0, 'aaaa', 'asta tre sa fie aici PTR json', 0.0, '0000']
    testing_inventory = update_thing(testing_inventory,testing_thing)
    assert testing_inventory == [[0, 'aaaa', 'asta tre sa fie aici PTR json', 0.0, '0000']]


def test_get_by_id():
    testing_inventory = [[8, 'cutie5', 'O cutie goala si noua', 2.0, 'L2R3']]
    assert get_by_id(testing_inventory, 8) == [8, 'cutie5', 'O cutie goala si noua', 2.0, 'L2R3']
    assert get_by_id(testing_inventory, 9) is None
