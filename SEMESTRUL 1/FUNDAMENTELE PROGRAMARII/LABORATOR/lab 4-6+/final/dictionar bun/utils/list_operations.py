def copy_list(list_a):
    """
    Functia returneaza o copie a listei a
    """
    new_list = []
    for el in list_a:
        new_list.append(el)

    return new_list

def copy_dict(dict_a):
    """
    Functia returneaza o copie a dictionarului a
    """
    new_dict = {}
    for key, value in dict_a.items():
        new_dict[key] = value

    return new_dict

def add_in_undo_list(e_dict, undo_list):
    """
    Functia adauga in undo_list o copie a dictionarului expenses
    """
    new_dict = copy_list(e_dict)
    undo_list.append(new_dict)

def update_undo(expenses_dict, undo_list):
    """
    Functia modifica lista de undo, adaugand o copie a dictionarului expenses
    """
    len_undo = len(undo_list)
    if expenses_dict != undo_list[len_undo-1]:
        add_in_undo_list(expenses_dict, undo_list)

def remove_from_undo_list(undo_list, l):
    """
    Functia sterge ultimul element din lista de undo
    """
    undo_list.pop()


def test_add_in_undo_list():
    t1_dict = {'expenses': [1, 2], 'other_data': 'data'}
    t2_dict = {'expenses': [3], 'other_data': 'data'}
    add_in_undo_list(t2_dict, t1_dict['expenses'])

def test_update_undo():
    t1_dict = {'expenses': [1, 2], 'other_data': 'data'}
    t2_dict = {'expenses': [3], 'other_data': 'data'}
    update_undo(t2_dict, t1_dict['expenses'])

def test_remove_from_undo_list():
    test_list = [{'expenses': [1, 2], 'other_data': 'data'}, {'expenses': [2, 3], 'other_data': 'data'}, {'expenses': [3, 4], 'other_data': 'data'}]
    remove_from_undo_list(test_list, 3)
    assert test_list == [{'expenses': [1, 2], 'other_data': 'data'}, {'expenses': [2, 3], 'other_data': 'data'}]

test_add_in_undo_list()
test_update_undo()
test_remove_from_undo_list()
