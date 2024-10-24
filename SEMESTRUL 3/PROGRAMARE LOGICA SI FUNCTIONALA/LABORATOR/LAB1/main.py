#9.a) Adaugare(el, el1...eln) = { el1 (+) [el], daca n < 2,
#                                 el1 (+) Adaugare(el, e2....eln), daca n >= 2
#                                }
#9.b) Concatenare(el1...eln, EL1...ELN) = { el1 (+) Concatenare(el2...eln, EL1...ELN) , daca n > 0
#                                           EL, n == 0
#                                          }

class Nod:
    def __init__(self, e):
        self.e = e
        self.urm = None


class Lista:
    def __init__(self):
        self.prim = None


'''
crearea unei liste din valori citite pana la 0
'''


def creareLista():
    lista = Lista()
    lista.prim = creareLista_rec()
    return lista


def creareLista_rec():
    x = int(input("x="))
    if x == 0:
        return None
    else:
        nod = Nod(x)
        nod.urm = creareLista_rec()
        return nod


'''
tiparirea elementelor unei liste
'''


def tipar(lista):
    tipar_rec(lista.prim)

#9.a) Adaugare(el, el1...eln) = { [el], daca n < 2,
#                                 el1 (+) Adaugare(el, e2....eln), daca n >= 2
#                                }
def adaugare(lista):
    adaugare_rec(11, lista.prim)
def adaugare_rec(el, e_curent):
    if e_curent.urm == None:
        nod = Nod(e_curent)
        e_curent.urm = nod
        return e_curent.urm
    else:
        return adaugare_rec(el, e_curent.urm)

def tipar_rec(nod):
    if nod != None:
        print(nod.e)
        tipar_rec(nod.urm)


'''
program pentru test
'''


def main():
    list = creareLista()
    #tipar(list)
    adaugare(list)
    tipar_rec(list.prim)
main()




