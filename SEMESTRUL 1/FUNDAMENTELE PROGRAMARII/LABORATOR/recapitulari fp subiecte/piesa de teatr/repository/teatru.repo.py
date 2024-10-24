from domain.entities import Piesa

class Teatru_Repo:

    def __init__(self):
        self.__piese = []
        self.__filename = "piese.txt"
        self.read_from_file()

    def read_from_file(self):
        with open(self.__filename, 'r') as f:
            for line in f:
                line = line.strip().split(";")