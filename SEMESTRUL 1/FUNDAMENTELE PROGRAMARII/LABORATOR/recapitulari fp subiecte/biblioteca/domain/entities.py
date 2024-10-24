class Carte:

    def __init__(self, id, titlu, autor, an):
        self.__id = id
        self.__titlu = titlu
        self.__autor = autor
        self.__an = an

    def get_id(self):
        return self.__id
    def get_titlu(self):
        return self.__titlu
    def get_autor(self):
        return self.__autor
    def get_an(self):
        return self.__an

    def set_id(self, id):
        self.__id = id

    def set_titlu(self, titlu):
        self.__titlu = titlu

    def set_autor(self, autor):
        self.__autor = autor

    def set_an(self, an):
        self.__an = an
