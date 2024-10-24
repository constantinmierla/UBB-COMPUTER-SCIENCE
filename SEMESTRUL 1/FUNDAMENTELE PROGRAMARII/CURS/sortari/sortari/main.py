import unittest


class Afisari:
    @staticmethod
    def afisare_lista(lista):
        for i in lista:
            print(i, end=' ')


class Cautari:
    @staticmethod
    def cautare_secventiala(lista, element_cautat) -> bool:
        """
        functia ce cauta variabila element in lista
        :param lista: lista in care se face cautarea
        :param element_cautat: elementul dupa care se face cautarea
        :return: True (daca elementul este in lista), False (in caz contrar)

        ------COMPLEXITATE------
        Best case: T(n) apartine O(1): elementul cautat este pe prima pozitie in lista
        Worst case: T(n) apartine O(n): elementul cautat este pe ultima pozitie in lista
        Avergae case: T(n) = (1 + 2 + ... + n) / n = n * (n + 1) / 2 * n = (n + 1) / 2 => T(n) apartine O(n)

        Auxiliary Space: O(1), nu se folosesc alte variabile pe parcursul cautarii
        """
        for element in lista:
            if element == element_cautat:
                return True

        return False

    @staticmethod
    def cautare_binara_iterativ(lista, element):
        stanga = 0
        dreapta = len(lista) - 1
        while stanga <= dreapta:
            mijloc = (stanga + dreapta) // 2

            if lista[mijloc] == element:
                return True

            if element < lista[mijloc]:
                dreapta = mijloc - 1
            elif element > lista[mijloc]:
                stanga = mijloc + 1

        return False

    @staticmethod
    def cautare_binara_revursiv(lista, element_cautat, stanga, dreapta) -> bool:
        """
        functie ce cauta variabila element_cautat in lista
        :param lista: o lista cu elemente CARE ESTE SORTATA
        :param element_cautat: elementul dupa care se face cautarea
        :param stanga: capatul din stanga a secventei din care se face cautarea
        :param dreapta: capatul din dreapta a secventei din care se face cautarea
        :return: True (daca elementul este in lista), False (in caz contrar)

        ------COMPLEXITATE---------
        T(n) = { teta(1), n = 1 | T(n/2) + teta(1) }
        Best case: T(n) apartine O(1): elementul cautat - se afla pe pozitita din mijloc a listei
                                                        - numarul de elemente al listei este
        Worst Case: T(n) apartine O(log n)
        Average case: T(n) apartine O(log n)

        !!!! functia este implementata recursiv, deci complexitatea spatiului auxiliar este O(log n)
        """
        if dreapta == stanga:
            return element_cautat == lista[dreapta]
        else:
            mijloc = (stanga + dreapta) // 2

            if element_cautat == lista[mijloc]:
                return True
            elif element_cautat <= lista[mijloc]:
                return Cautari.cautare_binara_revursiv(lista, element_cautat, stanga, mijloc - 1)
            else:
                return Cautari.cautare_binara_revursiv(lista, element_cautat, mijloc + 1, dreapta)


class TestareCautari(unittest.TestCase):
    def test_cautare_secventiala(self):
        lista = [4, 2, 5, 32, 6, 12, 9, 6, 23]
        self.assertEqual(Cautari.cautare_secventiala(lista, 0), False)
        self.assertEqual(Cautari.cautare_secventiala(lista, 4), True)
        self.assertEqual(Cautari.cautare_secventiala(lista, 23), True)
        self.assertEqual(Cautari.cautare_secventiala(lista, 12), True)

    def test_cautare_binara_revursiv(self):
        lista = [1, 2, 3, 4, 5, 6, 7, 8, 9]
        self.assertEqual(Cautari.cautare_binara_revursiv(lista, 5, 0, len(lista) - 1), True)
        self.assertEqual(Cautari.cautare_binara_revursiv(lista, 8, 0, len(lista) - 1), True)
        self.assertEqual(Cautari.cautare_binara_revursiv(lista, 1, 0, len(lista) - 1), True)
        self.assertEqual(Cautari.cautare_binara_revursiv(lista, 9, 0, len(lista) - 1), True)
        self.assertEqual(Cautari.cautare_binara_revursiv(lista, 0, 0, len(lista) - 1), False)
        self.assertEqual(Cautari.cautare_binara_revursiv(lista, 10, 0, len(lista) - 1), False)

    def test_cautare_binara_iterativ(self):
        lista = [1, 2, 3, 4, 5, 6, 7, 8, 9]
        self.assertEqual(Cautari.cautare_binara_iterativ(lista, 5), True)
        self.assertEqual(Cautari.cautare_binara_iterativ(lista, 8), True)
        self.assertEqual(Cautari.cautare_binara_iterativ(lista, 1), True)
        self.assertEqual(Cautari.cautare_binara_iterativ(lista, 9), True)
        self.assertEqual(Cautari.cautare_binara_iterativ(lista, 0), False)
        self.assertEqual(Cautari.cautare_binara_iterativ(lista, 10), False)


