from domain.entities import *
from repository.repo import *
from service.serv import *
class Console:
    def __init__(self, serv):
        self.serv = serv

    def adauga_ui(self):
        nume = input('introduceti numele ')
        prenume = input('introduceti prenumele ')
        inaltime = input('introduceti intaltimea ')
        post = input('introduceti postul ')
        self.serv.adauga_serv(nume,prenume,inaltime,post)

    def modifica_ui(self):
        nume = input('introduceti numele ')
        prenume = input('introduceti prenumele ')
        inaltime = input('introduceti intaltimea ')
        self.serv.modifica_serv(nume,prenume,inaltime)

    def tipareste_ui(self):
        lista = self.serv.tipareste_serv()
        for el in lista:
            print(el)


    def importa_ui(self):
        self.serv.import_serv('jucatori.txt')
    def run(self):
        print('Meniul principal: ')
        while True:
            cmd = input('adauga, modifica, tipareste, import, stop: ')
            if cmd == 'adauga':
                self.adauga_ui()
            elif cmd == 'modifica':
                self.modifica_ui()
            elif cmd == 'tipareste':
                self.tipareste_ui()
            elif cmd == 'import':
                self.importa_ui()
            elif cmd == 'stop':
                exit()
            else:
                print('comanda ',cmd,' este invalida\nRevenire la meniul principal...')
