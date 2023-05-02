from datetime import date

import jsonpickle

from Domain.card_client_validator import CardClientValidate
from Repository.file_repository import FileRepository
from Service.cardclient_service import CardClientService
from Service.undo_redo_service import UndoRedoService


def test_card_service():
    with open('test_cards.txt', 'w') as f:
        f.write(jsonpickle.encode({}))
    with open('test_card_ids.txt', 'w') as f:
        f.write(jsonpickle.encode({}))

    card_repo = FileRepository('test_cards.txt')
    card_val = CardClientValidate('test_card_ids.txt')
    undo_redo = UndoRedoService()
    serviciul_lui_peste_prajit = CardClientService(card_repo, card_val, undo_redo)
    serviciul_lui_peste_prajit.create(1, 'peste', 'prajit', '1451010999999', date(1800, 1, 1), 5000000)
    serviciul_lui_peste_prajit.update(1, '', '', '', '', 500000000000)
    serviciul_lui_peste_prajit.delete(1)
    assert serviciul_lui_peste_prajit.read() == []
    serviciul_lui_peste_prajit.create(1, 'peste', 'prajit', '1451010999999', date(1800, 1, 1), 5000000000)
    assert len(serviciul_lui_peste_prajit.full_search('peste')) == 1
    assert len(serviciul_lui_peste_prajit.sort_by_points_desc()) == 1
    serviciul_lui_peste_prajit.apply_birthday_bonus(date(1945, 10, 10), 95)
    assert serviciul_lui_peste_prajit.read_by_id(5000) is None
    serviciul_lui_peste_prajit.read_by_id(1).points == 10000000095
