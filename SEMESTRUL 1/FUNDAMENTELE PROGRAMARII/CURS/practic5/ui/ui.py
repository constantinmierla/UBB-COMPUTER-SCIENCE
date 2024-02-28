from repository.repo import RepoProdus
from domain.entities import Produs
from service.serv import ServProdus

class Console:
    def __init__(self,serv):
        self.serv = serv

    def adauga_ui(self):
        id = input('introduceti id ul : ')
        denumire = input('denumire: ')
        pret = input('pret: ')
        self.serv.adauga_serv(id,denumire,pret)

    def sterge_ui(self):
        nr = int(input('introduceti cifra: '))
        self.serv.sterge_serv(nr)

    def filtreaza_ui(self):
        text = input('introduceti textul: ')
        pret = int(input('introduceti pretul: '))
        lista = self.serv.filtreaza_serv(text,pret)
        for e in lista:
            print(e)
    def undo_ui(self):
        self.serv.undo_serv()

    def run(self):
        while True:
            print('Bine ati venit pe meniul principal!\n')
            cmd = input('Comenzi disponibile:\nadauga, sterge, filtrare, undo, stop\n')
            if cmd == 'adauga':
                self.adauga_ui()
            elif cmd =='sterge':
                self.sterge_ui()
            elif cmd == 'filtrare':
                self.filtreaza_ui()
            elif cmd == 'undo':
                self.undo_ui()
            elif cmd == 'stop':
                exit()
            else:
                print('Comanda invalida!')