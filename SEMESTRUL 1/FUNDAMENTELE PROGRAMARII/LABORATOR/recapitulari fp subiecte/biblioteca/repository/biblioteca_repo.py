from domain.entities import Carte

class Biblioteca_repo:

    def __init__(self):
        self.__carti = []
        self.__filename = "carti.txt"
        self.read_from_file()

    def add(self, carte):
        self.__carti.append(carte)
        self.update_file()

    def read_from_file(self):
        with open(self.filename,'r') as f:
            for line in f:
                line = line.strip().split(";")
                carte = Carte(id = line[0], titlu = line[1], autor = line[2], an = line[3])
                self.carti.append(carte)

    def update_file(self):
        with open(self.filename, 'w') as f:
            for carte in self.__carti:
                f.write(str(carte))

    def modify_list(self, carte):
    