from domain.entities import *
from repository.repo import *
from service.serv import *
from ui.ui import *
if __name__ == '__main__':
    consola = Console(ServMelodie(RepoMelodie('fisier.txt')))
    consola.run()
