import jsonpickle
from os import path, remove

from Domain.artist import Artist
from Domain.painting import Painting
from Domain.painting_validator import PaintingValidator
from Repository.file_repository import FileRepository
from Service.painting_service import PaintingService


def test_painting_service():
    with open('test_file2.txt', 'w') as f:
        f.write(jsonpickle.encode({}))
    with open('test_file3.txt', 'w') as f:
        f.write(jsonpickle.encode({}))
    p_repo = FileRepository('test_file2.txt')
    a_repo = FileRepository('test_file3.txt')
    p_val = PaintingValidator()
    p_service = PaintingService(p_repo, p_val, a_repo)
    a_repo.create(Artist('1', 'Vasile Garbasevschi', 'clasic'))

    # TEST FUNCTIONALITATEA 2
    p_service.create('1', '1', 'Il Rinoceronte', '200000', '2020')
    assert p_service.read_by_id('1') == Painting('1', '1', 'Il Rinoceronte', 200000, 2020)
    try:
        p_service.create('2', '1', 'E finito il bei tempo che fu', '2000', 'in viitor')
    except:
        p_service.create('2', '1', 'Ciorba de perisoare la mine acasa', '2000', '2019')
    assert p_service.read_by_id('2').title == 'Ciorba de perisoare la mine acasa'

    # TEST FUNCTIONALITATEA 3
    assert p_service.expensive_paintings() == {'clasic': Painting('1', '1', 'Il Rinoceronte', 200000, 2020)}

    # TEST FUNCTIONALITATEA 4
    assert p_service.get_artists_by_number_of_paintings(1) == {'1': 2}

    # TEST FUNCTIONALITATEA 5
    p_service.dump_to_json('test_dump')

    assert path.exists('test_dump.json') is True
