import jsonpickle

from Domain.artist_validator import ArtistValidator
from Repository.file_repository import FileRepository
from Service.artist_service import ArtistService


def test_artist_service():
    with open('test_file2.txt', 'w') as f:
        f.write(jsonpickle.encode({}))
    a_repo = FileRepository('test_file2.txt')
    a_val = ArtistValidator()
    a_service = ArtistService(a_repo, a_val)

    # TEST FUNCTIONALITATEA 1
    a_service.create('1', 'Alexandru Vancea', 'abstract')
    try:
        a_service.create('2', 'Pablo Diego Jose Francisco de Paula Juan Nepomuceno Cipriano de la Santisima Trinidad Ruiz Picasso', 'cubism')
    except ValueError:
        a_service.create('2', 'Nicolae Grigorescu', 'clasic')
    assert a_service.read_by_id('2').name == 'Nicolae Grigorescu'
