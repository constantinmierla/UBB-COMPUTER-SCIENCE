from repository.repo import *
from service.serv import *

class Console:
    def __init__(self, serv):
        self.serv = serv
        #self.lista_curenta = []
        self.an = -1
        self.sir = ''

    #def afiseaza_lista(self):
      #  self.lista_curenta = self.serv.repo.load_from_file()
       # for el in self.lista_curenta:
        #    print(el)
    def adauga_ui(self):
        id = int(input('introduceti id: '))
        titlu = input('introduceti titlu: ')
        autor = input('introduceti autor: ')
        an = int(input('introduceti an: '))
        self.serv.adauga_serv(id,titlu,autor,an)

    def sterge_ui(self):
        cifra = int(input('introduceti cifra: '))
        self.serv.sterge_serv(cifra)

    def undo_ui(self):
        try:
            self.serv.undo_serv()
        except Exception:
            print('Nu se mai poate face undo!\n')
    def filtrare_ui(self):
        self.sir = input('introduceti sirul: ')
        self.numar = int(input('introduceti numarul: '))
        lista = self.serv.filtrare_serv(self.sir,self.numar)


    def run(self):
        while True:
            print('Bine ati venit pe meniul principal!')
            #self.afiseaza_lista()
            lista = self.serv.filtrare_serv(self.sir, self.an)
            for el in lista:
                print (el)
            print (f"{self.sir}, {self.an}")
            cmd = input('introduceti optiunea: adauga, sterge, filtrare, undo, stop\n')
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
                print('comanda ',cmd,' este invalida!\nRevenire la meniu...')
