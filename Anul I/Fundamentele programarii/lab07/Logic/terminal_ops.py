from Domain.bcolors import Colors
from Logic.crud import add_thing, update_thing, delete_thing, show_all, override_list
from Logic.operations import change_location, concat_to_description_by_price, print_priciest, sort_inventory_by_price, \
    print_sums_at_locations, remove_from_description_by_price


def terminal_help(args):
    '''
    Afiseaza in terminal documentatia comenzilor permise
    :param args: placeholder - necesar pentru interpretarea automata a comenzilor
    :return: None
    '''

    print(f'{Colors.BOLD}#######{Colors.END}')
    print(f'{Colors.BOLD}LISTA COMENZI{Colors.END}')
    print(f'Tipuri: id-{Colors.PURPLE}int{Colors.END}, name-{Colors.PURPLE}string{Colors.END}, description-{Colors.PURPLE}string{Colors.END}, price-{Colors.PURPLE}float{Colors.END}, location-{Colors.PURPLE}string{Colors.GREEN}')
    print(f'\nadauga,id,name,description,price,location  {Colors.LIGHT_WHITE}# adauga obiectul cu atributele specificate la inventar{Colors.GREEN}')
    print(f'\nmodifica,id,name,description,price,location  {Colors.LIGHT_WHITE}# modifica atributele obiectului cu id-ul dat{Colors.GREEN}')
    print(f'\nsterge,id  {Colors.LIGHT_WHITE}# sterge obiectul cu id-ul dat{Colors.GREEN}')
    print(f'\nafiseaza  {Colors.LIGHT_WHITE}# afiseaza tot inventarul{Colors.GREEN}')
    print(f'\nstop  {Colors.LIGHT_WHITE}# opreste terminalul de comenzi{Colors.GREEN}')
    print(f'\n{Colors.END}')


def get_command_list():
    '''
    Preia un sir de comenzi introdus in terminal si il transforma in lista de comenzi cu parametrii lor
    :return: lista de comenzi
    '''

    input_string = input(f'>:')
    command_list = input_string.split(';')
    result = []
    for position in range(len(command_list)):
        args_list = command_list[position].split(',')
        result.append(args_list)
    return result


def handle_command(thing_list, command_as_string_list):
    '''
    Preia o comanda valida data ca lista si o executa
    :param thing_list: inventarul dat
    :param command_as_string_list: comanda: o lista formata din handle-ul comenzii urmat de parametrii acesteia
    :return: inventarul modificat
    '''

    command_mapper = {
        'adauga': add_thing,
        'modifica': update_thing,
        'sterge': delete_thing,
        'afiseaza': show_all,
        'mutare': change_location,
        'concat': concat_to_description_by_price,
        'maxpret': print_priciest,
        'ordonare': sort_inventory_by_price,
        'sumpret': print_sums_at_locations,
        'taie': remove_from_description_by_price,
        'suprascrie': override_list,
        'help': terminal_help
    }

    thing_list = command_mapper[command_as_string_list[0]](thing_list, *command_as_string_list[1:])

    return thing_list
