from Domain.bcolors import Colors
from Logic.terminal_ops import get_command_list, handle_command
from Logic.validations import validate_terminal_command


def handle_multiple_commands(thing_list1):
    '''
    Transforma un sir de comenzi din terminal in comenzi valide si le executa
    :param thing_list1: inventarul dat
    :return: inventarul modificat
    '''

    # def add_validate(command):
    #     erori = ''
    #     if command[0] != 'adauga':
    #         erori += f'\nINTERNAL ERROR: A fost apelata validarea gresita (adaugare in loc de {command[0]})'
    #     if len(command) < 6:
    #         erori += '\nSintaxa comenzii adauga este gresita: nu au fost date toate atributele obiectului'
    #     if len(erori) > 0:
    #         raise TypeError(erori)
    #     command[1] = int(command[1])
    #     command[4] = float(command[1])
    #
    #     return command

    command_counter = {
        'adauga': 0,
        'modifica': 0,
        'sterge': 0,
        'afiseaza': 0,
        'help': 0,
        'stop':0
    }

    while True:
        try:
            erori = ''
            command_counter['adauga'], command_counter['modifica'], command_counter['sterge'], command_counter['afiseaza'], command_counter['help'] = 0, 0, 0, 0, 0
            command_list = get_command_list()
            if command_list == [['']]:
                raise TypeError('Nicio comanda nu a fost introdusa!')
            command_names = []

            for each_command in command_list:
                try:
                    if each_command[0] != 'stop':
                        each_command = validate_terminal_command(each_command, thing_list1)
                        thing_list1 = handle_command(thing_list1, each_command)
                    command_counter[each_command[0]] += 1
                    command_names.append(each_command[0])
                except TypeError as te:
                    erori += str(te) + f' {each_command[0]}'

            if len(command_names):
                print(f'{Colors.DARK_GRAY}#efectuat:', end='')
            if command_counter['help']:
                print(f'{Colors.GREEN} {command_counter["help"]} liste comenzi {Colors.END};', end='')
            if command_counter['adauga']:
                print(f'{Colors.GREEN} {command_counter["adauga"]} adaugari {Colors.END};', end='')
            if command_counter['modifica']:
                print(f'{Colors.GREEN} {command_counter["modifica"]} modificari {Colors.END};', end='')
            if command_counter['sterge']:
                print(f'{Colors.GREEN} {command_counter["sterge"]} stergeri {Colors.END};', end='')
            if command_counter['afiseaza']:
                print(f'{Colors.GREEN} {command_counter["afiseaza"]} afisari {Colors.END};', end='')
            if command_counter['stop']:
                print(f'{Colors.GREEN} oprire {Colors.END};', end='')
            print('')
            if len(erori):
                raise TypeError(erori)
            if 'stop' in command_names:
                break

        except TypeError as te:
            print(f'\n{Colors.BLACK}Eroare: \n{te}\n --> reincearca!{Colors.END}\n')
        except KeyError as ke:
            print(f'\n{Colors.BLACK}Eroare: \n{ke}\n --> reincearca!{Colors.END}\n')
        except Exception as ex:
            print(f'\n{Colors.BLACK}Eroare: \n{ex}\n --> reincearca!{Colors.END}\n')
    return thing_list1
