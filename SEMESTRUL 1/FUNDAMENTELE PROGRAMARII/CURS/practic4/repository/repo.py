from domain.entities import Carte
class RepoCarte:
    def __init__(self, filename, lista_veche):
        self.filename = filename
        self.lista_veche = lista_veche
    def load_from_file(self):
        lista = []
        with open(self.filename, 'r') as f:
            lines = f.readlines()
            for line in lines:
                if line != '':
                    line = line.strip()
                    id,titlu,autor,an = line.split(';')
                    carte = Carte(id,titlu,autor,an)
                    lista.append(carte)
        return lista

    def save_to_file(self, lista):
        with open(self.filename, 'w') as f:
            for e in lista:
                string = str(str(e.get_id()) + ';' + str(e.get_titlu()) + ';' + str(e.get_autor()) + ';' + str(e.get_an()) + '\n')
                f.write(string)

    def adauga_repo(self, carte):
        lista = self.load_from_file()
        lista.append(carte)
        self.save_to_file(lista)

    def sterge_repo(self, cifra):
        lista = self.load_from_file()
        lista_noua = []
        self.lista_veche = []
        for e in lista:
            anul = int(e.get_an())
            ok = 0
            while anul > 0:
                if anul%10 == cifra:
                    ok = 1
                anul = anul//10
            if ok == 0:
                lista_noua.append(e)
            else:
                self.lista_veche.append(e)
        self.save_to_file(lista_noua)