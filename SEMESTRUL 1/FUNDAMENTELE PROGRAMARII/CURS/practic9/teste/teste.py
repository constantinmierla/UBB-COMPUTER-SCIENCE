from domain.entities import *
from repository.repo import *
from service.serv import *
class Tests:

    @staticmethod
    def test_load_from_file():
        repotest = RepoJucator('testrepo.txt')
        lista = repotest.load_from_file()
        assert len(lista) == 2
        assert lista[0].get_nume() == 'oanea'

    @staticmethod
    def test_save_to_file():
        repotest = RepoJucator('testrepo.txt')
        lista = repotest.load_from_file()
        listanoua = [Jucator('mierla','constantin','190','Fundas')]

        repotest.save_to_file(listanoua)
        assert len(repotest.load_from_file()) == 1
        repotest.save_to_file(lista)

    @staticmethod
    def test_adauga_repo():
        repotest = RepoJucator('testrepo.txt')
        listaveche = repotest.load_from_file()
        repotest.adauga_repo(Jucator('costi','mihalache','150','Fundas'))
        lista = repotest.load_from_file()
        assert lista[2].get_nume() == 'costi'
        repotest.save_to_file(listaveche)
    @staticmethod
    def run():
        Tests.test_load_from_file()
        Tests.test_save_to_file()
        Tests.test_adauga_repo()