from validations import validare_client
from repository.repo_client import clientRepo
class ClientService:

    def __init__(self, repo_clienti, validator_clienti):
        self.__repo_clienti = repo_clienti
        self.__validator_clienti = validator_clienti

    def adauga_client(self, client):
        self.__validator_clienti.valideaza_client(client)
        self.__repo_clienti.adauga_client(client)

    def sterge_client(self, id):
        try:
            self.__repo_clienti.sterge_client(id)
            print("Stergere client cu succes!!!")
        except Exception as ex:
            print(f"a aparut o eroare:{ex}")
    def modifica_client(self,id, nume_nou, cnp_nou):
        try :
            self.__repo_clienti.modifica_client(id,nume_nou, cnp_nou)
            print("Modificare client reusita!!!")
        except Exception as ex:
            print (f"a aparut o eroare:{ex}")

    def cauta_client(self, id):
        return self.__repo_clienti.cauta_client(id)
