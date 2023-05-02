from Domain.thing import get_price, get_name, get_location, get_id, get_description


def test_thing_functions():
    test_get_id()
    test_get_name()
    test_get_location()
    test_get_description()
    test_get_price()


def test_parse_created_thing():
    testing_thing = [8, 'cutie5', 'O cutie goala si noua', 2.0, 'L2R3']
    return testing_thing


def test_get_id():
    assert get_id(test_parse_created_thing()) == 8


def test_get_name():
    assert get_name(test_parse_created_thing()) == 'cutie5'


def test_get_description():
    assert get_description(test_parse_created_thing()) == 'O cutie goala si noua'


def test_get_price():
    assert get_price(test_parse_created_thing()) == 2.0


def test_get_location():
    assert get_location(test_parse_created_thing()) == 'L2R3'
