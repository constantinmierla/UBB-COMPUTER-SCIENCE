from domain.entities import *
from repository.repo import *

class ServTractor:
    def __init__(self, repo,listaundo):
        """
        Constructor Controller
        :param repo: repository, type class
        :param listaundo: lista de undo, type lista
        """
        self.repo = repo
        self.listaundo = listaundo

    def adauga_serv(self, id, denumire, pret, model, data):
        """
        verifica daca obiectul e valid si il adauga
        :param id: id tractor, type str
        :param denumire: denumire tractor, type str
        :param pret: denumire pret, type str
        :param model: denumire model, type str
        :param data: denumire data, type str
        :return:
        :raise: Exception daca datele sunt invalide sau daca id ul exista deja
        """
        self.listaundo = self.repo.load_from_file()
        #validez
        if int(id)> 0 and int(id) < 999999 and int(pret)> 0 and int(pret) < 99999999:
            data.strip()
            """
            verificadata = data.split(':')
            if (verificadata[0]).isnumeric():
                if int(verificadata[0]) < 1 or int(verificadata[0]) > 31:
                    raise Exception
            else:
                raise Exception
            if int(verificadata[1]) < 1 or int(verificadata[1]) > 12:
                raise Exception
            if len(verificadata[2]) != 4:
                raise Exception
            """
            self.repo.adauga_repo(id,denumire,pret,model,data)
        else:
            raise Exception
    def sterge_serv(self, cifra):
        """
        sterge obiect daca contine pretul acea cifra
        :param cifra: cifra dorita, type str
        :return:
        """
        self.listaundo = self.repo.load_from_file()
        self.repo.sterge_repo(cifra)

    def filtrare_serv(self,text,numar):
        """
        filtreaza dupa cerintele dorite
        :param text: textul dorit, type str
        :param numar: numarul dorit, type str
        :return: lista filtrata, type lista
        """
        listanoua = []
        lista = self.repo.load_from_file()

        if text != '' and numar != '-1':
            for el in lista:
                if el.get_denumire() == text and int(el.get_pret()) < int(numar):
                    listanoua.append(el)
        elif text == '' and numar == '-1':
            for el in lista:
                listanoua.append(el)
        elif text == '':
            for el in lista:
                if int(el.get_pret()) < int(numar):
                    listanoua.append(el)
        elif numar == '-1':
            for el in lista:
                if el.get_denumire() == text:
                    listanoua.append(el)
        return listanoua

    def undo_serv(self):
        """
        face undo la operatia de adaugare sau stergere
        :return:
        :raise: Exception daca nu se mai poate face undo
        """
        if self.listaundo != []:
            self.repo.save_to_file(self.listaundo)
            self.listaundo = []
        else:
            raise Exception
