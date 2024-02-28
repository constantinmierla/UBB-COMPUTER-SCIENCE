from Repository.film_file_repository import FilmFileRepository
from Repository.client_file_repository import ClientFileRepository
from Repository.rent_repository import RentRepository
from Service.film_service import FilmService
from Service.client_service import ClientService
from Service.rent_service import RentService
from UI.console import console


if __name__ == '__main__':
    repo=FilmFileRepository("film_file.txt")
    repo1=ClientFileRepository("client_file.txt")
    repo2=RentRepository()
    srv=FilmService(repo)
    srv1=ClientService(repo1)
    srv2=RentService(repo2)
    ui=console(srv,srv1,srv2)
    ui.run()

    repo.write_to_file("fisier_filme_nou.txt")
