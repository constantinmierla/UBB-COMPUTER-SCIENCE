from domain.entities import Jucator
from repository.repo import RepoJucator
import random

class ServJucator:
    def __init__(self,repo):
        self.repo = repo

    def adauga_serv(self,nume,prenume,inaltime,post):
        jucator = Jucator(nume,prenume,inaltime,post)
        self.repo.adauga_repo(jucator)

    def modifica_serv(self,nume,prenume,inaltime):
        try:
            self.repo.modifica_repo(nume,prenume,inaltime)
        except Exception:
            print('Jucator inexistent!\n')

    def tipareste_serv(self):
        lista = self.repo.load_from_file()
        lista = sorted(lista, key = lambda x:x.get_inaltime(), reverse = True)
        fundas = [x for x in lista if x.get_post() == 'Fundas']
        pivot = [x for x in lista if x.get_post() == 'Pivot']
        extrema = [x for x in lista if x.get_post() == 'Extrema']
        listanoua = []
        listanoua.append(fundas[0])
        listanoua.append(fundas[1])
        listanoua.append(pivot[0])
        listanoua.append(extrema[0])
        listanoua.append(extrema[1])
        return listanoua

    def import_serv(self,filename):
        lista = []
        lista2 = self.repo.load_from_file()
        with open(filename, 'r') as f:
            lines = f.readlines()
            for line in lines:
                if line != '':
                    line = line.strip()
                    nume,prenume = line.split(' ')
                    ok = 1
                    for el in lista2:
                        if el.get_nume() == nume and el.get_prenume() == prenume:
                            ok = 0
                    if ok == 1:
                        inaltime = random.randint(150,230)
                        post = random.choice(['Fundas','Pivot','Extrema'])
                        self.adauga_serv(nume,prenume,inaltime,post)