class Sortari:
    @staticmethod
    def selection_sort(lista):
        """
        functia sorteaza lista si o returneaza
        CUM?
        pentru fiecare parcurgere, gaseste elementul minim din lista si il pune pe pozitia corecta
        :param lista: lista ce urmeaza a fi sortata
        :return: lista sortata

        --------- COMPLEXITATE ------------------
        average case: O(n^2)
        worst case: O(n^2)
        best case: O(n^2)

        => complexitate: teta(n^2)

        ALGORTIM in-place
        """
        for i in range(0, len(lista) - 1):
            min_index = i

            # determinam minimul
            for j in range(i + 1, len(lista)):
                if lista[j] < lista[min_index]:
                    min_index = j

            # daca s a gasit un minim, il pun pe pozitia i
            if min_index > i:
                lista[i], lista[min_index] = lista[min_index], lista[i]

    @staticmethod
    def insertion_sort(lista):
        """
        sparg lista, virtual, in 2 subliste: prima sortata, a doua nesortata
        iau fiecare element din lista nesortata si il pun in pozitia lui corecta din lista sortata
        asa incat prima lista sa ramana sortata
        :param lista: lista ce urmeaza a fi sortata
        :return: None

        ------- COMPLEXITATE--------
        worst case: O(n^2)
        best case: O(n) -> lista este deja sortata
        average case: O(n^2)

        ALGORITM in-place
        """
        for i in range(1, len(lista)):
            element = lista[i]
            ind = i

            while ind > 0 and element < lista[ind - 1]:
                lista[ind] = lista[ind - 1]
                ind = ind - 1

            lista[ind] = element

    @staticmethod
    def bubble_sort(lista):
        """
        se interschimba elementele consecutive daca nu sunt in ordinea dorita
        se executa acest proces pana cand nu se mai executa interschimbari
        :param lista: lista ce urmeaza a fi sortata
        :return: None

        ------- COMPLEXITATE ----------
        worst case: teta(n^2)
        best case: teta(n) -> lista este deja sortata
        average case: teta(n^2)
        general complexity: O(n^2)

        ALGORITM in-place
        """
        sortat = False
        while not sortat:
            sortat = True
            for i in range(1, len(lista)):
                if lista[i - 1] > lista[i]:
                    lista[i - 1], lista[i] = lista[i], lista[i - 1]
                    sortat = False

    @staticmethod
    def partitie(lista, stanga, dreapta):
        pivot = lista[stanga]
        i = stanga
        j = dreapta
        while i != j:
            while lista[j] >= pivot and i < j:
                j = j - 1
            lista[i] = lista[j]

            while lista[i] <= pivot and i < j:
                i = i + 1
            lista[j] = lista[i]

        lista[i] = pivot
        return i

    @staticmethod
    def quicksort(lista, stanga, dreapta):
        pozitie = Sortari.partitie(lista, stanga, dreapta)

        # sortez partea stanga
        if stanga < pozitie - 1:
            Sortari.quicksort(lista, stanga, pozitie - 1)
        # sortez partea dreapta
        if dreapta > pozitie + 1:
            Sortari.quicksort(lista, pozitie + 1, dreapta)

    @staticmethod
    def merge(lista, stanga, mijloc, dreapta):
        n1 = mijloc - stanga + 1
        n2 = dreapta - mijloc

        l1 = lista[stanga:mijloc + 1]
        l2 = lista[mijloc + 1:dreapta + 1]

        index = stanga
        i = 0
        j = 0
        while i < n1 and j < n2:
            if l1[i] < l2[j]:
                lista[index] = l1[i]
                i = i + 1
            else:
                lista[index] = l2[j]
                j = j + 1
            index = index + 1

        while i < n1:
            lista[index] = l1[i]
            i = i + 1
            index = index + 1

        while j < n2:
            lista[index] = l2[j]
            j = j + 1
            index = index + 1

    @staticmethod
    def merge_sort(lista, stanga, dreapta):
        if stanga < dreapta:
            mijloc = (stanga + dreapta) // 2

            Sortari.merge_sort(lista, stanga, mijloc)
            Sortari.merge_sort(lista, mijloc + 1, dreapta)
            Sortari.merge(lista, stanga, mijloc, dreapta)


