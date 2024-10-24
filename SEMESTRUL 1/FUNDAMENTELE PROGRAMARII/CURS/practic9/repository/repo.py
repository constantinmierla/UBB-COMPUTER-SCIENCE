from domain.entities import Jucator
import random
class RepoJucator:
    def __init__(self, filename):
        self.filename = filename

    def load_from_file(self):
        """
        incarca din fisierul txt
        :return: lista
        """
        lista = []
        with open(self.filename, 'r') as f:
            lines = f.readlines()
            for line in lines:
                if line != '':
                    line = line.strip()
                    nume,prenume,inaltime,post = line.split(',')
                    jucator = Jucator(nume,prenume,inaltime,post)
                    lista.append(jucator)
        return lista

    def save_to_file(self, lista):
        with open(self.filename, 'w') as f:
            for e in lista:
                f.write(str(str(e) + '\n'))


    def adauga_repo(self,Jucator):
        lista = self.load_from_file()
        lista.extend([Jucator])
        self.save_to_file(lista)

    def modifica_repo(self,nume,prenume,inaltime):
        lista = self.load_from_file()
        ok = 0
        for e in lista:
            if e.get_nume() == nume and e.get_prenume() == prenume:
                e.set_inaltime(inaltime)
                ok = 1
        self.save_to_file(lista)

        if ok == 0:
            raise Exception