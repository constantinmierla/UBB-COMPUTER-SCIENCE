class MovieService:
    def __init__(self, repo_film, validator_film):
        self.__repo_film = repo_film
        self.__validator_film = validator_film
    def adauga_film(self, film):
        self.__validator_film.valideaza_film(film)
        self.__repo_film.adauga_film(film)

    def sterge_film(self, id):
        try:
            self.__repo_film.sterge_film(id)
            print("stergere film cu succes")
        except Exception as ex:
            print(f"eroare{ex}")

    def modifica_film(self, id, nume_nou, gen_nou, desc_nou):
        try:
            self.__repo_film.modifica_film(id,nume_nou, gen_nou, desc_nou)
            print("modificare film cu succes")
        except Exception as ex:
            print(f"eroare{ex}")

    def cauta_film(self, id):
        return self.__repo_film.cauta_film(id)
