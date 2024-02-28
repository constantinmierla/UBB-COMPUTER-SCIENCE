class Bicicleta:
    def __init__(self, id_bicicleta, tip, pret):
        self.__id_bicicleta = id_bicicleta
        self.__tip = tip
        self.__pret = pret

    def get_id(self):
        return self.__id_bicicleta

    def get_tip(self):
        return self.__tip

    def get_pret(self):
        return self.__pret

    def set_id(self, id_nou):
        self.__id_bicicleta = id_nou

    def set_tip(self, tip_nou):
        self.__tip = tip_nou

    def set_pret(self, pret_nou):
        self.__pret = pret_nou