import datetime

class ExpenseError(Exception):
    pass

def get_apartment(expense):
    return expense['ap_nr']

def get_type(expense):
    return expense['e_type']

def get_amount(expense):
    return expense['amount']

def get_date(expense):
    return expense['e_date']

def verify_expense(e_dict, expense):
    key = (get_apartment(expense), get_type(expense))
    if key in e_dict:
        raise ExpenseError

def create_expense(ap_nr, e_type, amount, e_date):
    return {'ap_nr': ap_nr, 'e_type': e_type, 'amount': amount, 'e_date': e_date}

def modify_expense(e_dict, expense):
    key = (get_apartment(expense), get_type(expense))
    if key in e_dict:
        e_dict[key]['amount'] = get_amount(expense)
    else:
        raise ExpenseError

expenses = {
    (9, "gaz"): {'ap_nr': 9, 'e_type': 'gaz', 'amount': 125, 'e_date': datetime.date(2020, 1, 5)},
    (12, "gaz"): {'ap_nr': 12, 'e_type': 'gaz', 'amount': 100, 'e_date': datetime.date(2019, 1, 5)},
}

def test_verify_expense():
    test_expenses = {
        (9, "gaz"): {'ap_nr': 9, 'e_type': 'gaz', 'amount': 125, 'e_date': datetime.date(2020, 1, 5)},
        (12, "gaz"): {'ap_nr': 12, 'e_type': 'gaz', 'amount': 100, 'e_date': datetime.date(2019, 1, 5)},
    }

    expense = {'ap_nr': 9, 'e_type': 'gaz', 'amount': 125, 'e_date': datetime.date(2020, 1, 5)}
    try:
        verify_expense(test_expenses, expense)
        assert False
    except ExpenseError:
        assert True

    expense = {'ap_nr': 100, 'e_type': 'gaz', 'amount': 125, 'e_date': datetime.date(2020, 1, 5)}
    try:
        verify_expense(test_expenses, expense)
        assert True
    except ExpenseError:
        assert False

def test_create_expense():
    expense = create_expense(9, 'gaz', 125, datetime.date(2020, 1, 5))
    assert(expense == {'ap_nr': 9, 'e_type': 'gaz', 'amount': 125, 'e_date': datetime.date(2020, 1, 5)})

def test_modify_expense():
    test_expenses = {
        (9, "gaz"): {'ap_nr': 9, 'e_type': 'gaz', 'amount': 125, 'e_date': datetime.date(2020, 1, 5)},
        (12, "gaz"): {'ap_nr': 12, 'e_type': 'gaz', 'amount': 100, 'e_date': datetime.date(2019, 1, 5)},
    }

    expense = {'ap_nr': 9, 'e_type': 'gaz', 'amount': 250, 'e_date': datetime.date(2020, 1, 5)}
    modify_expense(test_expenses, expense)
    assert(test_expenses == {
        (9, "gaz"): {'ap_nr': 9, 'e_type': 'gaz', 'amount': 250, 'e_date': datetime.date(2020, 1, 5)},
        (12, "gaz"): {'ap_nr': 12, 'e_type': 'gaz', 'amount': 100, 'e_date': datetime.date(2019, 1, 5)},
    })

    try:
        expense = {'ap_nr': 10, 'e_type': 'gaz', 'amount': 300, 'e_date': datetime.date(2020, 1, 5)}
        modify_expense(test_expenses, expense)
        assert False
    except ExpenseError:
        assert True

test_verify_expense()
test_create_expense()
test_modify_expense()
