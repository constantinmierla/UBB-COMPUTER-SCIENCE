from domain.expense import verify_expense,get_type,get_date,get_apartment,get_amount,create_expense,modify_expense
import datetime

def generate_expenses():
    """
    Functia genereaza cheltuieli
    """
    return  [[9,"gaz",125,datetime.date(2020,1,5)],[12,"gaz",100,datetime.date(2019,1,5)],
    [12,"apa",200,datetime.date(2018,1,5)],[11,"apa",150,datetime.date(2020,10,5)],
    [11,"canalizare",50,datetime.date(2004,2,10)],
    [11,"gaz",400,datetime.date(2021,10,10)],[13,"apa",500,datetime.date(2019,5,10)]]

def add_expense(e_list, expense):
    """
    Functia adauga in lista cheltuiala
    """
    verify_expense(e_list,expense)
    e_list.append(expense)

def delete_expenses_by_ap(e_list, ap_nr):
    """
    Functia elimina cheltuielile din lista 
    """
    ok = True
    while ok:
        ok = False
        for el in e_list:
            if get_apartment(el) == ap_nr:
                e_list.remove(el)
                ok = True

def delete_expenses_by_aps(e_list, nr1, nr2):
    """
    Functia elimina din lista toate cheltuilile de la apartamentele care se incadreaza
    in intervalul nr1 si nr2
    """

    ok = True
    while ok:
        ok = False
        for el in e_list:
            if get_apartment(el) >=nr1 and get_apartment(el)<=nr2:
                e_list.remove(el)
                ok = True

def delete_expenses_by_type(e_list, ap_type):
    """
    Functia elimina din lista toate cheltuielile de un anumit tip   
    """
    ok = True
    while ok:
        ok = False
        for el in e_list:
            if get_type(el) == ap_type:
                e_list.remove(el)
                ok = True

def all_expenses_by_type(e_list, ap_type):
    """
    Functia returneaza toate cheltuielile care au un anumit tip
    """
    new_list = []
    for el in e_list:
        if get_type(el) == ap_type:
            new_list.append(el)

    return new_list

def aps_w_expenses(e_list):
    """
    Functia returneaza apartamentele care au cheltuieli
    """
    new_list = []
    for el in e_list:
        add = True
        for i in new_list:
            if get_apartment(el) == i:
                add = False
                break
        if add == True:
            new_list.append(get_apartment(el))

    return new_list

def aps_by_summ(e_list, aps_w_expenses_list, summ):
    """
    Functia returneaza apartamentele care au cheltuieli mai mari decat o suma data
    """
    new_list = []
    for el in aps_w_expenses_list:
        if total_expense_for_ap(e_list,el) > summ:
            new_list.append(el)

    return new_list

def total_expense_for_ap(e_list, nr_ap):
    """
    Functia returnea totalul de cheltuieli pentru un apartament dat
    """
    summ = 0
    for el in e_list:
        if get_apartment(el) == nr_ap:
            summ += get_amount(el)

    return summ

def total_expense_for_type(e_list, ap_type):
    """
    Functia returneaza suma totala pentru un anumit tip de cheltuiala
    """
    summ = 0
    for el in e_list:
        if get_type(el) == ap_type:
            summ += get_amount(el)
    
    return summ

def aps_sorted_by_type(e_list, ap_type):
    """
    Functia returneaza apartamentele care au cheltuieli de un anumit tip
    """ 
    new_list = []
    for el in e_list:
        if get_type(el) == ap_type:
            new_list.append(get_apartment(el))

    return new_list

def eliminate_expenses_by_type(e_list, ap_type):
    """
    Functia returneaza o lista fara cheltuielile de un anumit tip
    """
    new_list = []
    for el in e_list:
        if get_type(el) != ap_type:
            new_list.append(el)
    
    return new_list

def eliminate_expenses_by_summ(e_list, summ):
    """
    Functia returneaza o lista cu cheltuielile care sunt mai mici decat o suma
    """
    new_list = []
    for el in e_list:
        if get_amount(el) <= summ:
            new_list.append(el)
    
    return new_list


