class Melodie:
    def __init__(self, titlu, artist, gen, durata):
        self.__titlu = titlu
        self.__artist = artist
        self.__gen = gen
        self.__durata = durata

    def get_titlu(self):
        return self.__titlu
    def get_artist(self):
        return self.__artist
    def get_gen(self):
        return self.__gen
    def get_durata(self):
        return self.__durata

    def set_gen(self, value):
        self.__gen = value
    def set_durata(self, value):
        self.__durata = value

def test_creare_melodie():
    melodie = Melodie('titlu', 'artist', 'gen', 120)
    assert melodie.get_titlu() == 'titlu'
    assert melodie.get_artist() == 'artist'
    assert melodie.get_gen() == 'gen'
    assert melodie.get_durata() == 120
    melodie.set_gen('gen2')
    assert melodie.get_gen() == 'gen2'
    melodie.set_durata(100)
    assert melodie.get_durata() == 100

test_creare_melodie()