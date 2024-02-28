from domain.entities import Client

def citeste_numar(prompt, f, msg):
    while True:
        try:
            return f(input(prompt))
        except ValueError:
            print(msg)

class UI:
    def __init__(self, movie_service, client_service):
        self.__movie_service = movie_service
        self.__client_service = client_service

    def adauga_film_ui(self):
        id_film = citeste_numar("Introduceti id ul filmului : ", int, "id invalid")
        titlu = input("Introduceti titlul filmului : ")
        gen = input("Introduceti genul fimului : ")
        desc = input("Introduceti descrierea filmului : ")
        try :
            self.movie_service.adauga_film(id_film, titlu, gen, desc)
        except Exception as ex:
            print (f"Eroare adaugare film{ex}")
