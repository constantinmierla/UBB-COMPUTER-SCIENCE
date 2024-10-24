from domain.e_list import generate_expenses,add_expense,delete_expenses_by_ap,delete_expenses_by_aps,delete_expenses_by_type,all_expenses_by_type,aps_by_summ,aps_w_expenses,total_expense_for_ap,total_expense_for_type,aps_sorted_by_type,eliminate_expenses_by_summ,eliminate_expenses_by_type
from domain.expense import modify_expense,ExpenseError,create_expense
from utils.list_operations import copy_list, update_undo, remove_from_undo_list
import datetime

def read_option_UI():
    """
    Functie pentru citirea optiunii
    """
    while True:
        option = input("Introduceti o optiune: ")
        try:
            option = int(option)
            return option
        except ValueError:
            print("Va rugam sa introduceti o optiune valida")

def add_expense_UI(expenses_list):
    """
    Functia are rolul de a adauga o cheltuiala
    """
    apartment_number = input("Introduceti numarul apartamentului: ")
    type = input("Introduceti tipul cheltuielii(gaz,apa,canalizare,incalzire): ")
    amount = input("Introduceti suma cheltuielii: ")

    try:
        apartment_number = int(apartment_number)
        amount = int(amount)
        x = datetime.datetime.now().date()
        expense = create_expense(apartment_number, type, amount, x)
        add_expense(expenses_list, expense)
        print("Cheltuiala adaugata cu succes")
          
    except ValueError:
        print("Datele introduse nu sunt valide")
    except ExpenseError:
        print("Exista deja o cheltuiala")

def modify_expense_UI(expenses_list):
    """
    Funcitia modifica o cheltuiala existenta
    """
    apartment_number = input("Introduceti numarul apartamentului: ")
    type = input("Introduceti tipul cheltuielii(gaz,apa,canalizare,incalzire): ")
    amount = input("Introduceti suma noua a cheltuielii: ")
    try:
        apartment_number = int(apartment_number)
        amount = int(amount)
        x = datetime.datetime.now().date()
        new_expense = create_expense(apartment_number, type, amount, x) 
        modify_expense(expenses_list, new_expense)
        print("Modificare efectuata cu succes")
    except ValueError:
        print("Datele introduse nu sunt valide")
    except ExpenseError:
        print("Cheltuiala este inexistenta")
 
def delete_expenses_by_ap_UI(expenses_list):
    """
    Funcia sterge toate cheltuielile de la un apartament
    """
    number = input("Introduceti numarul apartamentului: ")

    try:
        number = int(number)
        delete_expenses_by_ap(expenses_list,number)
        print("Stergere efectuata cu succes")
    except ValueError:
        print("Introduceti un numar valid")

def delete_expenses_by_aps_UI(expenses_list):
    """
    Functia sterge cheltuielile de la apartamente consecutive
    """
    ap_nr_1 = input("Introduceti numarul primului apartament: ")
    ap_nr_2 = input("Introduceti numarul celui de al doilea apartament: ")

    try:
        ap_nr_1 = int(ap_nr_1)
        ap_nr_2 = int(ap_nr_2)
        delete_expenses_by_aps(expenses_list,ap_nr_1,ap_nr_2)
        print("Stergere efectuata cu succes")
    except ValueError:
        print("Numerele nu sunt valide")

def delete_expenses_by_type_UI(expenses_list):  
    """
    Functia sterge cheltuielile de un anumit tip de la toate apartamentele
    """
    try:
        ap_type = input("Introduceti tipul cheltuielii(gaz, incalzire, apa, canalizare): ")
        

        delete_expenses_by_type(expenses_list,ap_type)

        print("Stergere efectuata cu succes")
    except ValueError:
        print("Tipul nu este vaild")

def all_expenses_by_type_UI(expenses_list):
    """
    Functia tipareste toate cheltuielile de un anumit tip
    """
    ap_type = input("Introduceti tipul cheltuielii(gaz,apa,incalzire,canalizare): ")
    try:
        new_list = all_expenses_by_type(expenses_list, ap_type)
        print(new_list)
    except ValueError:
        print("Tipul nu este valid")

