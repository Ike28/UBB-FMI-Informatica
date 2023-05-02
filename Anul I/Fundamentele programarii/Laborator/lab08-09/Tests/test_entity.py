import jsonpickle

from Domain.entity import Entity


def test_entity_constructor_validator():
    with open('test_validator_ids.txt', 'w') as f:
        f.write(jsonpickle.encode([]))
    ent = Entity('1')
    assert ent.id == '1'
