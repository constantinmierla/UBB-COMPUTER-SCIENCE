from repository.repo import *
import random
class ServPiesa:
    def __init__(self, repo):
        self.__repo = repo
    def adauga(self,titlu,regizor,gen,durata):
        #validare
        self.__repo.adauga(titlu,regizor, gen, durata)

    def modifica(self,titlu,regizor,gen,durata):
        self.__repo.modifica(titlu,regizor,gen,durata)

    def export(self, filename):
        lista = self.__repo.load_from_file()
        lista = sorted(lista, key = lambda x:(x.get_titlu(), x.get_regizor()))
        with open(filename, 'w') as f:
            for el in lista:
                str = el.get_titlu() + ';' + el.get_regizor() + ';' + el.get_gen() + ';' + el.get_durata() + '\n'
                f.write(str)
    def random(self,numar):
        genuri = ['altele', 'satira', 'drama', 'comedie']
        vocale = ['a', 'e', 'i', 'o', 'u']
        consoane = ['b', 'c', 'd', 'f', 'g', 'h', 'j','k','l']
        titlu_list = []
        regizor_list = []
        titlu = ''
        regizor = ''
        ok = 0
        for i in range(int(numar)):
            litere = random.randint(8,12)
            spatiu = random.randint(1, litere)
            for j in range(litere):
                if ok == 0:
                    titlu_list.append(random.choice(vocale))
                    regizor_list.append(random.choice(vocale))
                    ok = 1
                else:
                    titlu_list.append(random.choice(consoane))
                    regizor_list.append(random.choice(consoane))
                    ok = 0
            titlu_list[spatiu] = ' '
            regizor_list[spatiu] = ' '
            for el in titlu_list:
                titlu+= el
            for el in regizor_list:
                regizor += el

            gen = random.choice(genuri)
            durata = str(random.randint(1,1000))
            self.adauga(titlu,regizor,gen,durata)
            titlu_list = []
            regizor_list = []
            titlu = ''
            regizor = ''
            ok = 0