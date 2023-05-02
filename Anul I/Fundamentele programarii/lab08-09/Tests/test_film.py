import jsonpickle

from Domain.film import Film
from Domain.film_validator import FilmValidate


def test_film_constructor_validator():
    with open('test_film_ids.txt', 'w') as f:
        f.write(jsonpickle.encode([]))
    f = Film('hhh', 1987, 18, True, 1)
    f_val = FilmValidate('test_film_ids.txt')
    f_val.validate(f)
    assert f.id == 1
    f2 = Film('aaa', 1989, 20, False, 1)
    try:
        f_val.validate(f2)
    except:
        f2 = Film('aaa', 1989, 20, False, 2)
        f_val.validate(f2)
    assert f2.id == 2
