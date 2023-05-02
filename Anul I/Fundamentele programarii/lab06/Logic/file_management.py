import json


def write_file(thing_list, filename='thing_list.txt'):
    with open(filename, 'w') as f:
        json.dump(thing_list, f)


def load_file(filename='thing_list.txt'):
    with open(filename, 'r') as f:
        return json.load(f)
