"""
created by Mierla Constantin
20 october 2023
"""

def meniu():
    print("1. Citirea unei liste de numere intregi")
    print("2. Se cauta secventa de lungime maximă cu proprietatea: Contine cel mult trei valori distincte")
    print("3. Se cauta secventa de lungime maximă: Oricare doua elemente consecutive difera printr-un numar prim")
    print("4. Se cauta secventa de lungime maximă cu proprietatea: x[i] < x[i+1] < ... < x[i+p]")
    print("5. Iesire din aplicatie")


def citeste(lista, nr_elemente_lista):
    v = []
    print("Introduceti elementele (apasati enter dupa fiecare element)")
    for i in range(0, nr_elemente_lista):
        x = int(input())
        v.append(x)
    lista[:] = v


#Contine cel mult trei valori distincte
def distincte(lista):
    start = 0
    final = 0
    lungime_maxima = 0
    max_range_start = 0
    max_range_end = 0
    distinct = 0

    while final < len(lista):
        if lista[final] != lista[start]:
            distinct += 1

        while distinct > 2:
            if lista[start] != lista[start + 1]:
                distinct -= 1
            start += 1

        if final - start + 1 > lungime_maxima:
            lungime_maxima = final - start + 1
            max_range_start = start
            max_range_end = final

        final += 1

    #print(lista[max_range_start:max_range_end + 1])
    return(lista[max_range_start:max_range_end + 1])

def test_cerinta1():
    assert(distincte([1,2,3,4])) == [1, 2, 3]
    assert (distincte([1, 7, 25, 6, 6])) == [1, 7, 25]
    assert (distincte([3, 3, 3])) == [3, 3, 3]


def prim(nr):
    div = 2
    while div < nr and nr % div > 0:
        div = div+1
    return div >= nr


#Oricare doua elemente consecutive difera printr-un numar prim
def secventa_prime_diferite(lista, nr_elemente_lista):

    lungime_maxima = 0
    index_inceput = 1

    auxiliar_stanga = 0
    lungime_curenta = 1

    for i in range(1, nr_elemente_lista):
        if prim(abs(lista[i - 1] - lista[i])):
            lungime_curenta += 1

        else:
            if lungime_curenta > lungime_maxima:
                lungime_maxima = lungime_curenta
                index_inceput = auxiliar_stanga

            lungime_curenta = 1
            auxiliar_stanga = i

    if lungime_curenta > lungime_maxima:
        lungime_maxima = lungime_curenta
        index_inceput = auxiliar_stanga

    if lungime_maxima <= 1:
        #print("Nu exista o secventa cu aceasta proprietate!")
        return("Nu exista o secventa cu aceasta proprietate!")
    else:
        return (lista[index_inceput:index_inceput + lungime_maxima])
        #print(lista[index_inceput:index_inceput + lungime_maxima])
        #for i in range(index_inceput, index_inceput + lungime_maxima):
            #print(lista[i])

def test_cerinta2():
    assert (secventa_prime_diferite([1, 2, 3, 4], 4)) == [1, 2, 3, 4]
    assert (secventa_prime_diferite([10], 1)) == "Nu exista o secventa cu aceasta proprietate!"
    assert (secventa_prime_diferite([3,3,3], 3)) == [3,3,3]
    assert (secventa_prime_diferite([1,7,25,6,6], 5)) == [25,6,6]
    #x[i] < x[i+1] < ... < x[i+p]
def function(lista, nr_elemente_lista):
    lungime_maxima = 0
    index_inceput = 1

    auxiliar_stanga = 0
    lungime_curenta = 1

    for i in range(1, nr_elemente_lista):
        if lista[i - 1] < lista[i]:
            lungime_curenta += 1

        else:
            if lungime_curenta > lungime_maxima:
                lungime_maxima = lungime_curenta
                index_inceput = auxiliar_stanga

            lungime_curenta = 1
            auxiliar_stanga = i

    if lungime_curenta > lungime_maxima:
        lungime_maxima = lungime_curenta
        index_inceput = auxiliar_stanga

    if lungime_maxima <= 1:
        #print("Nu exista o secventa cu aceasta proprietate!")
        return("Nu exista o secventa cu aceasta proprietate!")
    else:
        #print(lista[index_inceput:index_inceput + lungime_maxima])
        return(lista[index_inceput:index_inceput + lungime_maxima])

def test_cerinta3():
    assert(function([1,2,3],3)) == [1,2,3]
    assert(function([],0)) == "Nu exista o secventa cu aceasta proprietate!"
def main():
    # meniul aplicatiei
    lista = []
    while True:
        meniu()
        nr_cerinta = int(input())
        if nr_cerinta == 1:
            nr_elemente_lista = int(input("Scrieti numarul de elemente : "))
            citeste(lista, nr_elemente_lista)
        elif nr_cerinta == 2:
            result = distincte(lista)
            print(result)
            #distincte(lista)
            test_cerinta1()
        elif nr_cerinta == 3:
            result = secventa_prime_diferite(lista, nr_elemente_lista)
            print(result)
            test_cerinta2()
            #secventa_prime_diferite(lista, nr_elemente_lista)
        elif nr_cerinta == 4:
            result = function(lista, nr_elemente_lista)
            print(result)
            test_cerinta3()
            #function(lista, nr_elemente_lista)
        elif nr_cerinta == 5:
            print("Iesire aplicatie")
            break
        else:
            print("Valoare incorecta!")


main()
