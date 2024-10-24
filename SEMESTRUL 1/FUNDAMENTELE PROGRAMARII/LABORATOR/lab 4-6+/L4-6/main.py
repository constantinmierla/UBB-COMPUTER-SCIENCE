import sys
import datetime

apartment_expenses = {}

expense_history = []


def print_menu():
    """
    FUNCTIE DE PRINTARE A MENIULUI PRINCIPAL AL APLICATIEI
    """
    print("MENIUL PRINCIPAL\n")
    print("1. Adaugare")
    print("2. Stergere")
    print("3. Cautari")
    print("4. Rapoarte")
    print("5. Filtru")
    print("6. Undo")
    print("7. Iesire aplicatie\n")


def add_expense(apartment_number, amount, expense_type):
    """
        FUNCTIE CARE ADAUGA CHELTUIALA PENTRU UN APARTAMENT
    """
    if apartment_number not in apartment_expenses:
        apartment_expenses[apartment_number] = []
    expense = (amount, expense_type, datetime.date.today())
    apartment_expenses[apartment_number].append(expense)
    expense_history.append(expense)


def modify_expense(apartment_number, index, amount, expense_type):
    """
        FUNCTIE CARE MODIFICA CHELTUIALA PENTRU UN APARTAMENT
    """
    if apartment_number in apartment_expenses and 0 <= index < len(apartment_expenses[apartment_number]):
        apartment_expenses[apartment_number][index] = (amount, expense_type, datetime.date.today())
        expense_history.append((amount, expense_type, datetime.date.today()))


def add_menu():
    """
    FUNCTIE CARE POATE ADAUGA CHELTUIALA PENTRU UN APARTAMENT SAU MODIFICA CHELTUIALA
    """

    add_option = int(input("Selecteaza optiunea:\n"
                       "1. Adauga cheltuiala pentru un apartament\n"
                       "2. Modifica cheltuiala\n"))
    if add_option == 1:
        apartment_number = int(input("Introduceti numarul apartamentului: "))
        amount = float(input("Introduceti suma cheltuielii: "))
        expense_type = input("Introduceti tipul cheltuielii: \n"
                             "Tipuri disponibile :  apa, canal, incalzire, gaz, altele: ")
        add_expense(apartment_number, amount, expense_type)

    elif add_option == 2:
        apartment_number = int(input("Introduceti numarul apartamentului: "))
        index = int(input("Introduceti indexul cheltuielii de modificat: "))
        amount = float(input("Introduceti noua suma: "))
        expense_type = input("Introduceti noul tip: \n"
                             "Tipuri disponibile :  apa, canal, incalzire, gaz, altele: ")
        modify_expense(apartment_number, index - 1, amount, expense_type)


def remove_expenses_by_type(expense_type):
    """
    FUNCTIE CARE ELIMINA CHELTUIALA DE UN ANUMIT TIP
    """
    for apartment, expenses in apartment_expenses.items():
        apartment_expenses[apartment] = [(amount, t, date) for amount, t, date in expenses if t != expense_type]


def remove_expenses_less_than_amount(amount):
    """
    FUNCTIE CARE ELIMINA TOATE CHELTUIELILE MAI MICI DECAT O SUMA DATA
    """
    for apartment, expenses in apartment_expenses.items():
        apartment_expenses[apartment] = [(a, t, date) for a, t, date in expenses if a >= amount]

def print_total_expense_by_type(expense_type):
    """
    FUNCTIE CARE TIPARESTE SUMA TOTALA PENTRU UN TIP DE CHELTUIALA
    """
    total_expense = sum(amount for expenses in apartment_expenses.values() for amount, t, _ in expenses if t == expense_type)
    print(f"Suma totală pentru cheltuielile de tipul '{expense_type}' este: {total_expense}")


def sort_apartments_by_type():
    """
    FUNCTIE CARE TIPARESTE APARTAMENTELE SORTATE DUPA UN TIP DE CHELTUIALA
    """
    expense_type = input("Introduceti tipul de cheltuiala pentru a sorta apartamentele: ")
    sorted_apartments = sorted(apartment_expenses.keys(), key=lambda apartment: sum(amount for amount, t, _ in apartment_expenses[apartment] if t == expense_type))

    print(f"Apartamentele sortate după cheltuielile de tipul '{expense_type}':")
    for apartment in sorted_apartments:
        print(f"Apartamentul {apartment}")


def print_total_expense_for_apartment(apartment_number):
    """
    FUNCTIE CARE TIPARESTE TOTALUL DE CHELTUIELI PENTRU UN APARTAMENT DAT
    """
    if apartment_number in apartment_expenses:
        total_expense = sum(amount for amount, _, _ in apartment_expenses[apartment_number])
        print(f"Totalul de cheltuieli pentru apartamentul {apartment_number} este: {total_expense}")
    else:
        print(f"Apartamentul {apartment_number} nu exista in baza de date.")


