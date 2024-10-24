from domain.expense import verify_expense, get_type, get_date, get_apartment, get_amount, create_expense, modify_expense
import datetime

def generate_expenses():
    """
    Generează un dicționar cu cheltuieli pentru teste.
    """
    return {
        (9, "gaz"): {'ap_nr': 9, 'e_type': 'gaz', 'amount': 125, 'e_date': datetime.date(2020, 1, 5)},
        (12, "gaz"): {'ap_nr': 12, 'e_type': 'gaz', 'amount': 100, 'e_date': datetime.date(2019, 1, 5)},
        (12, "apa"): {'ap_nr': 12, 'e_type': 'apa', 'amount': 200, 'e_date': datetime.date(2018, 1, 5)},
        (11, "apa"): {'ap_nr': 11, 'e_type': 'apa', 'amount': 150, 'e_date': datetime.date(2020, 10, 5)},
        (11, "canalizare"): {'ap_nr': 11, 'e_type': 'canalizare', 'amount': 50, 'e_date': datetime.date(2004, 2, 10)},
        (11, "gaz"): {'ap_nr': 11, 'e_type': 'gaz', 'amount': 400, 'e_date': datetime.date(2021, 10, 10)},
        (13, "apa"): {'ap_nr': 13, 'e_type': 'apa', 'amount': 500, 'e_date': datetime.date(2019, 5, 10)},
    }

def add_expense(e_dict, expense):
    """
    Adaugă o cheltuială în dicționarul de cheltuieli.
    """
    verify_expense(e_dict, expense)
    key = (get_apartment(expense), get_type(expense))
    e_dict[key] = expense

def delete_expenses_by_ap(e_dict, ap_nr):
    """
    Șterge toate cheltuielile pentru un anumit apartament.
    """
    keys_to_remove = [key for key in e_dict.keys() if key[0] == ap_nr]
    for key in keys_to_remove:
        del e_dict[key]

def delete_expenses_by_aps(e_dict, nr1, nr2):
    """
    Șterge cheltuielile pentru apartamentele cuprinse între nr1 și nr2 (inclusiv).
    """
    keys_to_remove = [key for key in e_dict.keys() if nr1 <= key[0] <= nr2]
    for key in keys_to_remove:
        del e_dict[key]

def delete_expenses_by_type(e_dict, ap_type):
    """
    Șterge cheltuielile de un anumit tip pentru toate apartamentele.
    """
    keys_to_remove = [key for key in e_dict.keys() if get_type(e_dict[key]) == ap_type]
    for key in keys_to_remove:
        del e_dict[key]

def all_expenses_by_type(e_dict, ap_type):
    """
    Returnează o listă cu toate cheltuielile de un anumit tip.
    """
    return [expense for expense in e_dict.values() if get_type(expense) == ap_type]

def aps_w_expenses(e_dict):
    """
    Returnează o listă cu apartamentele pentru care există cheltuieli.
    """
    return list(set(get_apartment(expense) for expense in e_dict.values()))

def aps_by_summ(e_dict, aps_w_expenses_list, summ):
    """
    Returnează o listă cu apartamentele care au cheltuieli mai mari decât suma dată.
    """
    return [apartment for apartment in aps_w_expenses_list if total_expense_for_ap(e_dict, apartment) > summ]

def total_expense_for_ap(e_dict, nr_ap):
    """
    Calculează suma totală a cheltuielilor pentru un anumit apartament.
    """
    return sum(expense['amount'] for expense in e_dict.values() if get_apartment(expense) == nr_ap)

def total_expense_for_type(e_dict, ap_type):
    """
    Calculează suma totală a cheltuielilor pentru un anumit tip.
    """
    return sum(expense['amount'] for expense in e_dict.values() if get_type(expense) == ap_type)

def aps_sorted_by_type(e_dict, ap_type):
    """
    Returnează o listă cu apartamentele sortate după un anumit tip de cheltuială.
    """
    return sorted(set(get_apartment(expense) for expense in e_dict.values() if get_type(expense) == ap_type))

def eliminate_expenses_by_type(e_dict, ap_type):
    """
    Elimină cheltuielile de un anumit tip din dicționar.
    """
    return {key: expense for key, expense in e_dict.items() if get_type(expense) != ap_type}

def eliminate_expenses_by_summ(e_dict, summ):
    """
    Elimină cheltuielile mai mici decât suma dată din dicționar.
    """
    return {key: expense for key, expense in e_dict.items() if get_amount(expense) > summ}
