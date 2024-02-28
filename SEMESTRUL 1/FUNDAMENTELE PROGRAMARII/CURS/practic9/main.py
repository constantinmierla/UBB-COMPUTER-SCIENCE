from repository.repo import *
from service.serv import *
from ui.ui import *
from teste.teste import Tests
Tests.run()
cmd = Console(ServJucator(RepoJucator('jucator.txt')))
cmd.run()