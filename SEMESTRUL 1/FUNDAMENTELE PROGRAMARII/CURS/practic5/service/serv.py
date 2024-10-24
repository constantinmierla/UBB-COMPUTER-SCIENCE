from repository.repo import RepoProdus
from domain.entities import Produs
class ServProdus:
    def __init__(self,repo):
        self.repo = repo

    def adauga_serv(self,id,denumire,pret):
        #valideaza_adauga(id,denumire,pret)
        self.repo.adauga_repo(id,denumire,pret)

    def sterge_serv(self, nr):
        #lista = self.repo.load_from_file()
        undolist = []
        self.repo.sterge_repo(nr,undolist)

    def filtreaza_serv(self, text, pret):
        listanoua = []
        lista = self.repo.load_from_file()
        if text == '':
            #sortare dupa pret
            for e in lista:
                if int(e.get_pret()) < pret:
                    listanoua.append(e)
            print(1)
        elif pret == -1:
            for e in lista:
                if e.get_denumire() == text:
                    listanoua.append(e)
            print(2)
        else:
            for e in lista:
                if int(e.get_pret()) < pret and e.get_denumire() == text:
                    listanoua.append(e)
            print(3)
        return listanoua

    def undo_serv(self):
        pass
