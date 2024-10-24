from domain.entities import *
class RepoTractor:
    def __init__(self, filename):
        """
        initializare
        :param filename: string
        """
        self.filename = filename


    def load_from_file(self):
        """
        incarca din fisier
        :return: lista din fisier, type str
        """
        lista = []
        with open(self.filename, 'r') as f:
            lines = f.readlines()
            for line in lines:
                if line != '':
                    line.strip()
                    id,denumire,pret,model,data = line.split(';')
                    tractor = Tractor(id,denumire,pret,model,data)
                    lista.append(tractor)
        return lista

    def save_to_file(self, lista):
        """
        salveaza in fisier
        :param lista: lista de salvat, type lista
        :return:
        """
        with open(self.filename, 'w') as f:
            for e in lista:
                f.write(str(e))
                #print(str(str(e) + '\n'))

    def adauga_repo(self,id,denumire,pret,model,data):
        """
        adauga obiect
        :param id: id tractor, type str
        :param denumire: denumire tractor, type str
        :param pret: denumire pret, type str
        :param model: denumire model, type str
        :param data: denumire data, type str
        :return:
        """
        lista = self.load_from_file()
        for e in lista:
            if e.get_id() == id:
                raise Exception
        tractor = Tractor(id,denumire,pret,model,data)
        lista.extend(['\n',tractor])
        self.save_to_file(lista)

    def sterge_repo(self,cifra):
        """
        sterge obiect daca contine pretul acea cifra
        :param cifra: cifra dorita, type str
        :return:
        """
        lista = self.load_from_file()
        listanoua = []
        for e in lista:
            numar = int(e.get_pret())
            ok = 0
            while numar > 0:
                if numar%10 == int(cifra):
                    ok = 1
                numar = numar//10

            if ok == 0:
                listanoua.append(e)
        self.save_to_file(listanoua)

def test_repo():
#test load
    repo = RepoTractor('testtractor.txt')
    listainitiala = repo.load_from_file()
    assert len(listainitiala) == 1

    #test save
    listanoua = [Tractor('2','Case','10000','3210','20:10:2023')]
    repo.save_to_file(listanoua)
    listatest = repo.load_from_file()
    assert listatest[0].get_id() == '2'
    repo.save_to_file(listainitiala)

    #test adauga
    def adauga():
        repo.adauga_repo('3','Tractor','1999','2121','29:12:2024')
        listaadauga = repo.load_from_file()
        assert listaadauga[1].get_pret() == '1999'
        repo.save_to_file(listainitiala)

test_repo()