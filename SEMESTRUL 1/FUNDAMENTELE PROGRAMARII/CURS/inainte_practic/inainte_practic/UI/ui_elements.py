class Output:
    @staticmethod
    def print_message(mesaj):
        print(mesaj)

    @staticmethod
    def menu():
        print('1. Sterge tip')
        print('2. Sterge max')
        print('3. Exit')


class Input:
    @staticmethod
    def command_input(nr_max_inputs):
        while True:
            try:
                inp = int(input('Introdu o comanda: '))

                if 0 < inp <= nr_max_inputs:
                    return inp
                # in caz ca nu s a introdus un numar in intervalul cerut, afisam mesaj de eroare
                Output.print_message('Introdu o valoare corecta!')

            except ValueError:
                Output.print_message('Introdu o valoare corecta!')

    @staticmethod
    def correct_type_input(lista, mesaj):
        while True:
            tip = input(mesaj)

            nr = lista.get_numar()
            for i in range(0, nr):
                el = lista.get_element_from_position(i)

                if el.get_tip() == tip:
                    return tip
