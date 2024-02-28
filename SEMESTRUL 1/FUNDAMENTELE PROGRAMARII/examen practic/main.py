from domain.entities import *
from repository.repo import *
from service.serv import *
from ui.ui import *

cmd = Console(ServTractor(RepoTractor('tractor.txt'),[]),'','-1',[])
cmd.run()
