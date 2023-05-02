from datetime import date

import jsonpickle

from Domain.card_client import CardClient
from Domain.card_client_validator import CardClientValidate


def test_card_constructor_validator():
    with open('test_card_ids.txt', 'w') as f:
        f.write(jsonpickle.encode({}))
    c = CardClient('aaa', 'bbb', '5010809220224', date(2020, 1, 1), 300, 1)
    c_val = CardClientValidate('test_card_ids.txt')
    c_val.validate(c)
    assert c.id == 1
    c2 = CardClient('ccc', 'ddd', '6010809400400', date(2005, 1, 1), 200, 1)
    try:
        c_val.validate(c2)
    except:
        c2 = CardClient('ccc', 'ddd', '6010809400400', date(2005, 1, 1), 200, 2)
        c_val.validate(c2)
    assert c2.id == 2
