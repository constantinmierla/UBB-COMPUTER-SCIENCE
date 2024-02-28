from Service.film_service import FilmService
from Service.client_service import ClientService
from Repository.film_repository import FilmRepository
from Domain.domain import films, clients


class console:
    def __init__(self, srv, srv1, srv2):
        self.__srv = srv
        self.__srv1 = srv1
        self.__srv2 = srv2

    # films
    def add_film_ui(self):
        """
        Adauga film citit de la tastatura
        """
        id = int(input("ID-ul:"))
        title = input("Titlul:")
        description = input("Descrierea:")
        genre = input("Genul:")
        try:
            self.__srv.verify_existent_id_srv(id)
            self.__srv.add_film_srv(id, title, description, genre)
            print("Film adaugat cu succes")
        except ValueError as ve:
            print(ve)
        except KeyError as ke:
            print(ke)


    def add_random_film_ui(self):
        """
        Genereaza filme random
        """
        id = int(input("Dati id-ul filmului cu care doriti sa incepeti:"))
        self.__srv.verify_existent_id_srv(id)
        size = int(input("Dati numarul de filme random care vor fi generate:"))
        self.__srv.add_random_film_srv(id, size)

    def delete_film_ui(self):
        """
        Sterge un film dupa id
        """
        try:
            id = int(input("Dati id-ul filmului pe care doriti sa il stergeti:"))
            self.__srv.verify_not_existent_id_srv(id)
            self.__srv.delete_film_srv(id)
            print("Filmul sters cu succes")
        except ValueError as ve:
            print(ve)

    def modify_film_ui(self):
        """
        Modificam un film dupa id
        """
        try:
            id = int(input("Dati id-ul filmului pe care doriti sa o modificati:"))
            self.__srv.verify_not_existent_id_srv(id)
            new_title = input("Titlu nou:")
            new_description = input("Descriere noua:")
            new_genre = input("Gen nou:")
            self.__srv.modify_film_srv(id, new_title, new_description, new_genre)
            print("Film modificat cu succes")
        except ValueError as ve:
            print(ve)

    def find_film_ui(self):
        """
        Cauta un film dupa id si il afiseaza
        """
        try:
            id = int(input("Dati id-ul filmului cautat:"))
            self.__srv.verify_not_existent_id_srv(id)
            print(self.__srv.find_film_srv(id))
        except ValueError as ve:
            print(ve)

    def get_all_films_ui(self):
        """
        Tipareste lista cu filme
        """
        try:
            film_list = self.__srv.get_all_films_srv()
            if film_list == []:
                raise ValueError("Nu au fost adaugate filme")
            print("Lista filmelor este:")
            for fl in film_list:
                print(fl)
        except ValueError as ve:
            print(ve)

    # clients
    def add_client_ui(self):
        """
        Adauga client citit de la tastatura
        """
        try:
            id = int(input("ID-ul:"))
            name = input("Nume:")
            cnp = input("CNP:")
            self.__srv1.verify_existent_id_srv(id)
            if self.__srv1.add_client_srv(id, name, cnp):
                print("Client adaugat cu succes")
            else:
                print("Date invalide pentru client. Verificati numele sau CNP-ul.")
        except ValueError as ve:
            print(ve)
        except KeyError as ke:
            print(ke)

    def delete_client_ui(self):
        """
        Sterge client dupa id
        """
        try:
            id = int(input("Dati id-ul clientului pe care doriti sa il stergeti:"))
            self.__srv1.verify_not_existent_id_srv(id)
            self.__srv1.delete_client_srv(id)
            print("Client sters cu succes")
        except ValueError as ve:
            print(ve)

    def modify_client_ui(self):
        """
        Modifica client dupa id
        """
        try:
            id = int(input("Dati id-ul clientului pe care doriti sa il modificati:"))
            self.__srv1.verify_not_existent_id_srv(id)
            new_name = input("Nume nou:")
            new_cnp = input("CNP nou:")
            self.__srv1.modify_client_srv(id, new_name, new_cnp)
            print("Client modificat cu succes")
        except ValueError as ve:
            print(ve)

    def find_client_ui(self):
        """
        Cauta un client dupa id si il afiseaza
        """
        try:
            id = int(input("Dati id-ul clientului cautat:"))
            self.__srv1.verify_not_existent_id_srv(id)
            print(self.__srv1.find_client_srv(id))
        except ValueError as ve:
            print(ve)

    def get_all_clients_ui(self):
        """
        Tipareste lista cu clientii
        """
        try:
            client_list = self.__srv1.get_all_clients_srv()
            if client_list == []:
                raise ValueError("Nu au fost adaugati clienti")
            print("Lista clientilor este:")
            for cl in client_list:
                print(cl)
        except ValueError as ve:
            print(ve)

    # inchireiere
    def rent_ui(self):
        """
        Se implementeaza interfata pentru inchiriere filme
        """
        try:
            id_client = int(input("Dati id-ul clientului:"))
            self.__srv1.verify_not_existent_id_srv(id_client)
            cl = self.__srv1.find_client_srv(id_client)
            print(f"Bun venit, {cl.get_name()}")
            print("Aceasta e lista cu filme disponibile:")
            for fl in self.__srv.get_all_films_srv():
                print(fl)
            id_film = int(input("Alegeti filmul dupa id:"))
            self.__srv.verify_not_existent_id_srv(id_film)
            fl = self.__srv.find_film_srv(id_film)
            self.__srv2.add_rented_film_srv(id_film, id_client)
            print("Film inchiriat cu succes")
        except ValueError as ve:
            print(ve)

    def return_ui(self):
        """
        Se implementeaza interfata pentru returnare film
        """
        try:
            id_client = int(input("Dati id-ul clientului:"))
            self.__srv1.verify_not_existent_id_srv(id_client)
            cl = self.__srv1.find_client_srv(id_client)
            if len(self.__srv2.rented_films_by_client_srv(id_client)) == 0:
                raise ValueError("Clientul nu are niciun film inchiriat")
            print(f"Bun venit, {cl.get_name()}")
            if len(self.__srv2.rented_films_by_client_srv(id_client)) == 1:
                print("Acesta este filmul inchiriat de dvs:")
            else:
                print("Acestea sunt filmele inchiriate de dvs:")
            film_list = self.__srv2.rented_films_by_client_srv(id_client)
            for index in film_list:
                fl = self.__srv.find_film_srv(index)
                print(fl)
            id_film = int(input("Alegeti filmul pe care doriti sa il returnati:"))
            self.__srv.verify_not_existent_id_srv(id_film)
            self.__srv2.return_film_srv(id_film, id_client)
            print("Film returnat cu succes")
        except ValueError as ve:
            print(ve)

    # rapoarte
    def report_top_films(self):
        """
        Returneaza cele mai inchiriate filme
        """
        try:
            sorted_list = []
            freq = self.__srv2.rented_films_frequency_srv()
            for index in range(len(freq)):
                if freq[index] > 0:
                    fl = self.__srv.find_film_srv(index)
                    sorted_list.append([fl.get_title(), freq[index]])
            sorted_list = sorted(sorted_list, key=lambda x: x[-1], reverse=True)
            if sorted_list == []:
                raise ValueError("Nu a fost inregistrata nicio inchiriere")
            print("Raportul este :")
            for item in sorted_list:
                if item[1] == 1:
                    print(f"{item[0]} cu o inchiriere")
                else:
                    print(f"{item[0]} cu {item[1]} inchirieri")
        except ValueError as ve:
            print(ve)

    def report_clients(self, option):
        """
        Afiseaza clienti care au filme inchiriate in ordine alfabetica
        """
        try:
            sorted_list = []
            freq = self.__srv2.clients_frequency_srv()
            for index in range(len(freq)):
                if freq[index] > 0:
                    cl = self.__srv1.find_client_srv(index)
                    sorted_list.append([cl.get_name(), freq[index]])
            sorted_list = sorted(sorted_list, key=lambda x: x[option])
            if sorted_list == []:
                raise ValueError("Nu a fost inregistrata nicio inchiriere")
            print("Raportul este:")
            for item in sorted_list:
                if item[1] == 1:
                    print(f"{item[0]} cu un film inchiriat")
                else:
                    print(f"{item[0]} cu {item[1]} filme inchiriate")
        except ValueError as ve:
            print(ve)

    def report_30_active_clients(self):
        """
        Afiseaza primii 30% cei mai activi clienti
        """
        try:
            sorted_list = []
            freq = self.__srv2.clients_frequency_srv()
            for index in range(len(freq)):
                if freq[index] > 0:
                    cl = self.__srv1.find_client_srv(index)
                    sorted_list.append([cl.get_name(), freq[index]])
            sorted_list = sorted(sorted_list, key=lambda x: x[1], reverse=True)
            client_range = round(0.3 * len(sorted_list))
            if client_range < 1:
                client_range = 1
            if sorted_list == []:
                raise ValueError("Nu a fost inregistrata nicio inchiriere")
            print("Cei top 30% clienti activi sunt:")
            for index in range(client_range):
                if sorted_list[1] == 1:
                    print(f"{sorted_list[index][0]} cu un film inchiriat")
                else:
                    print(f"{sorted_list[index][0]} cu {sorted_list[index][1]} filme inchiriate")
        except ValueError as ve:
            print(ve)

    def print_interface(self):
        """
        Tipareste meniul cu optiuni
        """
        print('\n')
        print("""
        1) Adaugare
        2) Stergere
        3) Modificare
        4) Cautare
        5) Inchiriere/returnare
        6) Raport
        7) Afisare
        8) Generare filme random
        0) Exit
        """)

    def run(self):
        """
        Meniul care interactioneaza cu utilizatorul si
        apeleaza functiile dorite
        """
        while True:
            self.print_interface()
            option = int(input("Alegeti optiunea:"))
            if option == 1:
                print('\n')
                print("1) Adaugare film")
                print("2) Adaugare client")
                print("0) Exit")
                option = int(input("Alegeti optiunea:"))
                print('\n')
                if option == 1:
                    self.add_film_ui()
                elif option == 2:
                    self.add_client_ui()
                elif option == 0:
                    pass
                else:
                    raise ValueError("Comanda invalida")
                    pass
            elif option == 2:
                print('\n')
                print("1) Stergere film")
                print("2) Stergere client")
                print("0) Exit")
                option = int(input("Alegeti optiunea:"))
                print('\n')
                if option == 1:
                    self.delete_film_ui()
                elif option == 2:
                    self.delete_client_ui()
                elif option == 0:
                    pass
                else:
                    raise ValueError("Comanda invalida")
                    pass
            elif option == 3:
                print('\n')
                print("1) Modifica film")
                print("2) Modifica client")
                print("0) Exit")
                option = int(input("Alegeti optiunea:"))
                print('\n')
                if option == 1:
                    self.modify_film_ui()
                elif option == 2:
                    self.modify_client_ui()
                elif option == 0:
                    pass
                else:
                    raise ValueError("Comanda invalida")
                    pass
            elif option == 4:
                print('\n')
                print("1) Cautare film")
                print("2) Cautare client")
                print("0) Exit")
                option = int(input("Alegeti optiunea:"))
                print('\n')
                if option == 1:
                    self.find_film_ui()
                elif option == 2:
                    self.find_client_ui()
                elif option == 0:
                    pass
                else:
                    raise ValueError("Comanda invalida")
                    pass
            elif option == 5:
                print('\n')
                print("1) Inchiriere film")
                print("2) Returnare film")
                print("0) Exit")
                option = int(input("Alegeti optiunea:"))
                print('\n')
                if option == 1:
                    self.rent_ui()
                elif option == 2:
                    self.return_ui()
                elif option == 0:
                    pass
                else:
                    raise ValueError("Comanda invalida")
                    pass
            elif option == 6:
                print('\n')
                print("1) Raport cele mai inchiriate filme")
                print("2) Raport clienti cu filme inchiriate ordonat dupa nume")
                print("3) Raport clienti cu filme inchiriate ordonat dupa numarul de inchirieri")
                print("4) Raport cu primii 30% cei mai activi clienti")
                print("0) Exit")
                option = int(input("Alegeti optiunea:"))
                print('\n')
                if option == 1:
                    self.report_top_films()
                elif option == 2:
                    self.report_clients(0)
                elif option == 3:
                    self.report_clients(1)
                elif option == 4:
                    self.report_30_active_clients()
                elif option == 0:
                    pass
                else:
                    raise ValueError("Comanda invalida")
                    pass
            elif option == 7:
                print('\n')
                print("1) Lista filme")
                print("2) Lista clienti")
                print("0) Exit")
                option = int(input("Alegeti optiunea:"))
                print('\n')
                if option == 1:
                    self.get_all_films_ui()
                elif option == 2:
                    self.get_all_clients_ui()
                elif option == 0:
                    pass
                else:
                    raise ValueError("Comanda invalida")
                    pass
            elif option == 8:
                self.add_random_film_ui()
            elif option == 0:
                break
            else:
                print("Comanda invalida, incercati din nou")