def test_add_expense():
    test_dict = {}
    e1 = create_expense(12, "gaz", 100, datetime.date(2020, 1, 1))
    e2 = create_expense(12, "apa", 200, datetime.date(2019, 1, 1))
    e3 = create_expense(9, "gaz", 50, datetime.date(2018, 1, 1))

    add_expense(test_dict, e1)
    assert len(test_dict) == 1
    assert get_apartment(test_dict[(12, "gaz")]) == 12
    assert get_type(test_dict[(12, "gaz")]) == "gaz"
    assert get_amount(test_dict[(12, "gaz")]) == 100
    assert get_date(test_dict[(12, "gaz")]) == datetime.date(2020, 1, 1)

    add_expense(test_dict, e2)
    assert len(test_dict) == 2
    assert get_apartment(test_dict[(12, "gaz")]) == 12
    assert get_type(test_dict[(12, "gaz")]) == "gaz"
    assert get_amount(test_dict[(12, "gaz")]) == 100
    assert get_date(test_dict[(12, "gaz")]) == datetime.date(2020, 1, 1)
    assert get_apartment(test_dict[(12, "apa")]) == 12
    assert get_type(test_dict[(12, "apa")]) == "apa"
    assert get_amount(test_dict[(12, "apa")]) == 200
    assert get_date(test_dict[(12, "apa")]) == datetime.date(2019, 1, 1)

    add_expense(test_dict, e3)
    assert len(test_dict) == 3
    assert get_apartment(test_dict[(12, "gaz")]) == 12
    assert get_type(test_dict[(12, "gaz")]) == "gaz"
    assert get_amount(test_dict[(12, "gaz")]) == 100
    assert get_apartment(test_dict[(9, "gaz")]) == 9
    assert get_type(test_dict[(9, "gaz")]) == "gaz"
    assert get_amount(test_dict[(9, "gaz")]) == 50
    assert get_date(test_dict[(9, "gaz")]) == datetime.date(2018, 1, 1)

def test_delete_expenses_by_ap():
    test_dict = {}
    e1 = create_expense(12, "gaz", 100, datetime.date(2020, 1, 1))
    e2 = create_expense(12, "apa", 200, datetime.date(2019, 1, 1))
    e3 = create_expense(9, "gaz", 50, datetime.date(2018, 1, 1))

    add_expense(test_dict, e1)
    add_expense(test_dict, e2)
    add_expense(test_dict, e3)

    delete_expenses_by_ap(test_dict, 12)

    assert len(test_dict) == 1
    assert get_amount(test_dict[(9, "gaz")]) == 50

def test_delete_expenses_by_aps():
    test_dict = generate_expenses()

    delete_expenses_by_aps(test_dict, 11, 12)

    assert len(test_dict) == 2
    assert get_amount(test_dict[(9, "gaz")]) == 125
    assert get_apartment(test_dict[(9, "gaz")]) == 9
    assert get_apartment(test_dict[(13, "apa")]) == 13

def test_delete_expenses_by_type():
    test_dict = generate_expenses()

    ap_type = "gaz"

    delete_expenses_by_type(test_dict, ap_type)

    assert len(test_dict) == 4
    assert get_type(test_dict[(12, "apa")]) == "apa"
    assert get_type(test_dict[(11, "canalizare")]) == "canalizare"
    assert get_amount(test_dict[(11, "apa")]) == 150

def test_all_expenses_by_type():
    test_dict = generate_expenses()
    test_list = all_expenses_by_type(test_dict, "gaz")
    assert len(test_list) == 3

def test_aps_w_espenses():
    test_dict = generate_expenses()
    test_list = aps_w_expenses(test_dict)
def test_aps_by_summ():
    test_dict = generate_expenses()
    test_list = aps_w_expenses(test_dict)
    the_list = aps_by_summ(test_dict, test_list, 200)
    assert the_list == [12, 11, 13]

def test_total_expense_for_ap():
    test_dict = generate_expenses()
    e9 = total_expense_for_ap(test_dict, 9)
    e8 = total_expense_for_ap(test_dict, 8)
    e11 = total_expense_for_ap(test_dict, 11)
    assert e9 == 125
    assert e8 == 0
    assert e11 == 600

def test_total_expense_for_type():
    test_dict = generate_expenses()
    e_water = total_expense_for_type(test_dict, "apa")
    e_gas = total_expense_for_type(test_dict, "gaz")
    assert e_water == 850
    assert e_gas == 625


test_delete_expenses_by_type()
test_delete_expenses_by_aps()
test_delete_expenses_by_ap()
test_add_expense()
test_all_expenses_by_type()
test_total_expense_for_type()
test_total_expense_for_ap()
