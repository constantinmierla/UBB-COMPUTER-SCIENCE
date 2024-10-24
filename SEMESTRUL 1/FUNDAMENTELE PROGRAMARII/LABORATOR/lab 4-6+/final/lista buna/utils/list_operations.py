
def copy_list(list_a):
    """
    Functia returneaza o copie a listei a
    """
    new_list = []
    for el in list_a:
        new_list.append(el)

    return new_list

def add_in_undo_list(e_list, undo_list):
    """
    Functia adauga in undo_list o lista noua
    """
    new_list = copy_list(e_list)
    undo_list.append(new_list)

def update_undo(expenses_list, undo_list):
    """
    Functia modifica lista de undo, adaugand o lista nou
    """
    len_undo = len(undo_list)
    if expenses_list != undo_list[len_undo-1]:
        add_in_undo_list(expenses_list, undo_list)

def remove_from_undo_list(undo_list, l):
    """
    Functia sterge ultima lista din lista de undo
    """
    undo_list.remove(undo_list[l-1])

def test_copy_list():
    test_list = [1,2,3]
    new_list = copy_list(test_list)
    assert(new_list == [1,2,3])

def test_add_in_undo_list():
    t1_list = [1,2]
    t2_list = [3]
    add_in_undo_list(t2_list, t1_list)
    assert(t1_list == [1,2,[3]])

def test_update_undo():
    t1_list = [1,2]
    t2_list = [3]
    update_undo(t2_list, t1_list)
    assert(t1_list == [1,2,[3]])

def test_remove_from_undo_list():
    test_list = [[1,2],[2,3],[3,4]]
    remove_from_undo_list(test_list, 3)
    assert(test_list == [[1,2],[2,3]])

test_copy_list()
test_add_in_undo_list()
test_update_undo()
test_remove_from_undo_list()