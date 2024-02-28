from REPOSITORY.storage import Repo, RepoFile
from BUSINESS.service import Service
from UI.ui_elements import Output, Input


class Main:
    @staticmethod
    def run_all_tests():
        pass

    @staticmethod
    def run_main():
        lista_biciclete = Repo()
        fisier = RepoFile('fisier.txt')

        while True:
            # load data from file
            lista_biciclete.load_from_file(fisier)

            Output.menu()
            command = Input.command_input(3)

            if command == 1:
                # scurta afisare
                Service.print_all_biciclete(lista_biciclete)
                # stergere dupa un anumit tip
                # citesc tipul
                tip = Input.correct_type_input(lista_biciclete, 'Introdu tipul bicicletei dupa care se face stergerea:')
                # fac stergerea
                Service.sterge_el_by_tip(lista_biciclete, tip)

            elif command == 2:
                # stergere elemente cu pret maxim
                Service.stergere_pret_maxim(lista_biciclete)

            elif command == 3:
                exit()

            # actualizez fisierul
            lista_biciclete.write_in_file(fisier)


if __name__ == '__main__':
    Main.run_main()
