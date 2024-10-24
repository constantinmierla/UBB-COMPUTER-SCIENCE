from domain.entities import Produs
class RepoProdus:
    def __init__(self, filename):
        self.__filename = filename

    def load_from_file(self):
        lista = []
        with open(self.__filename, 'r') as f:
            lines = f.readlines()
            for line in lines:
                if line != '':
                    line = line.strip()
                    id,denumire,pret = line.split(';')
                    produs = Produs(id, denumire, pret)
                    lista.append(produs)
        return lista

    def save_to_file(self, lista):
        with open(self.__filename, 'w') as f:
            for e in lista:
                string = str(e.get_id()) + ';' + str(e.get_denumire()) + ';' + str(e.get_pret()) + '\n'
                f.write(string)

    def adauga_repo(self, id, denumire, pret):
        lista = self.load_from_file()
        produs = Produs(id, denumire, pret)
        lista.append(produs)
        self.save_to_file(lista)

    def sterge_repo(self, nr, undolist):
        lista = self.load_from_file()
        listanoua = []
        for e in lista:
            idd = int(e.get_id())
            ok = 0
            while idd > 0:
                if idd % 10 == nr:
                    ok = 1
                idd = idd//10

            if ok == 0:
                listanoua.append(e)
            else:
                undolist.append(e)

        self.save_to_file(listanoua)
