class Piesa:
    def __init__(self, titlu, regizor, gen, durata):
        self.__titlu = titlu
        self.__regizor = regizor
        self.__gen = gen
        self.__durata = durata

    def get_titlu(self):
        return self.__titlu
    def set_titlu(self, titlu):
        self.__titlu = titlu
    def get_regizor(self):
        return self.__regizor
    def set_regizor(self, value):
        self.__regizor = value
    def get_gen(self):
        return self.__gen
    def set_gen(self, value):
        self.__gen = value
    def get_durata(self):
        return self.__durata
    def set_durata(self, value):
        self.__durata = value
    def __str__(self):
        return f"{self.__titlu, self.__regizor, self.__gen, self.__durata}"
    