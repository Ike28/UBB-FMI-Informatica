def create_thing(input_object_id, input_name, input_description, input_price, input_location):
    '''
    Creeaza un obiect cu atributele date object_id, name, description, price, location SUB FORMA DE LISTA
    :param input_object_id: id-ul obiectului
    :param input_name: numele obiectului
    :param input_description: descrierea obiectului
    :param input_price: pretul de achizitie al obiectului
    :param input_location: locatia de depozitare a obiectului
    :return: obiectul format, dictionar
    '''
    
    return [
        input_object_id,
        input_name,
        input_description,
        input_price,
        input_location
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


def set_name(thing, new_name):
    '''
    Actualizeaza atributul nume
    :param thing: obiectul dat, lista
    :param new_name: numele nou, string
    :return: obiectul actualizat, lista
    '''

    thing[1] = new_name
    return thing


def get_description(thing):
    '''
    Extrage descrierea dintr-un obiect
    :param thing: obiectul dat, lista
    :return: descrierea obiectului, string
    '''

    return thing[2]


def set_description(thing, new_description):
    '''
    Actualizeaza atributul descriere
    :param thing: obiectul dat, lista
    :param new_description: noua descriere, string
    :return: obiectul actualizat, lista
    '''

    thing[2] = new_description
    return thing


def get_price(thing):
    '''
    Extrage pretul dintr-un obiect
    :param thing: obiectul dat, lista
    :return: pretul obiectului, float
    '''

    return thing[3]


def set_price(thing, new_price):
    '''
    Actualizeaza atributul pret
    :param thing: obiectul dat, lista
    :param new_price: noul pret, float
    :return: obiectul actualizat, lista
    '''

    thing[3] = new_price
    return thing


def get_location(thing):
    '''
    Extrage locatia de depozitare dintr-un obiect
    :param thing: obiectul dat, lista
    :return: locatia obiectului, string cu len(string) == 4
    '''

    return thing[4]


def set_location(thing, new_location):
    '''
    Actualizeaza atributul locatie
    :param thing: obiectul dat, lista
    :param new_location: noua locatie, string cu len(string) == 4
    :return: obiectul actualizat, lista
    '''

    thing[4] = new_location
    return thing


def to_string(thing):
    '''
    Transpune un obiect intr-un string echivalent ce poate fi afisat
    :param thing: obiectul dat, lista
    :return: string-ul ce prezinta obiectul
    '''

    return f'ID={get_id(thing)} : Obiectul {get_name(thing)}: {get_description(thing)[:30]}, ' \
           f'cu pretul de achizitie = {get_price(thing)}; depozitat in sala {get_location(thing)}'
