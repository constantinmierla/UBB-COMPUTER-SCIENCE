import datetime
class ExpenseError(Exception):
    pass

def get_apartment(expense):
    """
    Functia returneaza numarului apartamentului a unei cheltuieli specificie
    """
    return expense[0]

def get_type(expense):
    """
    Functia returneaza tipul cheltuielii
    """
    return expense[1]

def get_amount(expense):
    """
    Functia returneaza suma cheltuielii
    """
    return expense[2]

def get_date(expense):
    """
    Functia returneaza data cheltuielii
    """
    return expense[3]

def verify_expense(e_list,expense):
    """
    Functia verifica daca exista cheltuiala in lista
    """
    for el in e_list:
        if get_type(expense) == get_type(el) and get_apartment(expense) == get_apartment(el):
            raise ExpenseError

def create_expense(ap_nr, e_type, amount, e_date):
    """
    Functia returneaza cheltuiala sub forma de dictionar(o creeaza)
    """
    return [ap_nr, e_type, amount, e_date]

def modify_expense(e_list, expense):
    """
    Functia schimba in lista suma unei cheltuieli
    """
    for el in e_list:
        if get_type(expense) == get_type(el) and get_apartment(expense) == get_apartment(el):
            el[2] = get_amount(expense)
            return
    raise ExpenseError

[[9,"gaz",125,datetime.date(2020,1,5)],[12,"gaz",100,datetime.date(2019,1,5)],
    [12,"apa",200,datetime.date(2018,1,5)],[11,"apa",150,datetime.date(2020,10,5)],
    [11,"canalizare",50,datetime.date(2004,2,10)],
    [11,"gaz",400,datetime.date(2021,10,10)],[13,"apa",500,datetime.date(2019,5,10)]]

def test_verify_expense():
    test_list = [[9,"gaz",125,datetime.date(2020,1,5)],[12,"gaz",100,datetime.date(2019,1,5)]]
    expense = [9,"gaz",125,datetime.date(2020,1,5)]
    try:
        verify_expense(test_list, expense)
        assert False
    except:
        assert True

    expense = [100,"gaz",125,datetime.date(2020,1,5)]
    try:
        verify_expense(test_list, expense)
        assert True
    except:
        assert False

def test_create_expense():
    expense = create_expense(9,"gaz",125,datetime.date(2020,1,5))
    assert(expense == [9,"gaz",125,datetime.date(2020,1,5)])

def test_modify_expense():
    test_list = [[9,"gaz",125,datetime.date(2020,1,5)],[12,"gaz",100,datetime.date(2019,1,5)]]
    expense = [9,"gaz",250,datetime.date(2020,1,5)]
    modify_expense(test_list, expense)
    assert(test_list == [[9,"gaz",250,datetime.date(2020,1,5)],[12,"gaz",100,datetime.date(2019,1,5)]])
    try:
        expense = [10,"gaz",300,datetime.date(2020,1,5)]
        modify_expense(test_list, expense)
        assert False
    except:
        assert True

test_verify_expense()
test_create_expense()
test_modify_expense()