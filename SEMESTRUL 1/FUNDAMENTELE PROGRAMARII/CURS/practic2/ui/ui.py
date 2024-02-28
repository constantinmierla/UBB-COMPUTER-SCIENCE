from service.serv import ServPiesa
class Console:
    def __init__(self,srv):
        self.__srv = srv
    def adauga(self):
        titlu = input('Introduceti titlu: ')
        regizor = input('Introduceti regizor: ')
        gen = input('Introduceti gen: ')
        durata = input('Introduceti durata: ')
        self.__srv.adauga(titlu,regizor,gen,durata)
        #try except

    def modifica(self):
        titlu = input('Introduceti titlu: ')
        regizor = input('Introduceti regizor: ')
        gen = input('Introduceti gen: ')
        durata = input('Introduceti durata: ')
        self.__srv.modifica(titlu, regizor, gen, durata)
        #try except

    def export(self):
        nume_fisier = input('Nume fisier pentru export: ')
        self.__srv.export(nume_fisier)
    def random(self):
        numar = input('Introduceti numarul de piese: ')
        self.__srv.random(numar)

    def start(self):
        while True:
            print('Comenzi: adauga, modifica, random, export, stop')
            cmd = input('Comanda dvs: ')
            if cmd == 'adauga':
                self.adauga()
            elif cmd == 'modifica':
                self.modifica()
            elif cmd == 'random':
                self.random()
            elif cmd == 'export':
                self.export()
            elif cmd == 'stop':
                exit()
            else:
                print('Comanda invalida')