def add_1():
    """
    FUNCTIE CARE ADAUGA SAU MODIFICA CHELTUIALA PENTRU UN APARTAMENT
    """

    add_menu()


def delete_2():
    """
    FUNCTIE CARE PERMITE STERGEREA CHELTUIELILOR DIN APARTAMENTE
    """


def find_3():
    """
    FUNCTIE CARE TIPARESTE CHELTUIELI
    """


def report_4():
    """
    FUNCTIE CARE TIPARESTE TOTALUL DE CHELTUIELI PENTRU UN APARTAMENT DAT
    """
    print("Selectati optiunea:")
    print("1. Tipărește suma totală pentru un tip de cheltuială")
    print("2. Tipărește toate apartamentele sortate după un tip de cheltuială")
    print("3. Tipărește totalul de cheltuieli pentru un apartament dat")

    option = int(input("Optiune: "))

    if option == 1:
        expense_type = input("Introduceti tipul de cheltuiala pentru care doriti suma totala: ")
        print_total_expense_by_type(expense_type)
    elif option == 2:
        sort_apartments_by_type()
    elif option == 3:
        apartment_number = int(input("Introduceti numarul apartamentului pentru care doriti suma totala: "))
        print_total_expense_for_apartment(apartment_number)
    else:
        print("Optiune invalida. Va rugam selectati o optiune valida (1, 2 sau 3).")



def filter_5():
    """
    FUNCTIE CARE ELIMINA TOATE CHELTUIELILE DE UN ANUMIT TIP
                 ELIMINA TOATE CHELTUIELILE MAI MICI DECAT O SUMA DATA
    """
    filter_option = int(input("Selectati optiunea:\n"
                              "1. Elimină toate cheltuielile de un anumit tip\n"
                              "2. Elimină toate cheltuielile mai mici decât o sumă dată\n"))

    if filter_option == 1:
        expense_type = input("Introdu tipul de cheltuiala: ")
        remove_expenses_by_type(expense_type)
    elif filter_option == 2:
        amount = float(input("Introdu valoarea minima: "))
        remove_expenses_less_than_amount(amount)
    else:
        print("Eroare. Optiuni disponibile: 1 si 2")

def undo_6():
    """
    Reface ultima operație (lista de cheltuieli revine la ce exista înainte de ultima operație care a modificat lista).
    """

def leave_7():
    """
    FUNCTIE CARE PERMITE IESIREA DIN APLICATIE
    """

    print("Iesire aplicatie")
    sys.exit()


def read_option():
    """
    FUNCTIE DE CITIRE A OPTIUNII
    """
    try:
        option = int(input("Introduceti numarul optiunii : "))
        return option
    except ValueError:
        print("Introduceti un numar valid.\n")
        return None


def chosed_option(option):
    """
    FUNCTIE CARE REDIRECTIONEAZA ALEGEREA UTILIZATORULUI CATRE FUNCTIA ASOCIATA
    """
    print("")
    if option == 1:
        add_1()
    elif option == 2:
        delete_2()
    elif option == 3:
        find_3()
    elif option == 4:
        report_4()
    elif option == 5:
        filter_5()
    elif option == 7:
        leave_7()
    elif option < 1 or option > 7:
        print("Introduceti un numar valid.")


def test_add_expense():
    apartment_expenses.clear()
    add_expense(101, 200.0, "apa")
    assert len(apartment_expenses) == 1
    assert len(apartment_expenses[101]) == 1
    assert apartment_expenses[101][0] == (200.0, "apa", datetime.date.today())


def test_modify_expense():
    apartment_expenses[1] = [(150.0, "apa", datetime.date(2021, 2, 3))]
    modify_expense(1, 0, 200.0, "gaz")
    assert len(apartment_expenses[1]) == 1
    assert apartment_expenses[1][0] == (200.0, "gaz", datetime.date.today())


def test_remove_expenses_by_type():
    apartment_expenses[1] = [(200.0, "apa", datetime.date(2023, 1, 1)),
                               (100.0, "gaz", datetime.date(2023, 1, 2))]
    remove_expenses_by_type("apa")
    assert len(apartment_expenses[1]) == 1
    assert apartment_expenses[1][0] == (100.0, "gaz", datetime.date(2023, 1, 2))


def test_remove_expenses_less_than_amount():
    apartment_expenses[1] = [(200.0, "apa", datetime.date(2023, 5, 28)),
                               (100.0, "gaz", datetime.date(2023, 12, 22)),
                               (50.0, "apa", datetime.date(2023, 7, 28))]
    remove_expenses_less_than_amount(150.0)
    assert len(apartment_expenses[1]) == 1
    assert apartment_expenses[1][0] == (200.0, "apa", datetime.date(2023, 5, 28))


def tests():
    test_add_expense()
    test_modify_expense()
    test_remove_expenses_by_type()
    test_remove_expenses_less_than_amount()
    apartment_expenses.clear()

def main():

    tests()
    while True:

        print_menu()
        option = read_option()
        chosed_option(option)


main()