from repository.repo import RepoProdus
from service.serv import ServProdus
from ui.ui import Console

cmd = Console(ServProdus(RepoProdus('magazin.txt')))
cmd.run()