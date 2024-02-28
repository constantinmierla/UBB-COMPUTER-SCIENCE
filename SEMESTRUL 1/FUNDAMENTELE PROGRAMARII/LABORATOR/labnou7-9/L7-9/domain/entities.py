class Movie:

    def __init__(self, id, title, desc, gen):
        #constructorul clasei

        self.__id = id
        self.__title = title
        self.__desc = desc
        self.__gen = gen

    def get_id(self):
        return self.__id

    def get_title(self):
        return self.__titlu

    def get_desc(self):
        return self.__desc

    def get_gen(self):
        return self.__gen

    def set_title(self, value):
        self.__titlu = value

    def set_desc(self, value):
        self.__desc = value

    def set_gen(self, value):
        self.__gen = value

    def __eq__(self, other):
        return self.__id == other.__id

    def __str__(self):
        return f"[{self.__id}]{self.__titlu}:{self.__gen} - {self.desc}"


class Client:

    def __init__(self, id, name, cnp):
        self.__id = id
        self.__name = name
        self.__cnp = cnp

    def get_id(self):
        return self.__id

    def get_name(self):
        return self.__name

    def get_cnp(self):
        return self.__cnp

    def set_name(self, value):
        self.__name = value

    def set_cnp(self, value):
        self.__cnp = value

    def __eq__(self, other):
        return self.__id == other.__id

    def __str__(self):
        return f"[{self.__id}]{self.__name}:{self.__cnp}"

