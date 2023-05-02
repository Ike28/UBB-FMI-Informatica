def create_thing(object_id, name, description, price, location):
    '''
    Creeaza un obiect cu atributele date object_id, name, description, price, location SUB FORMA DE LISTA
    :param object_id: id-ul obiectului
    :param name: numele obiectului
    :param description: descrierea obiectului
    :param price: pretul de achizitie al obiectului
    :param location: locatia de depozitare a obiectului
    :return: obiectul format, lista
    '''
    
    return [
        object_id,
        name,
        description,
        price,
        location
    ]


def get_id(thing):
    '''
    Extrage id-ul dintr-un obiect
    :param thing: obiectul dat, dictionar
    :return: id-ul obiectului, int
    '''

    return thing[0]


def get_name(thing):
    '''
    Extrage numele dintr-un obiect
    :param thing: obiectul dat, lista
    :return: numele obiectului, string
    '''

    return thing[1]


def get_description(thing):
    '''
    Extrage descrierea dintr-un obiect
    :param thing: obiectul dat, lista
    :return: descrierea obiectului, string
    '''

    return thing[2]


def get_price(thing):
    '''
    Extrage pretul dintr-un obiect
    :param thing: obiectul dat, lista
    :return: pretul obiectului, float
    '''

    return thing[3]


def get_location(thing):
    '''
    Extrage locatia de depozitare dintr-un obiect
    :param thing: obiectul dat, lista
    :return: locatia obiectului, string cu len(string) == 4
    '''

    return thing[4]


def to_string(thing):
    '''
    Transpune un obiect intr-un string echivalent ce poate fi afisat
    :param thing: obiectul dat, lista
    :return: string-ul ce prezinta obiectul
    '''

    return f'Obiectul de id={get_id(thing)}, {get_name(thing)}: {get_description(thing)[:30]}, ' \
           f'cu pretul de achizitie={get_price(thing)}, depozitat in {get_location(thing)}'
