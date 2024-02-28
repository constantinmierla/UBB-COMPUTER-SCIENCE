class Validareclient:
    def valideaza_client(self, client):
        erori = ""
        if client.get_id() < 0:
            erori += "id client invalid\n"
        if client.get_name() == "":
            erori += "nume client invalid\n"
        if client.get_cnp() <= 999999999 or client.get_cnp() > 9999999999:
            erori += "cnp client invalid\n"

        if len(erori) > 0:
            raise Exception(erori)