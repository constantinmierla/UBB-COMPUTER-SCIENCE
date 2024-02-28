class Tractor:
    def __init__(self,id,denumire,pret,model,data):
        """
        Constructor
        :param id: id tractor, type str
        :param denumire: denumire tractor, type str
        :param pret: denumire pret, type str
        :param model: denumire model, type str
        :param data: denumire data, type str
        """
        self.__id = id
        self.__denumire = denumire
        self.__pret = pret
        self.__model = model
        self.__data = data

    def get_id(self):
        """
        Obtine id
        :return: tractor, type str
        """
        return self.__id

    def get_denumire(self):
        """
        Obtine denumire
        :return: tractor, type str
        """
        return self.__denumire

    def get_pret(self):
        """
        Obtine pret
        :return: pret, type str
        """
        return self.__pret

    def get_model(self):
        """
        Obtine model
        :return: model, type str
        """
        return self.__model

    def get_data(self):
        """
        Obtine data
        :return: data, type str
        """
        return self.__data

    def __str__(self):
        """
        functie care afiseaza formatul corect pentru obiect
        :return: obiect, type str
        """
        return f'{self.__id};{self.__denumire};{self.__pret};{self.__model};{self.__data}'

def test_domain():
    tractor = Tractor('1','john deere','9000','3650dt','21.03.2020')
    assert tractor.get_id() == '1'
    assert tractor.get_denumire() == 'john deere'
    assert tractor.get_model() == '3650dt'
    assert tractor.get_data() == '21.03.2020'
test_domain()