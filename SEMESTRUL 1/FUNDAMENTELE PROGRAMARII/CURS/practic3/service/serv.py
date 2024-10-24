from repository.repo import RepoMelodie
from domain.entities import Melodie
import random
class ServMelodie:
    def __init__(self, repo):
        self.repo = repo

    def modifica_serv(self, titlu, artist, gen, durata):
        ok = 1
        if gen == 'Rock' or gen == 'Pop' or gen == 'Jazz' or gen == 'Altele':
            ok = 1
        else:
            print ("Eroare gen!")
            ok = 0
        if int(durata) < 0 or int(durata) != float(durata):
            print ("Eroare durata!")
            ok = 0

        if ok == 1:
            self.repo.modifica(titlu,artist,gen,durata)

    def export_serv(self, fisier):
       lista = self.repo.load_from_file()
       lista = sorted(lista, key = lambda x:(x.get_titlu(),x.get_artist()))
       with open(fisier, 'w') as f:
           for el in lista:
               string = el.get_titlu() + ',' + el.get_artist() + ',' + el.get_gen() + ',' + str(el.get_durata()) + '\n'
               f.write(string)
    def random_serv(self,numar,titluri,artisti):
        nr = int(numar)
        l3 = ['Pop', 'Jazz', 'Rock', 'Altele']
        ok = 1
        l1 = titluri.split(',')
        l2 = artisti.split(',')
        lista = self.repo.load_from_file()
        for i in range(nr):
            titlu = random.choice(l1)
            artist = random.choice(l2)
            durata = random.randint(90,250)
            gen = random.choice(l3)
            melodie = Melodie(titlu,artist,gen,durata)
            lista.append(melodie)

        self.repo.save_to_file(lista)
