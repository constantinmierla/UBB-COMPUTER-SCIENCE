from domain.entities import Client

class clientRepo:
    def __init__(self):
        self.__clienti = {}

    def adauga_client(self, client):

        id_client = Client.get_id()
        if id_client in self.__clienti:
            raise Exception("Id existent\n")
        self.__clienti[id_client] = client

    def sterge_client(self, id_client):
        if id_client in self.__clienti:
            del self.__clienti[id_client]
        else:
            raise Exception("Id inexistent\n")

    def modifica_client(self, id_client, nume_nou, cnp_nou):
        if id_client in self.__clienti:
            client = self.__clienti[id_client]
            client.set_name(nume_nou)
            client.set_cnp(cnp_nou)
        else:
            raise Exception("Id inexistent\n")

    def cauta_client(self, id_client):
        for client_id in self.__clienti:
            client = self.__clienti[client_id]
            if client.get_id() == id_client:
                return client
        return None

