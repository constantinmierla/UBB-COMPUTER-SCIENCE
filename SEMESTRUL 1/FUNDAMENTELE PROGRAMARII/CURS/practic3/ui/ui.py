from service.serv import ServMelodie

class Console:
    def __init__(self, serv):
        self.serv = serv

    def modifica_ui(self):
        titlu = input('Alegeti titlul: ')
        artist = input('Alegeti artistul: ')
        gen = input('Alegeti genul: ')
        durata = input('Alegeti durata: ')
        self.serv.modifica_serv(titlu,artist,gen,durata)
    def export_ui(self):
        nume = input('introduceti numele fisierului: ')
        self.serv.export_serv(nume)
    def random_ui(self):
        numar = input('introduceti numarul de melodii: ')
        titluri = input('introduceti titlurile: ')
        artisti = input('introduceti artistii: ')
        self.serv.random_serv(numar,titluri,artisti)
    def run(self):
        while True:
            cmd = input('alegeti: modificare, creeaza, exporta, stop: ')
            if cmd == 'modificare':
                self.modifica_ui()
            elif cmd == 'creeaza':
                self.random_ui()
            elif cmd == 'exporta':
                self.export_ui()
            elif cmd == 'stop':
                exit()
            else:
                print("Comanda invalida!")
