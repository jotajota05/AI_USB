import sys

def crear_clausulas(nombre_archivo_entrada):
	archivo_entrada = open(nombre_archivo_entrada,"r")
	linea = archivo_entrada.readline()
	num_huecos = int(linea[0])
	linea = archivo_entrada.readline()
	num_cartas = int(linea[0])
	clausulas = [[] for i in range(0,num_huecos*2)]
	count = 0
	for i in range(1,num_cartas+1):
		linea = archivo_entrada.readline()[::2]
		for j in range(0,num_huecos*2):
			if linea[j]=="0":
				new_literal = [i]
				clausulas[j] = clausulas[j]+new_literal
		lineaaux = linea[0:num_huecos]
		linea = linea[num_huecos:]
		linea = linea + lineaaux
		for j in range(0,num_huecos*2):
			if linea[j]=="0":
				new_literal = [-i]
				clausulas[j] = clausulas[j]+new_literal
	archivo_entrada.close()
	return num_cartas, clausulas

#########################################################################
#PROGRAMA PRINCIPAL DE TRADUCCION DE INSTANCIA CARDPUZZLE A FORMATO CNF#
#######################################################################

if len(sys.argv) != 3:
	print "Uso: python cardpuzzle.py <archivo_entrada> <archivo_salida>"
	exit()
else:
	(num_var, clausulas) = crear_clausulas(sys.argv[1])
	archivo_salida = open(sys.argv[2],"a")
	archivo_salida.write("p cnf "+str(num_var)+" "+str(len(clausulas))+"\n")
	for i in clausulas:
		linea = ""
		for j in i:
			linea = linea + str(j) + " "
		archivo_salida.write(linea+"0\n")
	archivo_salida.close()