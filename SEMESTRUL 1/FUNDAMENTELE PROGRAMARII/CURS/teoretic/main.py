def f(lista):
    n = len(lista)
    for i in range(n):
        ind = i-1
        aux = lista[i]
        while ind >= 0 and lista[ind] > aux:
            lista[ind+1] = lista[ind]
            ind = ind-1
        lista[ind+1] = aux
    return lista
print(f([1,5,4,4,9,3]))
"""
selectionsort direct
bubblesort
binarysearch
insertionsort

qsort
mergesort
"""