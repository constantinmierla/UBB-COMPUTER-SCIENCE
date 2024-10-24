from domain.entities import *
from repository.repo import *

class ServCarte:
    def __init__(self, repo):
        self.repo = repo

    def adauga_serv(self, id, titlu, autor, an):
        #validator
        carte = Carte(id,titlu,autor, an)
        self.repo.adauga_repo(carte)

    def sterge_serv(self,cifra):
        #validator
        self.repo.sterge_repo(cifra)

    def undo_serv(self):
        lista = self.repo.lista_veche
        if not lista:
            raise Exception
        else:
            lista.extend(self.repo.load_from_file())
            self.repo.lista_veche = []
            self.repo.save_to_file(lista)

    def filtrare_serv(self, sir, numar):
        lista = self.repo.load_from_file()
        listanoua = []
        if sir == '' and numar ==-1:
            for el in lista:
                listanoua.append(el)

        elif sir != '' and numar != -1:
            for el in lista:
                if el.get_titlu() == sir and int(el.get_an()) < numar:
                    listanoua.append(el)

        elif sir == '':
            for el in lista:
                if int(el.get_an()) < numar:
                    listanoua.append(el)

        else:
            for el in lista:
                if el.get_titlu() == sir:
                    listanoua.append(el)

        return listanoua





