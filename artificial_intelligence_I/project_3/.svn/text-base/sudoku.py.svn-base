import sys
import os

def valor(variable):
	if variable%9 == 0:
		return 9
	else:
		return variable%9

if (len(sys.argv)) != 2:
	print "Uso: python sudoku.py <archivo_entrada>"
	exit()

if (sys.argv[1])[-5:] != ".inst":
	print "La extension del archivo de entrada debe ser .inst"
	exit()

archivo_salida = "cnf/"+(sys.argv[1])[:-5]+".cnf"
print "\nEl archivo en formato cnf utilizado para el solver se puede encontrar en "+archivo_salida+"\n"

comando_python = "python sudoku-cnf.py "+sys.argv[1]+" "+archivo_salida
os.system(comando_python)
comando_zchaff = "./zchaff "+archivo_salida+" 100"
resultado = (os.popen(comando_zchaff).read()).split()

if resultado[-1]=="UNSAT":
	solucion = ["0" for i in range(0,81)]
	print "\nSolucion: "+solucion+"\n"
else:
	variables = [i for i in resultado[17:746] if int(i)>0]
	salida = ""
	for i in variables:
		salida+=str(valor(int(i)))
	print "\nSolucion: "+salida+"\n"
