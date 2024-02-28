class Jucator:
    def __init__(self, nume, prenume, inaltime, post):
        self.__nume = nume
        self.__prenume = prenume
        self.__inaltime = inaltime
        self.__post = post

    def get_nume(self):
        """
        getter nume

        :return:
        """
        return self.__nume
    def get_prenume(self):
        """

        :return:
        """
        return self.__prenume
    def get_inaltime(self):
        """

        :return: inaltime
        """
        return self.__inaltime
    def get_post(self):
        return self.__post
    def set_post(self, value):
        self.__post = value

    def set_nume(self, value):
        """
        :param value: str
        :return:
        """
        self.__nume = value

    def set_prenume(self, value):
        """
        :param value: str
        :return:
        """
        self.__prenume = value
    def set_inaltime(self, value):
        """

        :param value: string
        :return:
        """
        self.__inaltime = value

    def __str__(self):
        """
        :return:
        """
        return f"{self.__nume},{self.__prenume},{self.__inaltime},{self.__post}"