class MetodeDeProgramare:
    @staticmethod
    def max_di(lista, st, dr):
        """
        cauta maximul dintr o lista folosind divide et impera
        :param lista: lista in care se face cautarea
        :param st: pozitia de start
        :param dr: pozitia de final
        :return: maxim (int)
        """
        if st == dr:
            return lista[st]
        else:
            mij = (st + dr) // 2

            max1 = MetodeDeProgramare.max_di(lista, st, mij)
            max2 = MetodeDeProgramare.max_di(lista, mij + 1, dr)

            if max1 < max2:
                return max2
            else:
                return max1

    @staticmethod
    def pozitive_di(lista, st, dr):
        """
        calculeaza numarul de numere pozitive dintr o lista folosind divide et impera
        :param lista: lista in care se face cautarea
        :param st: pozitia de inceput a secventei in care se face cautarea
        :param dr: pozitia de final a secventei in care se face cautarea
        :return: numarul de numere pozitive
        """
        if st == dr:
            return lista[st] >= 0
        else:
            mij = (st + dr) // 2

            return MetodeDeProgramare.pozitive_di(lista, st, mij) + MetodeDeProgramare.pozitive_di(lista, mij + 1, dr)

    @staticmethod
    def par_di(lista, st, dr):
        """
        determina daca intr o lista se afla cel putin un numar par folosind divide et impera
        :param lista:
        :param st:
        :param dr:
        :return:
        """
        if st == dr:
            if lista[st] % 2 == 0:
                return True
            return False
        else:
            mij = (st + dr) // 2

            rs1 = MetodeDeProgramare.par_di(lista, st, mij)
            rs2 = MetodeDeProgramare.par_di(lista, mij + 1, dr)

            return rs1 or rs2

    @staticmethod
    def lista_inversa_di(lista, st, dr, lista_noua):
        if st == dr:
            lista_noua.append(lista[st])
        else:
            mij = (st + dr) // 2
            MetodeDeProgramare.lista_inversa_di(lista, mij + 1, dr, lista_noua)
            MetodeDeProgramare.lista_inversa_di(lista, st, mij, lista_noua)

    @staticmethod
    def produs_pozitii_pare_di(lista, st, dr):
        if st == dr:
            if st % 2 == 1:
                return lista[st]
            else:
                return 1
        else:
            mij = (st + dr) // 2
            p1 = MetodeDeProgramare.produs_pozitii_pare_di(lista, st, mij)
            p2 = MetodeDeProgramare.produs_pozitii_pare_di(lista, mij + 1, dr)

            return p1 * p2

    @staticmethod
    def lista_dublate_di(lista, st, dr, lista_noua):
        if st == dr:
            lista_noua.append(lista[st] * 2)
        else:
            mij = (st + dr) // 2
            MetodeDeProgramare.lista_dublate_di(lista, st, mij, lista_noua)
            MetodeDeProgramare.lista_dublate_di(lista, mij + 1, dr, lista_noua)

    @staticmethod
    def pare_sterse_di(lista, st, dr, lista_noua):
        if st == dr:
            if lista[st] % 2 == 1:
                lista_noua.append(lista[st])
        else:
            mij = (st + dr) // 2
            MetodeDeProgramare.pare_sterse_di(lista, st, mij, lista_noua)
            MetodeDeProgramare.pare_sterse_di(lista, mij + 1, dr, lista_noua)

    @staticmethod
    def cel_mai_lung_subsir_de_nr_pare(lista):
        """
        evident, aceasta problema se face folosind programarea dinamica
        :param lista:
        :return:
        """
        lista_noua = [0] * len(lista)
        lista_noua[len(lista) - 1] = 1
        pozitii = [0] * len(lista)
        pozitii[len(lista) - 1] = -1

        for i in range(len(lista) - 2, -1, -1):
            lista_noua[i] = 1
            pozitii[i] = -1

            for j in range(i + 1, len(lista)):
                if lista[i] >= lista[j] and lista_noua[i] < lista_noua[j] + 1:
                    lista_noua[i] = lista_noua[j] + 1
                    pozitii[j] = i

        j = 0
        for i in range(0, len(lista)):
            if lista_noua[i] > lista_noua[j]:
                j = i

        rez = []
        while j != -1:
            rez.append(lista[j])
            j = pozitii[j]

        print(rez)
