from Domain.domain import films, clients,Rent
from Repository.film_repository import FilmRepository
from Repository.client_repository import ClientRepository


class RentRepository:
    def __init__(self):
        """
        Se initializeaza lista unde se vor stoca filmele inchiriate
        """
        self.__rent_list = []


    def rented_films_by_client_repo(self, id):
        """
        Returneaza o lista cu id-ul filmelor inchiriate de un client
        """
        rented_films = []
        for item in self.__rent_list:
            if item[1] == id:
                rented_films.append(item[0])
        return rented_films

    def add_rented_film_repo(self, id_film, id_client):
        """
        Se adauga in lista filmelor inchiriate id-ul filmului si al clientului

        """
        self.__rent_list.append([id_film, id_client])

    def return_film_repo(self, id_film, id_client):
        """
        Elimina o carte returnata din lista cartilor inchiriate

        """
        ok = 1
        index = 0
        for item in self.__rent_list:
            if item[0] == id_film and item[1] == id_client:
                self.__rent_list.pop(index)
                ok = 0
                break
            index += 1
        if ok:
            raise ValueError("Inchirierea nu a fost inregistrata")

    def size(self):
        """
        Returneaza lungimea listei
        """
        return len(self.__rent_list)

    def rented_films_frequency_repo(self):
        """
        Returneaza o lista cu numarul de inchirieri a filmelor
        """
        freq_list = [0] * 100
        for item in self.__rent_list:
            freq_list[item[0]] += 1
        return freq_list

    def clients_frequency_repo(self):
        """
        Returneaza o lista cu numarul filmelor inchiriate de fiecare client
        """
        freq_list = [0] * 100
        for item in self.__rent_list:
            freq_list[item[1]] += 1
        return freq_list
