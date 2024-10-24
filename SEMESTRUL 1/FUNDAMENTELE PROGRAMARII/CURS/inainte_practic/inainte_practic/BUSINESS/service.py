class Service:
    @staticmethod
    def print_bicicleta(el):
        print(el.get_id(), end=" ")
        print(el.get_tip(), end=" ")
        print(el.get_pret())

    @staticmethod
    def print_all_biciclete(lista_biciclete):
        nr_el = lista_biciclete.get_numar()

        print('Id   |   Tip   |   Pret')

        for i in range(0, nr_el):
            el = lista_biciclete.get_element_from_position(i)

            Service.print_bicicleta(el)

    @staticmethod
    def sterge_el_by_tip(lista, tip):
        lista_noua = []
        for i in range(0, lista.get_numar()):
            el = lista.get_element_from_position(i)

            if el.get_tip() != tip:
                lista_noua.append(el)

        lista.copiere_lista_noua(lista_noua)

    @staticmethod
    def stergere_pret_maxim(lista):
        # determin pretul maxim
        pret_max = 0
        for i in range(0, lista.get_numar()):
            el = lista.get_element_from_position(i)

            if el.get_pret() > pret_max:
                pret_max = el.get_pret()

        lista_noua = []
        for i in range(0, lista.get_numar()):
            el = lista.get_element_from_position(i)

            if el.get_pret() != pret_max:
                lista_noua.append(el)

        lista.copiere_lista_noua(lista_noua)
