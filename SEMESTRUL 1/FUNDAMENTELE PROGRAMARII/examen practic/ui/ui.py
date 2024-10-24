from domain.entities import *
from repository.repo import *
from service.serv import *

class Console:
    def __init__(self,serv,text,numar,listafiltru):
        """
        initialiare Consola
        :param serv: service
        :param text: textul
        :param numar: numarul
        :param listafiltru: lista care mentine filtrul
        """
        self.serv = serv
        self.text = text
        self.numar = numar
        self.listafiltru = self.serv.filtrare_serv(self.text,self.numar)

    def adauga_ui(self):
        """
        Adauga obiect
        :return:
        :raise: Exception daca sunt invalide datele
        """
        id = input('introduceti id ul: ')
        denumire = input('introduceti denumire: ')
        pret = input('introduceti pretul: ')
        model = input('introduceti model: ')
        data = input('introduceti data: ')
        try:
            self.serv.adauga_serv(id,denumire,pret,model,data)
        except Exception:
            print('Eroare adauga!\n')

    def sterge_ui(self):
        """
        Sterge obiect
        :return:
        raise: Exception daca e invalida cifra
        """
        cifra = input('introduceti cifra : ')
        self.serv.sterge_serv(cifra)

    def filtrare_ui(self):
        """
        Filtreaza dupa textul si numarul dorit
        :return:
        """
        self.text = input('introduceti textul: ')
        self.numar = int(input('introduceti numarul : '))
        self.listafiltru = self.serv.filtrare_serv(self.text,self.numar)

    def undo_ui(self):
        """
        face undo la operatia de adaugare sau stergere
        :return:
        :raise: Exception daca nu se mai poate face undo
        """
        try:
            self.serv.undo_serv()
        except Exception:
            print('Nu se mai poate face undo!\n')


    def run(self):
        """
        Meniul principal al aplicatiei
        :return:
        """
        print('Bine ati venit pe meniul principal!')
        #self.listafiltru = self.serv.filtrare_serv(self.text, self.numar)
        while True:
            print('filtru curent:', self.text,',',self.numar)
            for e in self.listafiltru:
                print(e)
            cmd = input('Introduceti comanda: adauga, sterge, filtrare, undo, stop\n')
            if cmd == 'adauga':
                self.adauga_ui()
            elif cmd == 'sterge':
                self.sterge_ui()
            elif cmd == 'filtrare':
                self.filtrare_ui()
            elif cmd == 'undo':
                self.undo_ui()
            elif cmd == 'stop':
                exit()
            else:
                print('comanda ',cmd,' este invalida!\nRevenire meniu principal...')
