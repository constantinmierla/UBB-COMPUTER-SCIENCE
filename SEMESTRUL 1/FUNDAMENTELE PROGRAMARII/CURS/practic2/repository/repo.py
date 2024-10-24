from domain.entities import *

class RepoPiesa:
    def __init__(self,filename):
        self.filename = filename

    def load_from_file(self):
        lista = []
        with open (self.filename, 'r') as f:
            lines = f.readlines()
            for line in lines:
                if line != '':
                    line = line.strip()
                    titlu,regizor,gen,durata = line.split(';')
                    piesa = Piesa(titlu, regizor, gen, durata)
                    lista.append(piesa)
        return lista
    def save_to_file(self, lista):
        with open(self.filename,'w') as f:
            for piesa in lista:
                str = piesa.get_titlu() + ';' + piesa.get_regizor()+';' + piesa.get_gen()+';'+piesa.get_durata() + '\n'
                f.write(str)

    def adauga(self,titlu,regizor,gen,durata):
        lista = self.load_from_file()
        piesa = Piesa(titlu,regizor, gen, durata)
        lista.append(piesa)
        self.save_to_file(lista)

    def modifica(self, titlu,regizor,gen,durata):
        ok = 0
        lista = self.load_from_file()
        for el in lista:
            if el.get_titlu() == titlu and el.get_regizor() == regizor:
                el.set_gen(gen)
                el.set_durata(durata)
                ok = 1
        if ok == 1:
            self.save_to_file(lista)
        else:
            raise ValueError