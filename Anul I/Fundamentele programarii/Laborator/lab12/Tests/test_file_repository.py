import jsonpickle

from Repository.file_repository import FileRepository
from Domain.entity import Entity


def test_file_repository():
    with open('test_file1.txt', 'w') as f:
        f.write(jsonpickle.encode({}))
    ent_repo = FileRepository('test_file1.txt')
    ent = Entity('1')
    ent_repo.create(ent)
    assert ent_repo.get_by_id('1') == ent
    ent2 = Entity('1')
    ent_repo.update(ent2)
    assert ent_repo.get_by_id('1') == ent2
    ent_repo.delete('1')
    assert ent_repo.read() == []
    assert ent_repo.get_by_id('3') is None
