from domain.entities import Movie

class movieRepo:
    def __init__(self):
        self.__movies = {}

    def adauga_film(self, film):
        id_film = film.get_id()
        if id_film in self.__movies:
            raise Exception("Id existent\n")
        else:
            self.__movies[id_film] = film

    def sterge_film(self, id_film):
        if id_film in self.__movies:
            del self.__movies[id_film]
        else:
            raise Exception("Id inexistent\n")

    def modifica_film(self, id_film, nume_nou, gen_nou, desc_nou):
        if id_film in self.__movies:
            film = self.__movies[id_film]
            film.set_name(nume_nou)
            film.set_gen(gen_nou)
            film.set_desc(desc_nou)
        else:
            raise Exception("Id inexistent\n")

    def cauta_film(self, id_film):
        for film_id in self.__movies:
            film = self.__movies[film_id]
            if film.get_id() == id_film:
                return film
        return None


