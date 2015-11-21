import sys

#Da el valor de la variable dados fila, columna y contenido
def variable(m, fila, columna, contenido):
	return (fila-1)*m*3 + (columna-1)*3 + contenido

#Devuelve las dimensiones del tablero
def dimension(nombre_archivo):
	archivo_entrada = open(nombre_archivo,"r")
	linea = archivo_entrada.readline()
	m=0
	for i in linea:
		if i!="\n":
			m = m*10 + int(i)
	archivo_entrada.close()
	return m

#En toda casilla debe haber una metra azul, una metra roja o ninguna metra
def casilla_no_vacia(m,nombre_archivo):
	archivo = open(nombre_archivo,"a")
	for fila in range(1,m+1):
		for columna in range(1,m+1):
			linea = ""
			for valor in range(1,4):
				var = variable(m,fila,columna,valor)
				linea = linea + str(var) + " "
			archivo.write(linea+"0\n")
	archivo.close()
	return m*m

#Toda casilla puede tener SOLAMENTE un valor. No pueden haber valores
#repetidos en una casilla
def casilla_no_rep(m,nombre_archivo):
	archivo = open(nombre_archivo,"a")
	for fila in range(1,m+1):
		for columna in range(1,m+1):
			for valor in range (1,3):
				for aux in range(valor+1,4):
					linea = "-"+str(variable(m,fila,columna,valor))+" "
					linea = linea +"-"+str(variable(m,fila,columna,aux))+" "
					archivo.write(linea+"0\n")
	archivo.close()
	return m*m*3

#Una fila no puede ser vacia originalmente
def fila_no_vacia(m,nombre_archivo):
	archivo = open(nombre_archivo,"a")
	for fila in range(1,m+1):
		linea = ""
		for columna in range(1,m+1):
			linea+= ("-"+str(variable(m,fila,columna,1))+" ")
		archivo.write(linea+"0\n")
	archivo.close()
	return m	


#Una columna debe tener metras de solo un color.
def color_columna(m,nombre_archivo,num_columna,columna):
	archivo = open(nombre_archivo,"a")
	count = 0
	for i in range(0,m):
		valor = int(columna[i])
		if valor==1:
			for j in range(0,m):
				otro_valor = int(columna[j])
				if otro_valor==2:
					linea = "-"+str(variable(m,i+1,num_columna+1,valor+1))+" "
					linea = linea +"-"+str(variable(m,j+1,num_columna+1,otro_valor+1))+" "
					archivo.write(linea+"0\n")
					count+=1
	archivo.close()
	return count

#Dada la instancia inicial se tiene que asegurar que una fila no puede quedar vacia
#y una columna no puede tener 2 elementos de diferente color.
def instancia(m,nombre_archivo_entrada,nombre_archivo_salida):
	archivo_lectura = open(nombre_archivo_entrada,"r")
	tablero = [archivo_lectura.readline().split() for i in range(0,m+1)]
	archivo_lectura.close()
	archivo_salida = open(nombre_archivo_salida,"a")
	num_vacio = 0
	#Ninguna fila puede quedar vacia
	for fila in range(1,m+1):
		linea = ""
		for columna in range(0,m):
			valor = int(tablero[fila][columna])
			if valor!=0:
				linea = linea+str(variable(m,fila,(columna+1),valor+1))+" "
			else:
				archivo_salida.write(str(variable(m,fila,columna+1,1))+" 0\n")
				num_vacio+=1
		archivo_salida.write(linea+"0\n")
	archivo_salida.close()
	#Ninguna columna puede tener dos casillas con diferente color
	num_clause= m + num_vacio
	for i in range(0,m):
		columna = [tablero[fila][i] for fila in range(1,m+1)]
		num_clause+=color_columna(m,nombre_archivo_salida,i,columna)
	return num_clause

########################################################################
#PROGRAMA PRINCIPAL DE TRADUCCION DE INSTANCIA SOLITARIO A FORMATO CNF#
######################################################################

if len(sys.argv) != 3:
	print "Uso: python solitario.py <archivo_entrada> <archivo_salida>"
	exit()
else:
	m = dimension(sys.argv[1])
	num_clause = casilla_no_vacia(m,sys.argv[2])
	num_clause += casilla_no_rep(m,sys.argv[2])
	num_clause += fila_no_vacia(m,sys.argv[2])
	num_clause += instancia(m,sys.argv[1],sys.argv[2])
	num_variables = m*m*3
	archivo_salida = open(sys.argv[2],"r+")
	info = archivo_salida.read()
	archivo_salida.close()
	archivo_salida = open(sys.argv[2],"w")	
	archivo_salida.write("p cnf "+str(num_variables)+" "+str(num_clause)+"\n"+info)
	archivo_salida.close()
