from main import *


class Main:
    @staticmethod
    def main():
        lista = [2, 4, 5, 6, 6, 9, 12, 23, 32]
        print(Cautari.cautare_secventiala(lista, 23))
        print(Cautari.cautare_binara_iterativ(lista, 4))
        print(Cautari.cautare_binara_revursiv(lista, 12, 0, len(lista) - 1))
        print(Cautari.cautare_binara_iterativ(lista, 29))

        lista = [4, 2, 5, 32, 6, 12, 9, 6, 23]
        Sortari.selection_sort(lista)
        Afisari.afisare_lista(lista)

        print('\n')

        lista = [4, 2, 5, 32, 6, 12, 9, 6]
        Sortari.insertion_sort(lista)
        Afisari.afisare_lista(lista)

        print('\n')

        lista = [4, 2, 5, 0, 3, -2, 12, 45, 23, 12, 9, 8, 5, 2, 1, 4]
        Sortari.bubble_sort(lista)
        Afisari.afisare_lista(lista)

        print('\n')

        lista = [4, 2, 5, 0, 3, -2, 12, 45, 23, 12, 9, 8, 5, 2, 1, 4]
        Sortari.quicksort(lista, 0, len(lista) - 1)
        Afisari.afisare_lista(lista)

        print('acum:\n')
        lista = [5, 3, 1, 8, 9, 3, -1, 5, 23]
        print(lista)
        Sortari.merge_sort(lista, 0, len(lista) - 1)
        print(lista)

        lista = [4, 2, 5, 0, 3, -2, 12, 45, 23, 12, 9, 8, 5, 2, 1, 4]
        print(MetodeDeProgramare.max_di(lista, 0, len(lista) - 1))

        lista = [4, -2, -5, 0, 3, -2, 12, -45, -23, 12, -9, 8, 5, -2, -1, -4, 0, 9, -3]
        print(MetodeDeProgramare.pozitive_di(lista, 0, len(lista) - 1))

        lista = [4, -2, -5, 0, 3, -2, 12, -45, -23, 12, -9, 8, 5, -2, -1, -4, 0, 9, -3]
        print(MetodeDeProgramare.par_di(lista, 0, len(lista) - 1))

        lista = [1, 3, 5, 7, 9]
        print(MetodeDeProgramare.par_di(lista, 0, len(lista) - 1))

        lista = [1, 3, 4, 5, 6, 2, 8]
        lista_noua = []
        MetodeDeProgramare.lista_inversa_di(lista, 0, len(lista) - 1, lista_noua)
        Afisari.afisare_lista(lista_noua)

        print('\n')
        lista = [1, 2, 3, 5, 6, 1, 2, 2, 3]
        print(MetodeDeProgramare.produs_pozitii_pare_di(lista, 0, len(lista) - 1))

        lista = [1, 3, 4, 5, 6, 2, 8]
        lista_noua = []
        MetodeDeProgramare.lista_dublate_di(lista, 0, len(lista) - 1, lista_noua)
        Afisari.afisare_lista(lista_noua)

        print('\n')
        lista = [1, 3, 4, 3, 2, 5, 6, 2, 8]
        lista_noua = []
        MetodeDeProgramare.pare_sterse_di(lista, 0, len(lista) - 1, lista_noua)
        Afisari.afisare_lista(lista_noua)

        print('\n')
        lista = [1, 2, 2, 3, 4, 6, 3, 5, 6]
        print(MetodeDeProgramare.cel_mai_lung_subsir_de_nr_pare(lista))


Main.main()
