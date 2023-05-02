from Domain.artist import Artist
from Domain.artist_validator import ArtistValidator


def test_artist_constructor_validator():

    a1 = Artist('1', 'Ibeala Ibeulu', 'abstract')
    a_val = ArtistValidator()
    a_val.validate(a1)
    assert a1.id == '1'
    a2 = Artist('1', 'Daniel Vacaretu', 'cubism')
    try:
        a_val.validate(a2)
    except:
        a2 = Artist('2', 'Daniel Vacaretu', 'clasic')
        a_val.validate(a2)
    assert a2.id == '2'
