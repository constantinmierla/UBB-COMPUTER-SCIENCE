from ui.ui import *
from service.serv import *
from repository.repo import *

ui = Console(ServPiesa(RepoPiesa('fisier.txt')))
ui.start()