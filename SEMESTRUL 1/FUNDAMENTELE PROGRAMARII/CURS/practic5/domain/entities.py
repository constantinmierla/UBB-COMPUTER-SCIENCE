class Produs:
    def __init__(self, id, denumire, pret):
        self.__id = id
        self.__denumire = denumire
        self.__pret = pret

    def get_id(self):
        return self.__id

    def get_denumire(self):
        return self.__denumire

    def get_pret(self):
        return self.__pret

    def set_id(self, value):
        self.__id = value

    def set_denumire(self, value):
        self.__denumire = value

    def set_pret(self, value):
        self.__pret = value

    def __str__(self):
        return f"Produs: {self.__id}, {self.__denumire}, {self.__pret}"

def test_domain():
    produs = Produs(1,'Cipsuri',5)
    assert produs.get_id() == 1
    assert produs.get_pret() == 5
    #assert produs.set_id(4) == 4