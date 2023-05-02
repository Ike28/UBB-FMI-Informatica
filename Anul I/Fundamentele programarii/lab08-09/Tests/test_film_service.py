import jsonpickle
from os import path

from Domain.film_validator import FilmValidate
from Repository.file_repository import FileRepository
from Service.film_service import FilmService
from Service.undo_redo_service import UndoRedoService


def test_film_service():
    with open('test_films.txt', 'w') as f:
        f.write(jsonpickle.encode({}))
    with open('test_film_ids.txt', 'w') as f:
        f.write(jsonpickle.encode([]))

    film_repo = FileRepository('test_films.txt')
    film_val = FilmValidate('test_film_ids.txt')
    undo_redo = UndoRedoService()
    ia_daici_ca_nai_servici = FilmService(film_repo, film_val, undo_redo)
    ia_daici_ca_nai_servici.create(1, 'Anemia lui Gray', 2005, 300, True)
    undo_redo.undo()
    assert ia_daici_ca_nai_servici.read() == []
    undo_redo.redo()
    ia_daici_ca_nai_servici.update(1, 'Anomalia lui Gray', '', '', '')
    ia_daici_ca_nai_servici.delete(1)
    assert ia_daici_ca_nai_servici.read() == []
    ia_daici_ca_nai_servici.create(1, 'Anemia lui Gray', 2005, 300, True)
    assert len(ia_daici_ca_nai_servici.full_search('ray')) == 1
    ia_daici_ca_nai_servici.generate_films(5)
    assert len(ia_daici_ca_nai_servici.read()) == 6
    assert ia_daici_ca_nai_servici.read_by_id(1) is not None
    ia_daici_ca_nai_servici.write_films_to_excel()
    assert path.exists('films.xlsx') is True