def aps_by_summ_UI(expenses_list):
    """
    Functia tipareste apartamentele care au cheltuieli mai mari decat o suma data
    """
    summ = input("Introduceti suma: ")

    try:
        summ = int(summ)
        aps_w_expenses_list = aps_w_expenses(expenses_list)
        aps_by_summ_list = aps_by_summ(expenses_list, aps_w_expenses_list, summ)
        print(aps_by_summ_list)
    except ValueError:
        print("Suma introdusa nu este valida")

def all_expenses_by_date_UI(expenses_list):
    """
    Functia tipareste cheltuielile efectuate inainte de o zi si mai mari decat o suma data
    """
    print("Soon")

def total_expense_for_ap_UI(expenses_list):
    """
    Functia tipareste totalul de cheltuieli pentru un apartament dat
    """
    nr_ap = input("Introduceti numarul apartamentului: ")
    
    try:
        nr_ap = int(nr_ap)
        total_expense = total_expense_for_ap(expenses_list, nr_ap)
        print("Cheltuielile totale sunt de: ",total_expense,"lei")
    except ValueError:
        print("Introduceti un numar valid")

def total_expense_for_type_UI(expenses_list):
    """
    Functia tipareste suma totala pentru un anumit tip de cheltuiala
    """
    ap_type = input("Introduceti tipul cheltuielii(gaz,apa,incalzire,canalizare): ")

    try:
        total_expense = total_expense_for_type(expenses_list, ap_type)
        print("Suma totala este de: ",total_expense," lei")
    except ValueError:
        print("Tipul nu este valid")

def sort_aps_by_type_UI(expenses_list):
    """
    Functia tipareste apartamentele sortate dupa un tip de cheltuiala
    """

    ap_type = input("Introduceti tipul: ")

    try:
        aps_list = aps_sorted_by_type(expenses_list, ap_type)
        print(aps_list)
    except ValueError:
        print("Tipul nu este valid")

def eliminate_expenses_by_type_UI(expenses_list):
    """
    Functia elimina cheltuielile de un anumit tip
    """
    ap_type = input("Introduceti tipul cheltuielii(gaz,apa,incalzire,canalizare): ")
    try:
        new_list = eliminate_expenses_by_type(expenses_list,ap_type)
        return new_list
    except ValueError:
        print("Tipul nu este valid")
        return -1

def eliminate_expenses_by_summ_UI(expenses_list):
    """
    Functia elimina cheltuielile mai mici deca o suma data
    """
    summ = input("Introduceti o suma: ")

    try:
        summ = int(summ)
        new_list = eliminate_expenses_by_summ(expenses_list, summ)
        return new_list
    except ValueError:
        print("Suma introdusa nu este valida")
        return -1

def make_undo(undo_list):
    """
    Functia returneaza 
    """
    len_undo = len(undo_list)
    if len_undo > 1:
        new_list = copy_list(undo_list[len_undo-2])
        remove_from_undo_list(undo_list, len_undo)
        return new_list
    else:
        print("Nu se poate face undo")
        return -1

def main():
    """
    Funcitia principala pentru comenzi de tip string
    """
    expenses_list = generate_expenses()
    undo_list = [{}]
    while True:
        print("Comenzi disponibile: add, delete, find, filter, undo, show")
        update_undo(expenses_list, undo_list)
        cmd = input("Introduceti comanda: ")
        if cmd == "add":
            add_expense_UI(expenses_list)
        elif cmd == "delete":
            delete_expenses_by_ap_UI(expenses_list)
        elif cmd == "find":
            aps_by_summ_UI(expenses_list)
        elif cmd == "filter":
            total_expense_for_type_UI(expenses_list)
        elif cmd == "undo":
            new_list = make_undo(undo_list)
            if(new_list != -1):
                expenses_list = new_list
                print("Undo realizat cu succes")
        elif cmd == "exit":
            return
        elif cmd == "show":
            print (expenses_list)
        else:
            print("Comanda nu este valida")