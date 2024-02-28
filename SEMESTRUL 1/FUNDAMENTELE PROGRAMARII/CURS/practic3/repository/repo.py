from domain.entities import Melodie

class RepoMelodie:
    def __init__(self,filename):
        self.__filename = filename

    def load_from_file(self):
        lista = []
        with open(self.__filename, 'r') as f:
            lines = f.readlines()
            for line in lines:
                if line != '':
                    line = line.strip()
                    titlu,artist,gen,durata = line.split(',')
                    melodie = Melodie(titlu,artist,gen,durata)
                    lista.append(melodie)

        return lista

    def save_to_file(self, lista):
        with open(self.__filename, 'w') as f:
            for el in lista:
                string = el.get_titlu() + ','+ el.get_artist() + ',' + el.get_gen() + ','+ str(el.get_durata()) + '\n'
                f.write(string)

    def modifica(self,titlu,artist,gen,durata):
        lista = self.load_from_file()

        for el in lista:
            if el.get_titlu() == titlu and el.get_artist() == artist:
                el.set_gen(gen)
                el.set_durata(durata)

        self.save_to_file(lista)

def test_load_from_file():
    repo_test = RepoMelodie('testrepo.txt')
    lista = repo_test.load_from_file()
    assert len(lista) == 10
    assert lista[0].get_titlu() == 'titlu1'

def test_save_to_file():
    repo_test = RepoMelodie('testrepo.txt')
    lista_save = repo_test.load_from_file()
    lista = [Melodie('titlu','artist','gen',120)]
    repo_test.save_to_file(lista)
    assert len(repo_test.load_from_file()) == 1
    assert repo_test.load_from_file()[0].get_titlu() == 'titlu'

    repo_test.save_to_file(lista_save)

def test_modificare():
    repo_test = RepoMelodie('testrepo.txt')
    lista_save = repo_test.load_from_file()

    repo_test.modifica('titlu1', 'artist1', 'jazz', '999')
    lista = repo_test.load_from_file()
    assert lista[0].get_gen() == 'jazz'
    assert lista[0].get_durata() == '999'

    repo_test.save_to_file(lista_save)

test_load_from_file()
test_save_to_file()
test_modificare()