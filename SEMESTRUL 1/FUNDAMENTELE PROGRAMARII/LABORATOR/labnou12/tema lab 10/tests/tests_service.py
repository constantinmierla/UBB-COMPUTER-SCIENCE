from Service.film_service import FilmService
from Service.client_service import ClientService
from Service.rent_service import RentService
from Repository.film_file_repository import FilmFileRepository
from Repository.client_file_repository import ClientFileRepository
from Repository.rent_repository import RentRepository


def test_add_film_service():
    repo = FilmFileRepository("test_films.txt")
    repo.clear()
    service = FilmService(repo)

    assert service.get_all_films_srv() == []

    service.add_film_srv(1, "Harry Potter", "vrajitori", "Actiune")
    assert len(service.get_all_films_srv()) == 1


def test_modify_film_service():
    repo = FilmFileRepository("test_films.txt")
    repo.clear()
    service = FilmService(repo)

    service.add_film_srv(1, "Harry Potter", "vrajitori", "Actiune")

    service.modify_film_srv(1, "Harry Potter 2", "mai multi vrajitori", "Actiune")
    modified_film = service.find_film_srv(1)

    assert modified_film.get_title() == "Harry Potter 2"
    assert modified_film.get_description() == "mai multi vrajitori"


def test_add_client_service():
    repo = ClientFileRepository("test_clients.txt")
    repo.clear()
    service = ClientService(repo)

    assert service.get_all_clients_srv() == []

    service.add_client_srv(1, "Costi", "5040528330000")
    assert len(service.get_all_clients_srv()) == 1


def test_rent_and_return_service():
    film_repo = FilmFileRepository("test_films.txt")
    client_repo = ClientFileRepository("test_clients.txt")
    rent_repo = RentRepository()

    film_repo.clear()
    client_repo.clear()

    film_service = FilmService(film_repo)
    client_service = ClientService(client_repo)
    rent_service = RentService(rent_repo, film_service, client_service)

    film_service.add_film_srv(1, "Harry Potter", "vrajitori", "Actiune")
    client_service.add_client_srv(1, "Costi", "5040528330000")


    rented_films = rent_service.rented_films_by_client_srv(1)
    assert len(rented_films) == 1

    rent_service.return_film_srv(1, 1)

    rented_films_after_return = rent_service.rented_films_by_client_srv(1)
    assert len(rented_films_after_return) == 0
