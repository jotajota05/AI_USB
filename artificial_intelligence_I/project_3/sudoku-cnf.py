import sys

#Funcion que recibe el numero de fila y de columna de una casilla
#de un tablero SUDOKU y el numero que esta en esa casilla; devuelve
#el valor de la variable correspondiente para representar el problema
#SAT en formato CNF
def var(fila,col,valor):
	return (fila-1)*81 + (col-1)*9 + valor

#Toda casilla debe ser no vacia
def casilla_no_vacia(nombre_archivo):
	archivo = open(nombre_archivo,"a")
	for fila in range(1,10):
		for columna in range(1,10):
			linea = ""
			for valor in range(1,10):
				variable = var(fila,columna,valor)
				linea = linea + str(variable) + " "
			archivo.write(linea+"0\n")
	archivo.close()


#Toda casilla puede tener SOLAMENTE un valor. No pueden haber valores
#repetidos en una casilla
def casilla_no_rep(nombre_archivo):
	archivo = open(nombre_archivo,"a")
	for fila in range(1,10):
		for columna in range(1,10):
			for valor in range (1,9):
				for aux in range(valor+1,10):
					linea = "-"+str(var(fila,columna,valor))+" "
					linea = linea +"-"+str(var(fila,columna,aux))+" "
					archivo.write(linea+"0\n")
	archivo.close()

#Toda fila debe tener los numeros del 1 al 9 sin repeticiones
def fila_no_rep(nombre_archivo):
	archivo = open(nombre_archivo,"a")
	for fila in range(1,10):
		for valor in range(1,10):
			for columna in range(1,9):
				for aux in range(columna+1,10):
					linea = "-"+str(var(fila,columna,valor))+" "
					linea = linea +"-"+str(var(fila,aux,valor))+" "
					archivo.write(linea+"0\n")
	archivo.close()
	
#Toda columna debe tener los numeros del 1 al 9 sin repeticiones
def col_no_rep(nombre_archivo):
	archivo = open(nombre_archivo,"a")
	for columna in range(1,10):
		for valor in range(1,10):
			for fila in range(1,9):
				for aux in range(fila+1,10):
					linea = "-"+str(var(fila,columna,valor))+" "
					linea = linea +"-"+str(var(aux,columna,valor))+" "
					archivo.write(linea+"0\n")
	archivo.close()

#Todo cuadrado de 3x3 debe tener los numeros del 1 al 9 sin repeticiones
def cuad_no_rep(nombre_archivo,cuadrado_fila,cuadrado_columna):
	archivo = open(nombre_archivo,"a")
	cotainf_fila = 3*cuadrado_fila+1
	cotasup_fila = cotainf_fila + 3
	cotainf_col = 3*cuadrado_columna+1
	cotasup_col = cotainf_col + 3
	for valor in range(1,10):
		for fila in range(cotainf_fila,cotasup_fila):
			for col in range(cotainf_col,cotasup_col):
				linea="-"+str(var(fila,col,valor))+" "
				for fila_aux in range(fila,cotasup_fila):
					for col_aux in range(cotainf_col,cotasup_col):
						if col_aux>col or fila_aux>fila:
							new_line = linea +"-"+str(var(fila_aux,col_aux,valor))+" "
							archivo.write(new_line+"0\n")
	archivo.close()

#Lectura del estado inicial de la tabla sudoku con algunas variables asignadas
def estado_inicial(nombre_arch_lectura,nombre_arch_escritura):
	arch_lectura = open(nombre_arch_lectura,"r")
	arch_escritura = open(nombre_arch_escritura,"a")
	instancia = arch_lectura.readline();
	i=0
	for fila in range(1,10):
		for columna in range(1,10):
			if instancia[i]!=".":
				clausula = str(var(fila,columna,int(instancia[i])))
				arch_escritura.write(clausula+" 0\n")
			i = i+1
	arch_lectura.close()
	arch_escritura.close()

def primera_linea(nombre_archivo_entrada,nombre_archivo_salida):
	archivo_entrada = open(nombre_archivo_entrada,"r")
	archivo_salida = open(nombre_archivo_salida,"a")
	num_var = 729
	num_clause = 11745
	linea = archivo_entrada.readline()
	for i in linea:
		if i!="." and i!="\n":
			num_clause+=1
	archivo_entrada.close()
	archivo_salida.write("p cnf "+str(num_var)+" "+str(num_clause)+"\n")

#####################################################################
#PROGRAMA PRINCIPAL DE TRADUCCION DE INSTANCIA SUDOKU A FORMATO CNF#
###################################################################

if len(sys.argv) != 3:
	print "Uso: python hola.py <archivo_entrada>  <archivo_salida>"
	exit()
else:
	primera_linea(sys.argv[1],sys.argv[2])
	casilla_no_vacia(sys.argv[2])
	casilla_no_rep(sys.argv[2])
	fila_no_rep(sys.argv[2])
	col_no_rep(sys.argv[2])
	for i in range(0,3):
		for j in range(0,3):
			cuad_no_rep(sys.argv[2],i,j)
	estado_inicial(sys.argv[1],sys.argv[2])