#-------------Teste-----------
def test_add_expense():
    test_list = []
    e1 = create_expense(12,"gaz",100,datetime.date(2020,1,1))
    e2 = create_expense(12,"apa",200,datetime.date(2019,1,1))
    e3 = create_expense(9,"gaz",50,datetime.date(2018,1,1))

    add_expense(test_list,e1)
    assert(len(test_list)==1)
    assert(get_apartment(test_list[0]) == 12)
    assert(get_type(test_list[0]) == "gaz")
    assert(get_amount(test_list[0]) == 100)
    assert(get_date(test_list[0]) == datetime.date(2020,1,1))

    add_expense(test_list,e2)
    assert(len(test_list)==2)
    assert(get_apartment(test_list[0]) == 12)
    assert(get_type(test_list[0]) == "gaz")
    assert(get_amount(test_list[0]) == 100)
    assert(get_date(test_list[0]) == datetime.date(2020,1,1))
    assert(get_apartment(test_list[1]) == 12)
    assert(get_type(test_list[1]) == "apa")
    assert(get_amount(test_list[1]) == 200)
    assert(get_date(test_list[1]) == datetime.date(2019,1,1))

    add_expense(test_list,e3)
    assert(len(test_list)==3)
    assert(get_apartment(test_list[0]) == 12)
    assert(get_type(test_list[0]) == "gaz")
    assert(get_amount(test_list[0]) == 100)
    assert(get_apartment(test_list[2]) == 9)
    assert(get_type(test_list[2]) == "gaz")
    assert(get_amount(test_list[2]) == 50)
    assert(get_date(test_list[2]) == datetime.date(2018,1,1))

def test_delete_expenses_by_ap():
    test_list = []
    e1 = create_expense(12,"gaz",100,datetime.date(2020,1,1))
    e2 = create_expense(12,"apa",200,datetime.date(2019,1,1))
    e3 = create_expense(9,"gaz",50,datetime.date(2018,1,1))

    add_expense(test_list,e1)
    add_expense(test_list,e2)
    add_expense(test_list,e3)

    delete_expenses_by_ap(test_list,12)

    assert(len(test_list) == 1)
    assert(get_amount(test_list[0]) == 50)

def test_delete_expenses_by_aps():
    test_list = generate_expenses()

    delete_expenses_by_aps(test_list,11,12)

    assert(len(test_list) == 2)
    assert(get_amount(test_list[0]) == 125)
    assert(get_apartment(test_list[0])  == 9)
    assert(get_apartment(test_list[1]) == 13)

def test_delete_expenses_by_type():
    test_list=generate_expenses()

    ap_type = "gaz"

    delete_expenses_by_type(test_list, ap_type)

    assert(len(test_list) == 4)
    assert(get_type(test_list[0]) == "apa")
    assert(get_type(test_list[2]) == "canalizare")
    assert(get_amount(test_list[1]) == 150)

def test_all_expenses_by_type():
    test_list = generate_expenses()
    test_list2 = all_expenses_by_type(test_list,"gaz")
    assert(len(test_list2) == 3)
    
def test_aps_w_espenses():
    test_list = generate_expenses()
    test_list2 = aps_w_expenses(test_list)
    assert(test_list2 == [9,12,11,13])

def test_aps_by_summ():
    test_list = generate_expenses()
    test_list2 = aps_w_expenses(test_list)
    the_list = aps_by_summ(test_list, test_list2, 200)
    assert(the_list == [12,11,13])

def test_total_expense_for_ap():
    test_list = generate_expenses()
    e9 = total_expense_for_ap(test_list, 9)
    e8 = total_expense_for_ap(test_list, 8)
    e11 = total_expense_for_ap(test_list, 11)
    assert(e9 == 125)
    assert(e8 == 0)
    assert(e11 == 600)

def test_total_expense_for_type():
    test_list = generate_expenses()
    e_water = total_expense_for_type(test_list, "apa")
    e_gas = total_expense_for_type(test_list, "gaz")
    assert(e_water == 850)
    assert(e_gas == 625)

def test_aps_sorted_by_type():
    test_list = generate_expenses()
    aps_w_water = aps_sorted_by_type(test_list, "apa")
    aps_w_gas = aps_sorted_by_type(test_list, "gaz")
    assert(aps_w_water == [9,12,11])
    assert(aps_w_gas == [12,11,13])

def test_eliminate_expenses_by_type():
    test_list = generate_expenses()
    eliminate_water = eliminate_expenses_by_type(test_list, "apa")
    assert (len(eliminate_water) == 4)

def test_eliminate_expenses_by_summ():
    test_list = generate_expenses()
    new_list = eliminate_expenses_by_summ(test_list, 200)
    assert(len(new_list) == 5)

test_delete_expenses_by_type()
test_delete_expenses_by_aps()
test_delete_expenses_by_ap()
test_add_expense()
test_all_expenses_by_type()
test_aps_w_espenses()
test_aps_by_summ()
test_total_expense_for_type()
test_total_expense_for_ap()
test_eliminate_expenses_by_summ()
test_eliminate_expenses_by_type()