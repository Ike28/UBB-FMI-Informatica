from Domain.painting import Painting
from Domain.painting_validator import PaintingValidator


def test_painting_constructor_validator():

    p1 = Painting('1', '1', 'Human extinction', '300000', '1895')
    p_val = PaintingValidator()
    p1 = p_val.validate(p1)
    assert p1.id == '1'
    assert p1.price == 300000
    assert p1.year == 1895
    p2 = Painting('1', '1', 'Bourrasque', 'gratis', '1940')
    try:
        p2 = p_val.validate(p2)
    except:
        p2 = Painting('2', '1', 'Le Rossignol', '500000', '1940')
        p2 = p_val.validate(p2)
    assert p2.id == '2'
    assert p2.price == 500000
