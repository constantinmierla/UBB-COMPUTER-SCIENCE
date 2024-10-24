from repository.repo import *
from service.serv import *
from ui.ui import *

cmd = Console(ServCarte(RepoCarte('carte.txt', [])))
cmd.run()
