# Proyecto 5 - Programa N-Reinas

# Juan Garcia 05-38207
# Tamara Mendt 05-38546

import sys

#Funcion que verifica si una solucion encontrada es valida#

def es_solucion_valida(tablero):
    for i in range(0,len(tablero)):
        for j in range(0,len(tablero)):
            if tablero[i][j] == -1:
                return False
    return len(solucion_exacta(tablero)) == len(tablero)

#Funcion que verifica si una fila esta libre para ser asignada#

def libre_fila(tablero,f):
    n = len(tablero)
    for i in range(0,n):
        if tablero[f][i] == 1:
            return False
    return True

#Funcion que verifica si una columna esta libre para ser asignada#

def libre_col(tablero,c):
    n = len(tablero)
    for i in range(0,n):
        if tablero[i][c] == 1:
            return False
    return True

#Funcion que verifica si una diagonal esta libre para ser asignada#

def libre_diag(tablero,fila,col):
    n = len(tablero)
    for k in range(0,4):
        f = fila
        c = col
        while (f >= 0 and f < n and c >= 0 and c < n):
            if k == 0:
                if tablero[f][c] == 1:
                    return False
                f = f + 1
                c = c + 1
            if k == 1:
                if tablero[f][c] == 1:
                    return False
                f = f - 1
                c = c - 1
            if k == 2:
                if tablero[f][c] == 1:
                    return False
                f = f + 1
                c = c - 1
            if k == 3:
                if tablero[f][c] == 1:
                    return False
                f = f - 1
                c = c + 1
    return True

#Funcion que coloca una reina en una pisicion valida, dado un tablero#

def colocar_reina(tab,fila,num_sol):
    n = len(tab)
    
    tablero = []
    for i in range(0,n):
        tablero.append([])
        tablero[i][:] = tab[i][:]
    
    sol = 0
    i = fila
    for j in range(0,n):
        if (sol == num_sol) and (tablero[i][j] == -1) and libre_fila(tablero,i) and libre_col(tablero,j) and libre_diag(tablero,i,j):
            tablero[i][j] = 1
            for k in range(0,n):
                if tablero[k][j] != 1:
                    tablero[k][j] = 0
            for k in range(0,n):
                if tablero[i][k] != 1:
                    tablero[i][k] = 0
            for k in range(0,4):
                f = i
                c = j
                while (f >= 0 and f < n and c >= 0 and c < n):
                    if k == 0:
                        if tablero[f][c] != 1:
                            tablero[f][c] = 0
                        f = f + 1
                        c = c + 1
                    if k == 1:
                        if tablero[f][c] != 1:
                            tablero[f][c] = 0
                        f = f - 1
                        c = c - 1
                    if k == 2:
                        if tablero[f][c] != 1:
                            tablero[f][c] = 0
                        f = f + 1
                        c = c - 1
                    if k == 3:
                        if tablero[f][c] != 1:
                            tablero[f][c] = 0
                        f = f - 1
                        c = c + 1
            return tablero
        else:
            sol = sol + 1
    return False

#Funcion que calcula los sucesores de un estado dado#

def sucesores(tab):
    n = len(tab)

    tablero = []
    for i in range(0,n):
        tablero.append([])
        tablero[i][:] = tab[i][:]

    local = -1
    soluciones = []
    for k in range(0,n):
        for j in range(0,n):
            if tablero[k][j] == -1:
                local = k
                break
        if local != -1:
            break
    for l in range(0,n):
        solucion = colocar_reina(tablero,local,l)
        if solucion != False:
            soluciones.append(solucion)
    return soluciones

#Funcion que halla las soluciones para un numero de reinas dado#

def hallar_soluciones(tablero):
    num = 1
    nodos = [tablero]
    soluciones = []
    while len(nodos) != 0:
        actual = nodos.pop()
        if es_solucion_valida(actual):
            if not pertenece(solucion_exacta(actual),soluciones):
                soluciones.append(actual)
                print_sol(actual)
                num = num + 1
        else:
            suc = sucesores(actual)
            for i in range(0,len(suc)):
                nodos.append(suc[i])
    return soluciones

#Funcion que imprime una solucion#

def print_sol(tablero):
    sol = solucion_exacta(tablero)
    for i in range(0,len(tablero)):
        print "("+str(sol[i][0]+1)+","+str(sol[i][1]+1)+") ",
    print " "

#Funcion que convierte la solucion al formato especificado para imprimir#

def solucion_exacta(tablero):
    solucion = []
    n = len(tablero)
    for i in range(0,n):
        for j in range(0,n):
            if tablero[i][j] == 1:
                solucion.append([i,j])
    return solucion

#Funcion que me indica si dos estados son iguales#

def iguales(sol1,sol2):
    if len(sol1) != len(sol2):
        return False
    else:
        for i in range(0,len(sol1)):
            if sol1[i][0] != sol2[i][0] or sol1[i][1] != sol2[i][1]:
                return False
    return True

#Funcion que me dice si una solucion pertenece a una lista de soluciones#

def pertenece(sol,soluciones):
    for i in range(0,len(soluciones)):
        if iguales(sol,solucion_exacta(soluciones[i])):
            return True
    return False


#########################################################################################
################################ Programa Principal #####################################
#########################################################################################

if len(sys.argv) != 2:
    print "\nError: Ingrese bien los parametros -- use: nreinas <num_reinas>\n"
    exit()

if  (int(sys.argv[1]) < 0):
    print "\nError: El numero de Reinas debe ser positivo.\n"
    exit()

num_reinas = int(sys.argv[1])

print "\nNumero de Reinas = "+str(num_reinas)+"\n"

tablero = []

for i in range(0,num_reinas):
    fila = []
    for j in range(0,num_reinas):
        fila.append(-1)
    tablero.append(fila)

print "Soluciones:"

soluciones = hallar_soluciones(tablero)

print "\nNumero de Soluciones = "+str(len(soluciones))+"\n"
