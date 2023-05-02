import jsonpickle
from datetime import date, time
from Domain.booking import Booking
from Domain.booking_validator import BookingValidate
from Domain.card_client import CardClient
from Domain.film import Film


def test_booking_constructor_validator():
    with open('test_booking_ids.txt', 'w') as f:
        f.write(jsonpickle.encode([]))
    b = Booking(Film('aaa', 1900, 20, True, 3), date(2020, 10, 10), time(10, 10), CardClient('bbb', 'ccc', '6010810400400', date(2005, 1, 1), 300, 2), 1)
    b_val = BookingValidate('test_booking_ids.txt')
    b_val.validate(b)
    assert b.id == 1
    b2 = Booking(Film('uuu', 1980, 20, True, 4), date(2020, 10, 10), time(20, 20), CardClient('bbb', 'ccc', '6010810400400', date(2005, 1, 1), 300, 2), 1)
    try:
        b_val.validate(b2)
    except:
        b2 = Booking(Film('uuu', 1980, 20, True, 4), date(2020, 10, 10), time(20, 20), CardClient('bbb', 'ccc', '6010810400400', date(2005, 1, 1), 300, 2), 2)
        b_val.validate(b2)
    assert b2.id == 2
